void CvOutCalibration(int currentOscFreq1, int currentOscFreq2)
{
  int targetFrequency = noteFrequencies[probingFreqIndex];
 //int targetFrequency = 100;
  if (intitialFreqSet == false && calibWaiting == false)
  {
    if(chan == 0)
    {
      if (currentOscFreq1 > noteFrequencies[probingFreqIndex])
      {
         cvOutTable[0][probingFreqIndex] = 4095;
         probingFreqIndex++;
      }
      else
      {
          intitialFreqSet = true;
      }
    }
    else
    {
      if (currentOscFreq2 > noteFrequencies[probingFreqIndex])
      {
        cvOutTable[1][probingFreqIndex] = 4095;
        probingFreqIndex++;
      }
      else
      {
       intitialFreqSet = true;
      }
    }
  }
  else if(chan == 0)
  {
    tuningDurationCount++;
    if (tuningDurationCount > CvTuningDuration)
    {
      valueHasChanged = true;
      if (targetFrequency == currentOscFreq1 )
      {
        cvOutTable[0][probingFreqIndex] = cvValueForCalib;
        lastSavedFreq = currentOscFreq1;
        probingFreqIndex++;
        cvValueForCalib -= 8;
      }
      else if (currentOscFreq1 > targetFrequency && prevMeasuredFreq < targetFrequency)
      {
        tuningDurationCount = 0;
        int delta1 = currentOscFreq1 - targetFrequency;
        int delta2 = targetFrequency - prevMeasuredFreq;
        int cvToSave = delta1 < delta2 ? prevCvValueForCalib : cvValueForCalib; 
        cvOutTable[0][probingFreqIndex] = cvToSave;
        lastSavedFreq = currentOscFreq1;
        probingFreqIndex++;
        cvValueForCalib -= 8;
      }
      prevCvValueForCalib = cvValueForCalib;
      prevMeasuredFreq = currentOscFreq1;
      tuningDurationCount = 0;
      if (probingFreqIndex >= 104 || cvValueForCalib <= 0)
      {
        chan = 1;
        probingFreqIndex = 0;
        tuningDurationCount = 0;
        cvValueForCalib = 4095;
        prevCvValueForCalib = 4095;
        prevMeasuredFreq = 100;
        intitialFreqSet = false;
        calibWaiting = true;
      }
      else if (cvValueForCalib > 0)
      {
        cvValueForCalib--; 
      }
    }
  }
  else if (calibWaiting == false)
  {
    tuningDurationCount++;
    if (tuningDurationCount > CvTuningDuration)
    {
      valueHasChanged = true;
      if (targetFrequency == currentOscFreq2)
      {
        cvOutTable[1][probingFreqIndex] = cvValueForCalib;
        lastSavedFreq = currentOscFreq2;
        probingFreqIndex++;
        cvValueForCalib -= 8;
      }
      else if (currentOscFreq2 > targetFrequency && prevMeasuredFreq < targetFrequency)
      {
        tuningDurationCount = 0;
        int delta1 = currentOscFreq2 - targetFrequency;
        int delta2 = targetFrequency - prevMeasuredFreq;
        int cvToSave = delta1 < delta2 ? prevCvValueForCalib : cvValueForCalib; 
        cvOutTable[1][probingFreqIndex] = cvToSave;
        lastSavedFreq = currentOscFreq2;
        probingFreqIndex++;
        cvValueForCalib -= 8;
      }
      prevCvValueForCalib = cvValueForCalib;
      prevMeasuredFreq = currentOscFreq2;
      tuningDurationCount = 0;
      if (probingFreqIndex >= 104 || cvValueForCalib <= 0)
      {
        cvOutcalibrationFinished = true;
        if (CvSlotSet == false)
        {
          //setKnobsState();
          CV_slot = (analogRead(pot1) >> 5) / 32;
        }
        else if (CvTableNameSet == false)
        {
          knobValue[0] = analogRead(pot1) >> 5;
          knobValue[1] = analogRead(pot2) >> 5;
          knobValue[2] = analogRead(pot3) >> 5;
          knobValue[3] = analogRead(pot4) >> 5;
          buttonValue[0] = digitalRead(PC15) == LOW ? true : false;
          //setKnobsState();
          display.clearDisplay();
          display.setTextColor(WHITE);
          CV_tableName = encodeName(CV_tableName);
          display.display();
        }
        else
        {
          cv_table_saving(CV_tableName, CV_slot);
        }
      }
      else if (cvValueForCalib > 0)
      {
        cvValueForCalib--; 
      }
    }
  }
}


void cv_table_saving(String tableName, int index)
{
    Timer2.pause();
    setting->saveCvTable(cvOutTable, tableName, index);                                                                        // If loading state is high (see setting.cpp), use load to get the provisionnal preset name or load the preste if button 1 has been trigged
    Timer2.resume();
}

void cv_table_loading(int index)
{
  Timer2.pause();
  setting->loadCvTable(cvOutTable, index); 
  for(int i = 0; i < 104; i++)
  {
    stepSequencer[0]->setDacTableAt(i, cvOutTable[0][i]);
    stepSequencer[1]->setDacTableAt(i, cvOutTable[1][i]);
  }
  Timer2.resume();
}
