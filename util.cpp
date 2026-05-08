
#include "util.h"

void util::init()
{
  for (int i = 0; i < 6; i++)
  {
    lastAnalogValue[i] = 0;
    lastIncValue[i] = 0;
    incCount[i] = 0;
    decCount[i] = 0;
    fluct[i] = false;
  }
}

////////////////////////////////// Detect trigerring (rising edge) ////////////////////

bool util::triggerActive(int gateIn, int channel)
{
  bool trig = false;
  if (gateIn > 0 && previousGateIn[channel] <= 0.5)
  {
    trig = true;
  }
  previousGateIn[channel] = gateIn;
  return trig;
}

///////////////////////// Init a triggering and set his length ////////////////////

uint16_t util::triggCalibrer(int trigInit_1, int durationMillis, int channel)
{
    float durationFrames = durationMillis * 2;
    int trigOut = 0;
    if (trigInit_1 > 0)
    {
        trigFrame[channel] = 0;
        trigDetected[channel] = true;
        trigOut = 5;
    }
    if (trigDetected[channel])
    {
        trigFrame[channel] = trigFrame[channel] + 1;
        trigOut = 5;
    }
    if (trigFrame[channel] > durationFrames)
    {
        trigDetected[channel] = false;
    }
    return trigOut;
}

///////////////////////// Avoid fluctuation for the potentiometers values /////////////////

uint16_t util::antiFluct(uint16_t analogValue, int potNum)
{
    uint16_t stableValue = 0;

    if (analogValue == lastAnalogValue[potNum] + 1 )
    {
        if (analogValue == lastIncValue[potNum])
        {
            incCount[potNum]++;
        }
        else
        {
            incCount[potNum] = 0;
            fluct[potNum] = false;
        }
        lastIncValue[potNum] = analogValue;
    }
    if (analogValue == lastAnalogValue[potNum] - 1 )
    {
        if (analogValue == lastDecValue[potNum])
        {
            decCount[potNum]++;
        }
        else
        {
            decCount[potNum] = 0;
            fluct[potNum] = false;
        }
        lastDecValue[potNum] = analogValue;
    }
    if (analogValue >= lastAnalogValue[potNum] + 2 || analogValue <= lastAnalogValue[potNum] - 2)
    {
        decCount[potNum] = 0;
        incCount[potNum] = 0;
        fluct[potNum] = false;
    }
    if (decCount[potNum] > 3 || incCount[potNum] > 3)
    {
        fluct[potNum] = true;
    }
    if (fluct[potNum] == true)
    {
        if (decCount[potNum] > 3)
        {
            stableValue = lastDecValue[potNum];
        }
        else
        {
            stableValue = lastIncValue[potNum];
        }
        if (analogValue >= lastDecValue[potNum] + 2 || analogValue <= lastDecValue[potNum] - 2 || analogValue >= lastIncValue[potNum] + 2 || analogValue <= lastIncValue[potNum] - 2)
        {
            decCount[potNum] = 0;
            incCount[potNum] = 0;
        }
    }
    else
    {
        stableValue = analogValue;
    }
    lastAnalogValue[potNum] = analogValue;
    return stableValue;
}

