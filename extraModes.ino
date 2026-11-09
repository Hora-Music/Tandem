// Tandem, multimode CV generator.
// Copyright (C) 2020 Raphaël Hoffman (hora.music.contact@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-3.0-or-later

void extraModes()
{
   if (tableSelectorMode == false)
   {
    if (extraMode == TUNER || CvOutCalib == true)
    {
      /*if (extraMode == TUNER)
      {
        GPIOA->regs->BSRR = 0b0000000000001000;
        GPIOA->regs->BSRR = 0b0000000001000000;
      }
      else
      {
        GPIOA->regs->BRR = 0b0000000000001000;
        GPIOA->regs->BRR = 0b0000000001000000;
      }*/
      if (inc > 3200)
      {
        if (digitalRead(PB4) == HIGH)
        {
          extraModesButtonReady = true;
        }
        if (digitalRead(PB4) == LOW && extraModesButtonReady == true)
        {
          extraModesButtonReady = false;
          extraMode++;
          if (extraMode > 1)
          {
            extraMode = 0;
          }
          calibWaiting = false;
          if (cvOutcalibrationFinished == true)
          {
            if (CvSlotSet == false)
            {
              CvSlotSet = true;
              saveCvTableNum(CV_slot);
            }
            else
            {
              CvTableNameSet = true;
            }
            
          }
        }
        tunerFrequency = 1000000/period;//timer rate with an extra zero/period
        tunerFrequency2 = 1000000/period2;//timer rate with an extra zero/period
        if (CvOutCalib == false)
        {
          display.clearDisplay();
          display.setCursor(0, 15);
          display.setTextColor(WHITE);
          display.setCursor(10, 15);
          display.print(tunerFrequency / 10.0f);
          display.setCursor(55, 15);
          display.print(" Hz");
          display.setCursor(0, 15);
          display.setTextColor(WHITE);
          display.setCursor(80, 15);
          display.print(tunerFrequency2 / 10.0f);
          noteDisplayChannel1(tunerFrequency); 
          noteDisplayChannel2(tunerFrequency2); 
          display.display();     
        }
        else if (cvOutcalibrationFinished == false && CvOutCalib == true)
        {
          CvOutCalibration(tunerFrequency, tunerFrequency2);
          if (calibWaiting == true)
          {
            display.clearDisplay();
            display.setCursor(35, 5);
            display.setTextColor(WHITE);
            display.print("connect ch2 and");
            display.setCursor(35, 20);
            display.print("press the main button");
            display.display();  
          }
          else if (probingFreqIndex > 0)
          {
            display.clearDisplay();
            display.setCursor(35, 5);
            display.setTextColor(WHITE);
            display.print(prevMeasuredFreq);
            display.setCursor(35, 20);
            display.print("calib chan: ");
            display.setCursor(95, 20);
            display.print(chan + 1);
            display.setCursor(15, 35);
            display.print("lastSavedFreq:");
            display.setCursor(95, 35);
            display.print(lastSavedFreq);
            display.setCursor(15, 50);
            display.print("lastSavedCv:");
            display.setCursor(90, 50);
            display.print(cvOutTable[chan][probingFreqIndex - 1]);
            display.display();     
          }
          else
          {
            display.clearDisplay();
            display.setCursor(35, 15);
            display.setTextColor(WHITE);
            display.print("calib");
            display.display();     
          }
        }
        else if (CvOutCalib == true)
        {
          if(CvSlotSet == false)
          {
            if (ffff == true)
            {
               Timer2.pause();
              setting->initCvTableName(0);
              setting->initCvTableName(1);
              setting->initCvTableName(2);
              setting->initCvTableName(3);
              Timer2.resume();
              ffff = false;
            }
            CvOutCalibration(tunerFrequency, tunerFrequency2);
            Timer2.pause();
            display.clearDisplay();
            display.setCursor(10, 5);
            display.setTextColor(WHITE);
            display.print(CV_slot);
              
            display.print(setting->getCvTableName(0));
            display.setCursor(10, 15);
            display.print(setting->getCvTableName(1));
            display.setCursor(10, 25);
            display.print(setting->getCvTableName(2));
            display.setCursor(10, 35);
            display.print(setting->getCvTableName(3));
            display.drawRect(8, 5 + CV_slot * 9, 50, 10, WHITE);
            display.display();   
            Timer2.resume();
          }
          else if(CvTableNameSet == false)
          {
            CvOutCalibration(tunerFrequency, tunerFrequency2);
          }
          else
          {
            CvOutCalibration(tunerFrequency, tunerFrequency2);
            display.clearDisplay();
            display.setCursor(35, 15);
            display.setTextColor(WHITE);
            display.print("Calibration done");
            display.display();     
          }
        }
        inc = 0;
      }
    }
    else if (extraMode == SCOPE)
    {
      if (inc > scopeRate)
      {
        if (digitalRead(PB4) == HIGH)
        {
          extraModesButtonReady = true;
        }
        if (digitalRead(PB4) == LOW && extraModesButtonReady == true)
        {
          extraModesButtonReady = false;
          extraMode++;
          if (extraMode > 1)
          {
            extraMode = 0;
          }
        }
        if (scopePos < 127)
        {
          if (scopePos < 64)
          {
            analog_in_buffers[scopePos][0]= newData / 4;
            analog_in_buffers[scopePos][2] = newData2 / 4;
          }
          else
          {
            analog_in_buffers[scopePos - 64][1] = newData / 4;
            analog_in_buffers[scopePos - 64][3]= newData2 / 4;
          }
          scopePos++;
        }
        else
        {
          analog_in_buffers[scopePos - 64][1] = newData / 4;
          analog_in_buffers[scopePos - 64][3]= newData2 / 4;
          scopePos = 0;
          display.clearDisplay();
          for (int i = 0; i < 63; i++)
          {
              display.drawLine(i, 64 - analog_in_buffers[i][0], i + 1, 64 - analog_in_buffers[i + 1][0], WHITE); // 0 64
              display.drawLine(i + 63, 64 - analog_in_buffers[i][1], i + 63 + 1, 64 - analog_in_buffers[i + 1][1], WHITE); // 64 
              display.drawLine(i, 64 - analog_in_buffers[i][2], i + 1, 64 - analog_in_buffers[i + 1][2], WHITE);
              display.drawLine(i + 63, 64 - analog_in_buffers[i][3], i +63 + 1, 64 - analog_in_buffers[i + 1][3], WHITE);
          } 
          display.display();
          forceDisplay = false;
        }
        inc = 0;
      }
    }
    else if (extraMode == VOLTMETER)
    {
      if (digitalRead(PB4) == HIGH)
      {
        extraModesButtonReady = true;
      }
      if (digitalRead(PB4) == LOW && extraModesButtonReady == true)
      {
        extraModesButtonReady = false;
        extraMode++;
        if (extraMode > 3)
        {
          extraMode = 0;
        }
      }
      display.clearDisplay();
      display.setCursor(0, 15);
      display.setTextColor(WHITE);
      display.print(newData);
      display.display();          
    }
    else if (extraMode == VCO)
    {
      if (digitalRead(PB4) == HIGH)
      {
        extraModesButtonReady = true;
      }
      if (digitalRead(PB4) == LOW && extraModesButtonReady == true)
      {
        extraModesButtonReady = false;
        extraMode++;
        if (extraMode > 3)
        {
          extraMode = 0;
        }
      }
      display.setTextSize(2);
      display.setCursor(40, 25);
      display.print("OSC");
      display.display();    
      display.setTextSize(1);
    }
   }
   else
   {
    if (ffff == true)
      {
        Timer2.pause();
        setting->initCvTableName(0);
        setting->initCvTableName(1);
        setting->initCvTableName(2);
        setting->initCvTableName(3);
        Timer2.resume();
        ffff = false;
      }
      int pot = (analogRead(pot1) >> 5) / 32;
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setCursor(0, 54);
      display.print("select");
      if (cvTableNum != pot)
      {
        display.drawRect(5, 0 + pot * 11, 100, 12, WHITE);
      }
     
      for (int i = 0; i < 4; i++)
      {
        if (i != cvTableNum)
        {
          display.setTextColor(WHITE);
          display.setCursor(6, 2 + i * 11);
          display.print(setting->getCvTableName(i));
        }
        else
        {
          display.fillRect(5, 0 + i * 11, 100, 12, WHITE);
          display.setTextColor(BLACK);
          display.setCursor(6, 2 + i * 11);
          display.print(setting->getCvTableName(i));
          display.setTextColor(WHITE);
        }
      }
      display.display();  
      if (digitalRead(PB4) == HIGH)
      {
        tableSelectedButtonReady = true;
      }
      if (digitalRead(PB4) == LOW && extraModesButtonReady == true)
      {
        tableSelectedButtonReady = false;
        saveCvTableNum(pot);
        cvTableNum = pot;
      }
   }
}
