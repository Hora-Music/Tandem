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

///////////////////////////////////////////////////// Filling of the buffer used by the LFO scope ////////////////////////////////////////////

void fillScopeBuffer()
{
    int edit_channel = setting->getEditChannel();
    
    if (scope_mode == true && edit_channel == CHANNEL_A)
    {
       staticScopeBuffer [int(s_phase[edit_channel])] = 32 - (analog_in_buffers[input_buff_tail][5] >> 2) - 3;
    }
    else if( edit_channel == CHANNEL_A)
    {
        staticScopeBuffer [int(s_phase[edit_channel])] = (output_buffer_A_sample >> 7) - 3;
    }
    else
    {
        staticScopeBuffer [int(s_phase[edit_channel])] = (output_buffer_B_sample >> 7) - 3;
    }
}

///////////////////////////////////////////////////////////////// Process channel 1 ///////////////////////////////////////////////////////////

uint16_t processorCycle1()
{
  int pol1 = setting->getPolarity(0);
  trigInit_1 = 0;
  float shape1 = setting->getParamArray(0, 8);
  float trigMode1 = setting->getParamArray(0, 9);
  bool envGate1 = false;
  if (gate_input[0] > 0)
  {
     envGate1 = true;
  }
  uint16_t output = 0;
  float env1 = 0;
  uint8_t reset1 = 0;

  switch (setting->getModel_1())
  {
    case LFO :
    {
      if (utilities->triggerActive(gate_input[0], 0) || setting->get_reset(0) == 1)
      {
        if (scope_mode == false || s_phase[0] > 105)
        {
          reset1 = 1;
        }
      }
      if (setting->get_reset(0) == 1)
      {
        if (scope_mode == false || s_phase[0] > 105)
        {
          reset1 = 1;
        }
      }
      output = multiLFO[0]->getValue(param_mix[0][0], param_mix[1][0], false, 0.0, reset1, param_mix[2][0], 0);       
      s_phase[0] = multiLFO[0]->getShiftedPhase();
      switch (pol1)
      {
          case 0:
            GPIOA->regs->BSRR = 0b0000000000001000;
           break;
         case 1:
            GPIOA->regs->BRR = 0b0000000000001000;
           break;
      }
      
      phase[0] = multiLFO[0]->getPhase();
      t_pos[0] = (setting->getParamArray(0, LFO_TRIG_POS)) + (param_CV_mix_4A);
      if (t_pos[0] > 127)
      {
          t_pos[0] = 127;
      }
      if (t_pos[0] < 0)
      {
          t_pos[0] = 0;
      }
      if (s_phase[0] <= t_pos[0] + 2 && s_phase[0] >= t_pos[0] - 2)
      {
          trigInit_1 = 1;
      }
      else
      {
          trigInit_1 = 0;
      }
      setting->set_reset(0, false);
    }
    break;
    
    case ENVELOPE:
    {
      if (buttonValue[0] == true && setting->getEditChannel() == 0 && onSet && setting->getMainMenuOpened() == false && setting->isSaving() == false)
      {
            envGate1 = true;
      }
      env1 = ADSR[0]->getValue (envGate1, float(param_mix[0][0] / 127.0), float(param_mix[1][0] / 127.0), float(param_mix[2][0] / 127.0), float(param_mix[3][0] / 127.0), shape1 / 127.0, 0);
      rawEnvOut1 = env1; 
      output = 4095 - env1 * 4095;
      switch (pol1)
      {
         case 0:
            GPIOA->regs->BRR = 0b0000000000001000;
         break;
         case 1:
            GPIOA->regs->BSRR = 0b0000000000001000;
         break;
         case 2:
            GPIOA->regs->BSRR = 0b0000000000001000;
            output = -output/2 + 4095;
         break;
      }
      //output_A = 2055;
      if (trigMode1 < 42) // EOA
      {
          if (ADSR[0]->getState() == DECAY && (ADSR[0]->getDecayPhase() <= 0.0))
          {
              trigInit_1 = 1;
          }
      }
      else if (trigMode1 < 84) // EOD
      {
          if (ADSR[0]->getState() == SUSTAIN && ADSR[0]->getDecayPhase() != 0.0)
          {
              trigInit_1 = 1;
          }
      }
      else // EOR
      {
          if (ADSR[0]->getState() == REST && ADSR[0]->getReleasePhase() != 0.0)
          {
              trigInit_1 = 1;
          }
      }
    }
    break;
      
    case SEQUENCER:
    {
        const int paramOffset = 8;
        const int seqParamOffset = 71;
        const int numberOfParams = 7;
        //int mainPos = setting->getSeqNum(0);
        int mainPos = sequencer[0]->getPatternIndex();
        int floorParam = paramOffset + mainPos * numberOfParams;   
        uint8_t rootNote = setting->getParamArray(0, floorParam + 0) /10;
        uint8_t chord = setting->getParamArray(0, floorParam + 1) / 12;
        uint8_t oct = setting->getParamArray(0, floorParam + 2) / 12;
        uint8_t shift = setting->getParamArray(0, floorParam + 3) / 7;
        uint8_t order = setting->getParamArray(0, floorParam + 4) >> 2;
        uint8_t seqLength = setting->getParamArray(0, floorParam + 5) >> 3;
        uint8_t repeatParam = floor(setting->getParamArray(0, floorParam + 6) / 16); 
        bool extSync = false;
        bool loopMode = false;
        int seqOffset = seqParamOffset + mainPos;
        uint16_t rythmSeq = setting->getParamArray(0, seqOffset); 
        uint8_t patternIndexOffset = setting->getSeqNum(0);
        const int paramOffsetForClock = seqParamOffset + 16 + 16;
        bool activeRootNotes[8] = {false, false, false, false, false, false, false, false};
        for (int i = 0; i < 8; i ++)
        {
           if (setting->getParamArray(0,  paramOffset + i * numberOfParams) /10 != 0)
           {
              activeRootNotes[i] = true;
           }
        }
        if (output_buff_head - 1 >= 0)
        {
          if (reset_B[output_buff_head] == true && reset_B[output_buff_head - 1] == false)
          {
            sequencer[0]->reset(activeRootNotes);
          }
        }
        if (button_4_hold == true && onSet && setting->getCurrentMenu() == SEQUENCER)
        {
            sequencer[0]->reset(0);
            button_4_hold = false;
        }
        if (setting->getParamArray(0, paramOffsetForClock + 2) == true)
        {
           loopMode = true;
        }   
        sequencer[0]->setValues(patternIndexOffset, chord, repeatParam, extSync, rythmSeq, seqLength, oct, order, shift, loopMode, rootNote);
        output = sequencer[0]->processCV();
        if (utilities->triggerActive(gate_input[0], 0))
        {
          sequencer[0]->refresh(activeRootNotes);
        }
        trigInit_1 = sequencer[0]->processGate();
      }
      break;
      
      case CLASSIC_SEQUENCER:
      {
        GPIOA->regs->BRR = 0b0000000000001000;
        if (reset_A[output_buff_head] == true)
        {
           externSlideState[0] = true;
        }
        if (externSlideState[0] == true)
        {
           stepSequencer[0]->setSlide(1);
        }
        const int paramOffset = 8;
        const int seqParamOffset = 71;
        const int numberOfParams = 7;
        int seqOffset = seqParamOffset;
        int slideSeqOffset = seqParamOffset + 1;
        uint16_t rythmSeq = setting->getParamArray(0, seqOffset); 
        uint16_t slideSeq = setting->getParamArray(0, slideSeqOffset); 
        uint16_t gateModeSeq = setting->getParamArray(0, slideSeqOffset + 1);
        uint8_t notes[16];
        for (int i = 0; i < 8; i++)
        {
          int floorParam = paramOffset + i * numberOfParams;
          notes[i] = setting->getParamArray(0, floorParam + 0);
        }
        for (int i = 0; i < 8; i++)
        {
          int floorParam = paramOffset + i * numberOfParams;
          notes[i + 8] = setting->getParamArray(0, floorParam + 1);
        }
        uint8_t transpose = setting->getParamArray(0, paramOffset + 4);
        uint8_t length = setting->getParamArray(0, paramOffset + 5);
        uint8_t readMode = setting->getParamArray(0, paramOffset + 3);
        uint8_t clockDiv = setting->getParamArray(0, paramOffset + 6);
        stepSequencer[0]->setValues(clockDiv, gateModeSeq, slideSeq,  rythmSeq,  length,  transpose, readMode);
        stepSequencer[0]->setKbMode(setting->getKeyBoardMode(0));
        output = stepSequencer[0]->processCV();

        if (utilities->triggerActive(gate_input[0], 0))
        {
          externSlideState[0] = false;
          stepSequencer[0]->refresh(notes);
        }
        if (setting->getKeyBoardMode(0) == false)
        {
          trigInit_1 = stepSequencer[0]->processGate();
        }
        else
        {
          stepSequencer[setting->getEditChannel()]->forceNote(lastPlayedNote);
          stepSequencer[0]->processGate();
          trigInit_1 = isKeyPressed;
        }
      }
      break;
      
      case BASSLINE_ENVELOPE:
      {
        float accentLength = setting->getParamArray(0, 9) / 5.0;
        int accentHardness = setting->getParamArray(0, 8);
        float newWeight = 4 + (accentHardness / 1.4);
        accentFilter1.SetWeight(newWeight);
        if (utilities->triggerActive(gate_input[0], 0))
        {
             externAccentState[0] = false;
        } 
        float initLevel = 0.6;
        float accMult = 1.0 - initLevel;
        uint16_t accentState;
        float accentLevelKnob = float(param_mix[1][0] / 127.0);
        float accentLevel = 0.0;
        if (accentLevelKnob < 0.5)
        {
          accentLevel = accentLevelKnob * 2.0; 
        }
        else
        {
          accentLevel = 1.0 - (accentLevelKnob - 0.5) * 0.4;
          initLevel = 0.6 + (accentLevelKnob - 0.5) * 0.4;  
        }
        env1 = ADSR[0]->getValue (envGate1, float(param_mix[2][0] / 127.0), float(param_mix[3][0] / 256.0) + 0.5, 0.0, 0.0, 0.0, 0);
        float accentOuput = accentEnvelope[0]->getValue (envGate1, 0.0, accentLength / 127 + 0.5, 0.0, 0.0, 0.0, 0);
        env1 *= initLevel;
        float env_ = accentOuput;
        accentFilter1.Filter(env_);
        float filtredEnv = accentFilter1.Current() * accMult; 
        uint16_t accent_seq = setting->getParamArray(1, 74); 
        int chasePos = stepSequencer[1]->getSeqPos();
        uint16_t as = (accent_seq & (1 << chasePos)) >> chasePos;
        accentState = as;
        if (accentState == true && setting->getModel_2() == 3)
        {
          env1 += filtredEnv * accentLevel;
        } 
        if (reset_B[output_buff_head] == true)
        {
           externAccentState[0] = true;
        }
        if (externAccentState[0] == true)
        {
          env1 += filtredEnv * accentLevel;
        }
        if (env1 > 4095)
        {
          env1 = 4095;
        }
        output = 4095 - env1 * 4095;
    }
    break;
  }
  return output;
}

/////////////////////////////////////////////////////////////////// Process channel 2 /////////////////////////////////////////////////////////

uint16_t processorCycle2()
{
   int pol2 = setting->getPolarity(1);
   trigInit_2 = 0;
   float shape2 = setting->getParamArray(1, 8);
   float trigMode2 = setting->getParamArray(1, 9); 
   bool envGate2 = false;
   if (gate_input[1] > 0)
   {
       envGate2 = true;
   }
   uint16_t output = 0;
   float env2 = 0;
   uint8_t reset2 = 0;
   
   switch (setting->getModel_2())
   {
   case LFO :
   {
         if (utilities->triggerActive(gate_input[1], 1) || setting->get_reset(1) == 1)
         {
             reset2 = 1;
         }
         if (setting->get_reset(1) == 1)
         {
             reset2 = 1;
         }
         output = multiLFO[1]->getValue(param_mix[0][1] , param_mix[1][1], setting->getParamArray(1, LFO_SYNC), s_phase[0], reset2, param_mix[2][1], setting->getModel_1());
         switch (pol2)
        {
           case 0:
              GPIOA->regs->BSRR = 0b0000000001000000;
           break;
           case 1:
              GPIOA->regs->BRR = 0b0000000001000000;
           break;
        }
         s_phase[1] = multiLFO[1]->getShiftedPhase();
         phase[1] = multiLFO[1]->getPhase();
         t_pos[1] = (setting->getParamArray(1, LFO_TRIG_POS)) + param_CV_mix_4B;
         if (t_pos[1] > 127)
         {
             t_pos[1] = 127;
         }
         if (t_pos[1] < 0)
         {
             t_pos[1] = 0;
         }
         if (s_phase[1] <= t_pos[1] + 2 && s_phase[1] >= t_pos[1] - 2)
         {
             trigInit_2 = 1;
         }
         else
         {
             trigInit_2 = 0;
         }
         setting->set_reset(1, false);
   }
   break;
   case ENVELOPE:
   {
         if (buttonValue[0] == true && setting->getEditChannel() == 1 && onSet && setting->getMainMenuOpened() == false && setting->isSaving() == false)
         {
               envGate2 = true;
         }
         env2 = ADSR[1]->getValue (envGate2, float(param_mix[0][1] / 127.0), float(param_mix[1][1] / 127.0), float(param_mix[2][1]/ 127.0), float(param_mix[3][1] / 127.0), shape2 / 127.0, 0);
         rawEnvOut2 = env2; 
         output =  4095 - env2 * 4095;
         switch (pol2)
         {
           case 0:
              GPIOA->regs->BRR = 0b0000000001000000;
           break;
           case 1:
              GPIOA->regs->BSRR = 0b0000000001000000;
           break;
           case 2:
              GPIOA->regs->BSRR = 0b0000000001000000;
              output = -output/2 + 4095;
           break;
         }
         if (trigMode2 < 42) // EOA
         {
               if (ADSR[1]->getState() == DECAY && ADSR[1]->getDecayPhase() <= 0.0)
               {
                   trigInit_2 = 1;
               }
         }
         else if (trigMode2 < 84) // EOD
         {
               if (ADSR[1]->getState() == SUSTAIN && ADSR[1]->getDecayPhase() != 0.0)
               {
                   trigInit_2 = 1;
               }
         }
         else // EOR
         {
               if (ADSR[1]->getState() == REST && ADSR[1]->getReleasePhase() != 0.0)
               {
                   trigInit_2 = 1;
               }
         }
    }
    break;
    
    case SEQUENCER:
    {
         const int paramOffset = 8;
         const int seqParamOffset = 71;
         const int numberOfParams = 7;
         //int mainPos = setting->getSeqNum(0);
         int mainPos = sequencer[1]->getPatternIndex();
         int floorParam = paramOffset + mainPos * numberOfParams;   
         uint8_t rootNote = setting->getParamArray(1, floorParam + 0) /10;
         uint8_t chord = setting->getParamArray(1, floorParam + 1) / 12;
         uint8_t oct = setting->getParamArray(1, floorParam + 2) / 12;
         uint8_t shift = setting->getParamArray(1, floorParam + 3) / 7;
         uint8_t order = setting->getParamArray(1, floorParam + 4) >> 3;
         uint8_t seqLength = setting->getParamArray(1, floorParam + 5) >> 3;
         uint8_t repeatParam = floor(setting->getParamArray(1, floorParam + 6) / 16); 
         bool extSync = false;
         bool loopMode = false;
         int seqOffset = seqParamOffset + mainPos;
         uint16_t rythmSeq = setting->getParamArray(1, seqOffset); 
         uint8_t patternIndexOffset = setting->getSeqNum(1);
         const int paramOffsetForClock = seqParamOffset + 16 + 16;
         bool activeRootNotes[8] = {false, false, false, false, false, false, false, false};
         
         for (int i = 0; i < 8; i ++)
         {
            if (setting->getParamArray(1,  paramOffset + i * numberOfParams) /10 != 0)
            {
               activeRootNotes[i] = true;
            }
         }
         if (output_buff_head - 1 >= 0)
         {
           if (reset_A[output_buff_head] == true && reset_A[output_buff_head - 1] == false)
           {
             sequencer[1]->reset(activeRootNotes);
           }
         }
         if (button_4_hold == true && onSet && setting->getCurrentMenu() == SEQUENCER)
         {
             sequencer[1]->reset(0);
             button_4_hold = false;
         }
         if (setting->getParamArray(1, paramOffsetForClock + 2) == true)
         {
             loopMode = true;
         }   
         sequencer[1]->setValues(patternIndexOffset, chord, repeatParam, extSync, rythmSeq, seqLength, oct, order, shift, loopMode, rootNote);
         output = sequencer[1]->processCV();
         if (utilities->triggerActive(gate_input[1], 1))
         {
           sequencer[1]->refresh(activeRootNotes);
         }
         stepSequencer[1]->setKbMode(setting->getKeyBoardMode(1));
        if (setting->getKeyBoardMode(1) == false)
        {
          trigInit_2 = stepSequencer[1]->processGate();
        }
        else
        {
          //stepSequencer[1]->processGate();
          trigInit_2 = isKeyPressed;
        }
    }
    break;
    
    case CLASSIC_SEQUENCER:
    {
        GPIOA->regs->BRR = 0b0000000001000000;
        if (reset_B[output_buff_head] == true)
        {
           externSlideState[1] = true;
        }
        if (externSlideState[1] == true)
        {
          stepSequencer[1]->setSlide(1);
        }
        const int paramOffset = 8;
        const int seqParamOffset = 71;
        const int numberOfParams = 7;
        int seqOffset = seqParamOffset;
        int slideSeqOffset = seqParamOffset + 1;
        uint16_t rythmSeq = setting->getParamArray(1, seqOffset); 
        uint16_t slideSeq = setting->getParamArray(1, slideSeqOffset); 
        uint16_t gateModeSeq = setting->getParamArray(1, slideSeqOffset + 1);
        uint8_t notes[16];
        for (int i = 0; i < 8; i++)
        {
          int floorParam = paramOffset + i * numberOfParams;
          notes[i] = setting->getParamArray(1, floorParam + 0);
        }
        for (int i = 0; i < 8; i++)
        {
          int floorParam = paramOffset + i * numberOfParams;
          notes[i + 8] = setting->getParamArray(1, floorParam + 1);
        }
        uint8_t editSeqPos = setting->getSeqNum(1);
        uint8_t transpose = setting->getParamArray(1, paramOffset + 4);
        uint8_t length = setting->getParamArray(1, paramOffset + 5);
        uint8_t readMode = setting->getParamArray(1, paramOffset + 3);
        uint8_t clockDiv = setting->getParamArray(1, paramOffset + 6);
        stepSequencer[1]->setValues(clockDiv, gateModeSeq, slideSeq,  rythmSeq,  length,  transpose, readMode);
        output = stepSequencer[1]->processCV();
        if (utilities->triggerActive(gate_input[1], 1))
        {
          externSlideState[1] = false;
          stepSequencer[1]->refresh(notes);
        }
        if (setting->getKeyBoardMode(1) == false)
        {
          trigInit_2 = stepSequencer[1]->processGate();
        }
        else
        {
          stepSequencer[1]->forceNote(lastPlayedNote);
          stepSequencer[1]->processGate();
          trigInit_2 = isKeyPressed;
        }
        trigInit_2 = stepSequencer[1]->processGate();
    }
    break;
    
    case BASSLINE_ENVELOPE:
    {
        if (utilities->triggerActive(gate_input[1], 1))
        {
             externAccentState[1] = false;
        } 
        float accentLength = setting->getParamArray(1, 9) / 5.0;
        int accentHardness = setting->getParamArray(1, 8);
        float newWeight = 4 + (accentHardness / 1.4);
        accentFilter2.SetWeight(newWeight);
        float initLevel = 0.6;
        float accMult = 1.0 - initLevel;
        uint16_t accentState;
        float accentLevelKnob = float(param_mix[1][1] / 127.0);
        float accentLevel = 0.0;
        if (accentLevelKnob < 0.5)
        {
          accentLevel = accentLevelKnob * 2.0; 
        }
        else
        {
          accentLevel = 1.0 - (accentLevelKnob - 0.5) * 0.4;
          initLevel = 0.6 + (accentLevelKnob - 0.5) * 0.8; 
        }
        
        env2 = ADSR[1]->getValue (envGate2, float(param_mix[2][1] / 127.0), float(param_mix[3][1] / 256.0) + 0.5, 0.0, 0.0, 0.0, 0);
        float accentOuput = accentEnvelope[1]->getValue (envGate2, 0.0, accentLength / 127 + 0.5, 0.0, 0.0, 0.0, 0);
        env2 *= initLevel;
        float env_ = accentOuput;
        accentFilter2.Filter(env_);
        float filtredEnv = accentFilter2.Current() * accMult; 
        //if (setting->getModel_1() == CLASSIC_SEQUENCER)
        //{  
          uint16_t accent_seq = setting->getParamArray(0, 74); 
          int chasePos = stepSequencer[0]->getSeqPos();
          uint16_t as = (accent_seq & (1 << chasePos)) >> chasePos;
          accentState = as;
          
          if ((accentState == true  && setting->getModel_1() == 3))
          {
             env2 += filtredEnv * accentLevel;
          } 
          if (env2 > 4095)
          {
            env2 = 4095;
          }
        //}
        if (reset_A[output_buff_head] == true)
        {
           externAccentState[1] = true;
        }
        if (externAccentState[1] == true)
        {
          env2 += filtredEnv * accentLevel;
        }
        output = 4095 - env2 * 4095;
     }
     break;
    }
    return output;
}
