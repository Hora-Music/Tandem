
/*
 * ----------------------------------------Calculate the calibration values and storing in the non volatile memory---------------------------------------
 * 
 * If 0.1% tolerant resistors are used for the CV input circuit, the calibration should be useless,
 * this said some of the modules coming from the manufacturer seems to not meet this tolerance even if I asked for 0.1% resistors.
 * This gives a CV input returning 64 or 65 instead of 63 (when refer to the 0 to 127 value used by the cv processors) when there's no CV input connected.
 * As it is difficult for a small company to verify and require certainty of this high resistor's accuracy, I decided to implement a calibration process.
 * This is useless on most of the modules, but the process only has to be launch once and it ensure accuracy for every units. 
 * To calibrate the module: press and hold "channel 2" button, power on the module whitheout any jack in the cv inputs, release the button, and wait 5 secondes
 * to ensure the module is calibrated before using the CV inputs.
 * 
 * -------------------------------------------------------------------------------------------------------------------------------------------------------
 */


 void saveCvTableNum(int num)
{
  EEPROM.write(72, num);
}

int loadCvTableNum()
{
  int num = EEPROM.read(72);
  return num > 3 ? 3 : num;
}
void seq_CV_in_calibration_collector()
{
  for (int i = 0; i < 2; i ++)
  {
    if (previousMeasure[i] != CV_input[i])
    {
      measureStabity[i] = 0;
      measureCalibCount[i]++;
    }
    else
    { 
      measureStabity[i]++;
    }
    if (measureStabity[i] > biggestMeasureStabity[i] && seqCalibValueSet[i][0] == false)
    {
        bestSeqCalibCandidate[i] = CV_input[i];
        biggestMeasureStabity[i] = measureStabity[i];
        seqCalibValueSet[i][0] = true;
    }
    else if (measureStabity[i] > secondChoiceMeasureStabity[i] && seqCalibValueSet[i][1] == false)
    {
      if (bestSeqCalibCandidate[i] != CV_input[i])
      {
        secondSeqCalibCandidate[i] = CV_input[i];
        secondChoiceMeasureStabity[i] = measureStabity[i];
        seqCalibValueSet[i][1] = true;
      }
    }
    previousMeasure[i] = CV_input[i];
  }
}

void CV_in_calibration()
{
  if (calibFrameCount > 10000)
  {
    calibrationMode = false;
    if (CV_input[0] > 0)
    {
      CV_accuracy_comp[0] = CV_input[0] ;
      CV_accuracy_comp_sign[0] = 1;
    }
    else if (CV_input[0] < 0)
    {
      CV_accuracy_comp[0] = CV_input[0];
      CV_accuracy_comp_sign[0] = 0;
    }
    if (CV_input[1] > 0)
    {
      CV_accuracy_comp[1] = (CV_input[1]);
      CV_accuracy_comp_sign[1] = 1;
    }
    else if (CV_input[1] <= 0)
    {
      CV_accuracy_comp[1] = CV_input[1];
      CV_accuracy_comp_sign[1] = 0;
    }
    EEPROM.write(0, CV_accuracy_comp[0]);
    EEPROM.write(1, CV_accuracy_comp[1]);
    EEPROM.write(2, CV_accuracy_comp_sign[0]);
    EEPROM.write(3, CV_accuracy_comp_sign[1]);
    waitingForCvCalibration = true;
  }
}

/////////////////////////////////////////////////////// Load the calibration values from the non volatile memory /////////////////////////////////////////////////////////

void Load_CV_Compensator() 
{
  if (calibrationMode == false && waitingForCvCalibration == false && seqCvCalibration == false)
  {
    CV_accuracy_comp[0] = EEPROM.read(0);
    CV_accuracy_comp[1] = EEPROM.read(1);
    CV_accuracy_comp_sign[0] = EEPROM.read(2);
    CV_accuracy_comp_sign[1] = EEPROM.read(3);
    for (int i = 0 ; i < 60; i++)
    {
       bestCandidates[i][0] = EEPROM.read(4 + i * 4);
       secondCandidates[i][0] = EEPROM.read(4 + i * 4 + 1);
       bestCandidates[i][1] = EEPROM.read(4 + i * 4 + 2);
       secondCandidates[i][1] = EEPROM.read(4 + i * 4 + 3);
    }
    for (int i = 0 ; i < 60; i++)
    {
      for (int j = 0; j < 2; j++)
      {
         if (secondCandidates[i][j] == bestCandidates[i][j])
         {
          lowSecondCandidates[i][j] = highSecondCandidates[i][j] = bestCandidates[i][j];
         }
         else if (secondCandidates[i][j] > bestCandidates[i][j])
         {
           highSecondCandidates[i][j] = secondCandidates[i][j];
           lowSecondCandidates[i][j] = bestCandidates[i][j];
         }
         else if (secondCandidates[i][j] < bestCandidates[i][j])
         {
           highSecondCandidates[i][j] = bestCandidates[i][j];
           lowSecondCandidates[i][j] = secondCandidates[i][j];
         }
      }
    }
    for (int i = 0 ; i < 60; i++)
    { 
      for (int j = 0 ; j < 2; j++)
      { 
        if (i == 0)
        {
          lowSecondCandidates[i][j] = 0;
          int delta = lowSecondCandidates[i + 1][j] - highSecondCandidates[i][j];
          highSecondCandidates[i][j] = highSecondCandidates[i][j] + (delta / 2);
        }
        else if (i == 60 || highSecondCandidates[i][j] >= 1064)
        {
          lowSecondCandidates[i][j] = highSecondCandidates[i - 1][j] + 1;
          if (i == 60)
          {
            highSecondCandidates[i][j] = 1064;
          }
          else
          {
            int delta = lowSecondCandidates[i + 1][j] - highSecondCandidates[i][j];
            highSecondCandidates[i][j]= highSecondCandidates[i][j] + (delta / 2);
          }
        }
        else
        {
          lowSecondCandidates[i][j] = highSecondCandidates[i - 1][j] + 1;
          int delta = lowSecondCandidates[i + 1][j] - highSecondCandidates[i][j];
          highSecondCandidates[i][j] = highSecondCandidates[i][j] + (delta / 2);
        }
      }
    }
    /*for (int i = 0 ; i < 60; i++)
    { 
      for (int j = 0 ; j < 2; j++)
      { 
        if (i > 1)
        {
          if((bestCandidates[i - 1][j] != bestCandidates[i][j] - 1) && (secondCandidates[i - 1][j] != bestCandidates[i][j] - 1))
          {
            lowSecondCandidates[i][j] = bestCandidates[i][j] - 1;
          }
        }
        if (i < 59)
        {
          if((bestCandidates[i + 1][j] != bestCandidates[i][j] + 1) && (bestCandidates[i + 2][j] != bestCandidates[i][j] + 1) && (secondCandidates[i + 1][j] != bestCandidates[i][j] + 1))
          {
            highSecondCandidates[i][j] = bestCandidates[i][j] + 1;
          }
        }
      }
    }*/
  }
}

///////////////////////////////////////////////////////////////// Set SPI2, DMA for the ADC, timer2 //////////////////////////////////////////////////////////////////////

void set_SPI()
{
  SPI_2.begin();
  SPI_2.setBitOrder(MSBFIRST);
  SPI_2.setDataMode(SPI_MODE0); 
  SPI_2.setClockDivider(SPI_CLOCK_DIV8); 
}
void set_ADC_DMA()
{
  myADC.calibrate();
  for (unsigned int j = 0; j <6; j++) 
    pinMode(pins[j], INPUT_ANALOG);
  //1, 7, 13, 28, 41, 55, 71, 239
  //if(tunerMode == false)
  //{
  myADC.setSampleRate(ADC_SMPR_13_5);//ADC_SMPR_1_5
  //}
  myADC.setScanMode();              
  myADC.setPins(pins, 6);           
  myADC.setContinuous();           
  myADC.setDMA(dataPoints, 6, (DMA_MINC_MODE | DMA_CIRC_MODE), NULL); 
  myADC.startConversion();    
}

void set_Timer()
{
  Timer2.setMode(TIMER_CH1, TIMER_OUTPUTCOMPARE);
  if(tunerMode == false && CvOutCalib == false)
  {
    Timer2.setPeriod(1000); // in microseconds 500 -> 2Khz
  }
  else
  {
   Timer2.setPeriod(10); // in microseconds 500 -> 2Khz
  }
  Timer2.setCompare(TIMER_CH1, 1);   
  Timer2.attachInterrupt(TIMER_CH1, timerTick);
}

//////////////////////////////////////////////////////////// Init of the trigger and cv inputs buffers ///////////////////////////////////////////////////////////////////

void initBuffers()
{
  for (int i = 0; i <2; i++)
  {
      for (int j = 0; j < BUFFER_SIZE; j++)
      {
        trig_in_buffers[j][i] = 0;
        analog_in_buffers[j][i] = 0;
      }
  }
}
