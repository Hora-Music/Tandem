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

////////////////////////////////// Determine if the knobs are moved by the user, store the value in the current buffer tail index in the knobValue array ////////////////////////////

int getMappedCvValue(uint16_t inputValue, int channelNum)
{
  int out = 0;
  for(int i = 1; i < 60; i++)
  {
    if (inputValue >= lowSecondCandidates[i][channelNum] && inputValue <= highSecondCandidates[i][channelNum])
    {
      out = i;
      return out;
    }
  }
  return out;
}

void setKnobsState()
{
  for (int i = 0; i < 4; i++)
  {
    if(i == 1)
    { 
      if (setting->getKeyBoardMode(setting->getEditChannel()) == true && setting->getCurrentMenu() == CLASSIC_SEQUENCER && setting->getMainMenuOpened() == false && setting->getRoutingMenuOpened() == false)
      {
        knobValue[i] = setting->getEditChannel() == 0 ? getMappedCvValue(CV_input[1], 1) : getMappedCvValue(CV_input[0], 0) ;
      }
      else
      {
        knobValue[i] = analog_in_buffers[input_buff_tail][i];
      }
    }
    else
    {
      knobValue[i] = analog_in_buffers[input_buff_tail][i];
    }
    knobMoved[i] = controlScanner->detectKnobChanges(knobValue[i], i, firstFrame);
  }
  for (int i = 0 ; i < 4; i++)
  {
    knobWasMoved[i] = controlScanner->lookBackToKnob(i, 4000);
  }
  setting->scanKnobLock(knobValue);
}

//////////////////////////////////////////////////////////// Scan to detect buttons rising edge and storing in butotnTirgged array ////////////////////////////////////////////////////

void scanButtonPressing()
{
  for (int i = 0; i < 7; i++)
  {
      buttonTrigged[i] = controlScanner->detectButtonRisingEdge(i);
      if (unlockButton[i] == true)
      {
        effectiveTrigged[i] =  buttonTrigged[i];
      } 
      if (controlScanner->getButtonValue(i) == false)
      {
         unlockButton[i] = true;
      }
  }
  if (buttonValue[4] != 0)
  {
     button_4_hold_count ++; 
  }
  if (button_4_hold_count > 5000)
  {
     button_4_hold_count = 0;
     button_4_hold = true;
   }
}

/////////////////////////////////////////////////////////// Filling the routing map (two dimensions array, see setting.cpp) /////////////////////////////////////////////////////////// 

void mapRouting()
{
  for (int i = 0; i < 4; i++)
  {
     for (int j = 0; j < 4; j++)
     {
        routingMap[i][j] = setting->getPatchMapItem(i, j);
     }
  }
}

/////////////////////////////////////////////////////////// Routing and attenuation for the physical and virtual CV and gate inputs //////////////////////////////////////////////////////////////
    
void controlRouting()
{
    int previousOutput[4];
    int prevSampleIndex = 0;
    
    if (output_buff_head == 0)
    {
      prevSampleIndex = BUFFER_SIZE - 1;
    }
    else
    {
      prevSampleIndex = output_buff_head - 1;
    }
    previousOutput[0] = trig_output_buffer_A[prevSampleIndex];
    previousOutput[1] = output_buffer_A[prevSampleIndex];
    previousOutput[2] = trig_output_buffer_B[prevSampleIndex];
    previousOutput[3] = output_buffer_B[prevSampleIndex];
    previousOutput[1] = (127 - (previousOutput[1]  / 32)) - 64;
    previousOutput[3] = (127 - (previousOutput[3]  / 32)) - 64;
    
    for (int i = 0; i < 2; i++)
    {
      CV_input[i] = analog_in_buffers[input_buff_tail][i + 4] * 1.04;
      if (seqCvCalibration == false)
      {
        if (setting->getModel_1() != CLASSIC_SEQUENCER && i == 1)
        {
          CV_input[i] -= 64;
          if (CV_accuracy_comp_sign[i] == 0)
          {
            CV_input[i] += CV_accuracy_comp[i];
          }
          else if (CV_accuracy_comp_sign[i] == 1)
          {
            CV_input[i] -= CV_accuracy_comp[i];
          }
        }
        else if (setting->getModel_2() != CLASSIC_SEQUENCER && i == 0)
        {
          CV_input[i] -= 64;
          if (CV_accuracy_comp_sign[i] == 0)
          {
            CV_input[i] += CV_accuracy_comp[i];
          }
          else if (CV_accuracy_comp_sign[i] == 1)
          {
            CV_input[i] -= CV_accuracy_comp[i];
          }
        }
        else if (calibrationMode == true)
        {
         CV_input[i] -= 64;
        }
      }
    }
    for (int i = 0; i <2; i++)
    {
        for (int j = 0; j <2; j++)
        {
            destArray[i][j] = setting->getCVControlledParam(j, i);
        }
    }
    
    CV_int[0][0] = float(setting->getParamArray(0, INT_CV_PARAM1)) * 0.0079;
    CV_int[1][0] = float(setting->getParamArray(1, INT_CV_PARAM1)) * 0.0079;
    CV_int[0][1] = float(setting->getParamArray(0, INT_CV_PARAM2)) * 0.0079;
    CV_int[1][1] = float(setting->getParamArray(1, INT_CV_PARAM2)) * 0.0079;
    for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j <2; j++)
      {
        if (CV_int[i][j] > 1)
        {
          CV_int[i][j] = 1;
        }
      }
    }
    
    CVmixer->setCVLevels(CV_int);
    CVmixer->setCVdestinations(destArray);
    CVmixer->internalControlSumming(routingMap, previousOutput);
    CVmixer->externalControlSumming(CV_input);
    CVmixer->finalSumming();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            float paramValue = 0.0; 
            if ((setting->getModel_1() == LFO && j == 0 && setting->getParamArray(0, LFO_SYNC) != false) && i == 1)
            {
              float rawValue = setting->getParamArray(j, i);
              paramValue = int(floor(rawValue / 16)) * 16;
            }
            else if ((setting->getModel_1() != LFO && setting->getModel_2() == LFO && j == 1 && setting->getParamArray(1, LFO_SYNC) == true) && i == 1)
            {
              float rawValue = setting->getParamArray(j, i);
              paramValue = int(floor(rawValue / 16)) * 16;
            }
            else
            {
              paramValue = setting->getParamArray(j, i);
            }
            param_mix[i][j] = paramValue + CVmixer->getParamMix(i, j);
            if (param_mix[i][j] > 127)
            {
                param_mix[i][j] = 127;
            }
            else if (param_mix[i][j] < 0)
            {
                param_mix[i][j] = 0;
            }
        }
    }
    param_CV_mix_4B = CVmixer->getParamMix(3, 1);
    param_CV_mix_4A = CVmixer->getParamMix(3, 0);
    for (int i = 0; i < 2; i++)
    {
      gate_input[i] = trig_in_buffers[input_buff_tail][i];
      gate_input[i] = gateMixer->RoutedGateMix(gate_input[i], routingMap, i, previousOutput);
    }
}
