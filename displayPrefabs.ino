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

//////////////////////////////////////////////// Display functions used in displayMenus.ino //////////////////////////////////////////

void drawBufferWarning()
{
    if (input_buff_overload)
    {
      if (frameCount % 50 == 0)
      {
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(5, 15);
        display.setTextColor(WHITE);
        display.println("in_overload");
        display.display();
      }
    }
    if (output_buff_overload)
    {
      if (frameCount % 50 == 0)
      {
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(15, 15);
        display.setTextColor(WHITE);
        display.println("in_overload");
        display.display();
      }
    }
}

void drawRoutingIcone()
{
     display.drawCircle(108, 6, 3, WHITE);
     display.drawCircle(118, 6, 3, WHITE);
     display.drawCircle(118, 16, 3, WHITE);
     display.drawCircle(108, 16, 3, WHITE);
     display.drawLine(108, 6, 118, 16, WHITE);
     //display.drawRect(102, 1, 25, 24, WHITE);
}
void displaySeqTempo(int channel)
{
  display.setCursor(11, 24);
  display.print(setting->getParamArray(channel, 106));
}

void displaySeqParams(int channel)
{
  /*display.drawTriangle( 10, 4, 5, 7, 5, 1, WHITE);
  display.drawLine( 11, 0, 11, 8, WHITE);*/
  /*display.setTextColor(WHITE);
  const int paramOffset = 8;
  const int seqParamOffset = 71;
  const int numberOfParams = 7;
  int mainPos = sequencer[channel]->getPatternIndex();
  display.drawRect(mainPos * 11, 9, 10, 0, WHITE);
  uint8_t pitchPos[16];
  String nums = "1234567812345678";
  display.setCursor(94, 0);
  if (setting->getOctMode(channel) == false)
  {
    display.print("CHD->");
  }
  else
  {
    display.print("OCT->");
  }
  String notes[14] = {"/","A", "Bb", "B", "C", "Db","D", "Eb", "E", "F", "Gb", "G", "Ab"};
  String scales[11] = {"MIN", "MAJ", "MIN7", "MAJ7", "7","SUS4", "ADD4", "DIM", "AUG", "POW", "OCT"};
  int floorParam = paramOffset + mainPos * numberOfParams;
  uint8_t note = setting->getParamArray(channel, floorParam + 0) /10;
  uint8_t choord = setting->getParamArray(channel, floorParam + 1) / 12;
  uint8_t oct = setting->getParamArray(channel, floorParam + 2) / 12;
  uint8_t shift = setting->getParamArray(channel, floorParam + 3) >> 3;
  uint8_t length = setting->getParamArray(channel, floorParam + 5) >> 3;
  uint8_t repeat = floor(setting->getParamArray(channel, floorParam + 6) / 16);
  for (int i = 0; i < 8; i++)
  {
      display.setCursor(i * 11 + 1, 0);
      display.print(nums[i]);
  }
  display.setTextSize(2);
  display.setCursor(2, 12);
  String currentNote = notes[note];
  display.print(currentNote[0]);
  display.setTextSize(1);
  if (currentNote.length() > 1)
  {
    display.print(currentNote[1]);
    display.setCursor(22, 16);
  }
  else
  {
    display.setCursor(17, 16);
  }
  display.print(scales[choord]);
  display.setCursor(50, 16);
  display.print("OCT:");
  display.setCursor(77, 16);
  display.print(oct);
  int seqEditIndex = (setting->getSeqIndex(channel));
  int seqOffset = seqParamOffset + mainPos;
  uint16_t rythmSeq = setting->getParamArray(channel, seqOffset); 
  const int paramOffsetForClock = seqParamOffset + 16 + 16;
  for (int i = 0; i < 16; i++)
  {
    uint16_t shitedSeqPos = i + shift;
    if ( shitedSeqPos > length)
    {
        shitedSeqPos =  shitedSeqPos - (length + 1);
    }
    pitchPos[i] = sequencer[channel]->getNoteOrderNum(shitedSeqPos);
    uint16_t actBit = (rythmSeq & (1 << shitedSeqPos)) >> shitedSeqPos;
    if (i < length + 1)
    {
      display.drawRect(i * 8, 37, 8, 8, WHITE);
    
      if (actBit == 1)
      {
        display.fillRect(i * 8 + 2, 37, 6, 6, WHITE);
      }
      if (i != sequencer[channel]->getSeqPos())
      {
        display.drawLine(i * 8 + 1, 36 - pitchPos[i], i * 8 + 8, 36 - pitchPos[i], WHITE);
      }
      else
      {
        display.drawRect(i * 8 + 3, 36 - pitchPos[i] - 2, 4, 2, WHITE);
      }
    }
  }
  display.drawLine(seqEditIndex * 8 , 46, seqEditIndex * 8 + 8, 46, WHITE);
  for (int i = 0; i < 8; i++)
  {
    display.drawRect(i * 16, 50, 16, 4, WHITE);
    if (i <= repeat)
    {
      display.fillRect(i * 16 + 2, 51, 14, 2, WHITE);
    }
  }
  if (setting->getSubParam(channel) == 0)
  {
      display.setCursor(2, 57);
      display.print("<-SHIFT");
  }
  else if (setting->getSubParam(channel) == 1)
  {
      display.setCursor(2, 57);
      display.print("<-ORDER");
  }
  else if (setting->getSubParam(channel) == 2)
  {
      display.setCursor(2, 57);
      display.print("<-LENGTH");
  }
  else if (setting->getSubParam(channel) == 3)
  {
      display.setCursor(2, 57);
      display.print("<-REPEAT");
  }
  if (setting->getParamArray(channel, paramOffsetForClock + 2) == true)
  {
      display.setCursor(103, 15);
      display.print("Loop");
  }
  /*if (setting->getParamArray(channel, paramOffsetForClock + 1) == true)
  {
      display.setCursor(64, 57);
      display.print("Play");
      setting->setSeqNum(channel, mainPos);
  }
  else
  {
      display.setCursor(64, 57);
      display.print("Edit");
  }*/
  /*int repeatNumPosX = sequencer[channel]->getRepeatNum() * 16;
  display.drawRect(repeatNumPosX + 3, 51, 12, 1, BLACK);
  if (channel == 0)
  {
    display.fillCircle(58, 60, 3, WHITE);
    display.drawCircle(72, 60, 3, WHITE);
  }
  else
  {
    display.drawCircle(58, 60, 3, WHITE);
    display.fillCircle(72, 60, 3, WHITE);
  }*/
}

void displayClassicSeqParams(int channel)
{
  String noteNames[13] = {"C", "Db", "D", "Eb", "E","F", "Gb", "G", "Ab", "A", "Bb", "B"};
  display.setTextColor(WHITE);
  const int paramOffset = 8;
  const int seqParamOffset = 71;
  const int numberOfParams = 7;
  int seqOffset = seqParamOffset;
  int slideSeqOffset = seqParamOffset + 1;
  uint16_t rythmSeq = setting->getParamArray(channel, seqOffset); 
  uint16_t slideSeq = setting->getParamArray(channel, slideSeqOffset); 
  uint16_t gateModeSeq = setting->getParamArray(channel, slideSeqOffset + 1); 
  uint16_t rythmSeqB[16]; 
  uint16_t slideSeqB[16]; 
  uint16_t gateModeSeqB[16]; 
  for (uint8_t j = 0; j < 16; j++)
  { 
    uint16_t rs = (rythmSeq & (1 << j)) >> j;
    rythmSeqB[j] = rs;
    uint16_t ss  = (slideSeq & (1 << j)) >> j;
    slideSeqB[j] = ss;
    uint16_t gms  = (gateModeSeq & (1 << j)) >> j;
    gateModeSeqB[j] = gms;
  }
  uint8_t notes[16];
  for (int i = 0; i < 8; i++)
  {
    int floorParam = paramOffset + i * numberOfParams;
    notes[i] = setting->getParamArray(channel, floorParam + 0);
  }
  for (int i = 0; i < 8; i++)
  {
    int floorParam = paramOffset + i * numberOfParams;
    notes[i + 8] = setting->getParamArray(channel, floorParam + 1);
  }
  uint8_t editSeqPos = setting->getSeqNum(channel);
  uint8_t transpose = setting->getParamArray(channel, paramOffset + 4);
  uint8_t length = setting->getParamArray(channel, paramOffset + 5);
  display.setCursor(11, 0);
  //display.print(CV_input[1]);
  display.print("POS: ");
  display.setCursor(35, 0);
  display.print(editSeqPos + 1);
  display.setCursor(70, 0);
  display.print("NOTE:");
  display.setCursor(100, 0);
  display.print(noteNames[(notes[editSeqPos] + transpose) % 12] +  int(floor(notes[editSeqPos] + transpose) / 12));
  int chasePos = stepSequencer[channel]->getSeqPos();
  float ratio = 16.0 / float (length + 1);
  for (int i = 0; i < 16; i++)
  {
    if (i <= length)
    {
      display.drawRect(i * 8 * ratio , 10, 8 * ratio, 6, WHITE);
      if (slideSeqB[i] == 1)
      {
          display.drawLine(i * 8 * ratio + 7 * ratio, 53, i * 8 * ratio + 6 * ratio, 51, WHITE);
      }
      if (rythmSeqB[i] == 1)
      {
        display.fillRect(i * 8 * ratio + 2 * ratio, 11, 4 * ratio, 3, WHITE);
        if (gateModeSeqB[i] == 1)
        {
            display.drawLine(i * 8 * ratio , 18, i * 8 * ratio + 8 * ratio, 18, WHITE);
            display.drawLine(i * 8 * ratio , 17, i * 8 * ratio + 8 * ratio, 17, WHITE);
        }
        else
        {
            display.drawLine(i * 8 * ratio , 18, i * 8 * ratio + 3 * ratio, 18, WHITE);
            display.drawLine(i * 8 * ratio , 17, i * 8 * ratio + 3 * ratio, 17, WHITE);
        }
      }
      
      if (i != chasePos)
      {
        display.fillRect(i * 8 * ratio  + 2 * ratio, 23 + 24 - notes[i] / 1.35, 4 * ratio, notes[i] / 1.35 + 2, WHITE);
        if (i == editSeqPos)
        {
          //display.fillRect(i * 8  * ratio + 3 * ratio, 25, 2 * ratio, 22, WHITE);
          display.drawRect(i * 8 * ratio, 21, 8 * ratio, 30, WHITE);
        }
      }
      else
      {
        display.fillRect(i * 8 * ratio, 21, 8 * ratio, 30, WHITE);
        display.drawRect(i * 8 * ratio, 21, 8 * ratio, 30, BLACK);
        display.fillRect(i * 8 * ratio  + 2 * ratio, 23 + 24 - notes[i] / 1.35, 4 * ratio, notes[i] / 1.35 + 2, BLACK);
        if (i == editSeqPos)
        {
          //display.fillRect(i * 8  * ratio + 3 * ratio, 25, 2 * ratio, 22, BLACK);
          display.drawRect(i * 8 * ratio, 21, 8 * ratio, 30, WHITE);
        }
      }
    }
  }
  display.setCursor(59, 56);

  // for debug purpose --> display.print(stepSequencer[channel]->getDacTableAt(notes[0]));
  // display.print("LENGTH:");
  /*if (readMode == 0)
  {
    display.print("FWD");
  }
  else if (readMode == 1)
  {
    display.print("BWD");
  }
  else if (readMode == 2)
  {
    display.print("RND");
  }*/
  display.setCursor(5, 56);
  display.print("ROOT:");
  display.setCursor(35, 56);
  display.print(transpose);
  display.setCursor(100, 56);
  
  display.print(length + 1);
}

void drawRoutingMenuFrame(int dest, int source)
{
    int dist = 28;
    display.fillCircle(22 + dest * dist, 19, 9, WHITE);
    display.fillCircle(22 + source * dist, 52, 9, WHITE);
    for (int i = 0; i < 4; i++)
    {
        display.drawCircle(22 + i * dist, 19.0, 8.0, WHITE);
        display.drawCircle(22 + i * dist, 19.0, 5.0, BLACK);
        display.drawCircle(22 + i * dist, 52.0, 8.0, WHITE);
        display.drawCircle(22 + i * dist, 52.0, 5.0, BLACK);
    }
    //display.drawCircle(22 + dest * dist, 19.0, 10.0, BLACK);
    display.fillCircle(22 + dest * dist, 19.0, 5.0, BLACK);
    //display.drawCircle(22 + source * dist, 52.0, 10.0, BLACK);
    display.fillCircle(22 + source * dist, 52.0, 5.0, BLACK);
}
void drawSavingIcone()
{
        int x_offset = 0;
        int y_offset = 0;
        display.drawLine( 112 + x_offset, 2 + y_offset, 122 + x_offset, 2 + y_offset, WHITE);
        display.drawLine( 122 + x_offset, 2 + y_offset, 126 + x_offset, 6 + y_offset, WHITE);
        display.drawLine( 126 + x_offset, 6 + y_offset, 126 + x_offset, 16 + y_offset, WHITE);
        display.drawLine( 126 + x_offset, 16 + y_offset, 112 + x_offset, 16 + y_offset, WHITE);
        display.drawLine(  112 + x_offset, 16 + y_offset, 112 + x_offset, 2 + y_offset, WHITE);
        display.drawLine( 112 + x_offset, 2 + y_offset, 120 + x_offset, 2 + y_offset, WHITE);
        display.drawLine( 120 + x_offset, 2 + y_offset, 120 + x_offset, 6 + y_offset, WHITE);
        display.drawLine( 120 + x_offset, 6 + y_offset, 114 + x_offset, 6 + y_offset, WHITE);
        display.drawLine( 114 + x_offset, 6 + y_offset, 114 + x_offset, 2 + y_offset, WHITE);
}
void drawCVMenu(String param1,String param2, int level1, int level2)
{
      char PARAM_CHAR1 [5] = "CV 1";
      char PARAM_CHAR2 [5] = "CV 2";
     char INT_CHAR [8] = "level :";
      display.setCursor(11, 3 - 3 );
      display.print(PARAM_CHAR1);
      display.setCursor( 73, 3 - 3 );
      display.print(PARAM_CHAR2);
      display.setCursor(11, 23 - 3 );
      display.print(param1);
      display.setCursor(73, 23 - 3 );
      display.print(param2);
      display.setCursor(11, 48 - 3 );
      display.print(INT_CHAR);
      display.setCursor(73, 48 - 3 );
      display.print(INT_CHAR);
      display.setCursor(11, 56 - 3);
      display.print(level1);
      display.setCursor(73, 56 - 3 );
      display.print(level2);
}

void drawCommonMenuFrames(int channel)
{
      int y_offset = 11;
      display.drawTriangle( 10.0, 4.0, 5.0, 7.0, 5.0, 1.0, WHITE);
      //display.drawLine( 4.0, 0.0, 4.0, 8.0, WHITE);
      //display.drawLine( 0 , 64 - y_offset, 128, 64 - y_offset, WHITE);
      /*if (channel == 0)
      {
          display.fillCircle( 6.0, 59.0, 3.0, WHITE);
          display.drawCircle( 124.0, 59.0, 3.0, WHITE);
      }
      else
      {
          display.fillCircle( 124.0, 59.0, 3.0, WHITE);
          display.drawCircle( 6.0, 59.0, 3.0, WHITE);
      }*/
}

void drawPot(int radius, int coordCircle1_x, int coordCircle1_y, int paramValue, String param_name, int textOffset)
{
  float offsetAngle = 0.11; 
  float attack_radian = (((127 - paramValue) / 127.0) * 0.78) + offsetAngle;
  display.drawCircle(coordCircle1_x, coordCircle1_y, radius, WHITE);
  float sinRaw = sin(attack_radian * 6.28318530718);
  float cosRaw = cos(attack_radian * 6.28318530718);
  float p1_x = coordCircle1_x + (sinRaw) * radius * 0.9;
  float p1_y = coordCircle1_y + (cosRaw) * radius * 0.9;
  float p2_x = coordCircle1_x + (sinRaw) * radius * 0.2;
  float p2_y = coordCircle1_y + (cosRaw) * radius * 0.2;
  display.drawLine(p1_x, p1_y, p2_x, p2_y, WHITE);
  display.setCursor(textOffset + coordCircle1_x - (param_name.length() /2) * 6, coordCircle1_y + radius * 1.35);
  display.print(param_name);
  display.setCursor(coordCircle1_x - (String(paramValue).length() /2) * 6, (coordCircle1_y + radius * 1.35) + 9);
  display.print(paramValue);
  // uncomment for style 2
  /*float sinRawB = sin((attack_radian + 0.15) * 6.28318530718);
  float cosRawB = cos((attack_radian + 0.15) * 6.28318530718);
  float sinRawC = sin((attack_radian - 0.15) * 6.28318530718);
  float cosRawC = cos((attack_radian - 0.15) * 6.28318530718);
  float p1_xB = coordCircle1_x + (sinRawB) * radius * 0.6;
  float p1_yB = coordCircle1_y + (cosRawB) * radius * 0.6;
  float p2_xB = coordCircle1_x + (sinRawC) * radius * 0.6;
  float p2_yB = coordCircle1_y + (cosRawC) * radius * 0.6;
  display.drawLine(p1_xB, p1_yB, p2_xB, p2_yB, WHITE);*/
  
}
void drawDualPot(int radius, int coordCircle1_x, int coordCircle1_y, int paramValue, String param_name1, String param_name2,int textOffset)
{
  float offsetAngle = 0.11; 
  float attack_radian = (((127 - paramValue) / 127.0) * 0.78) + offsetAngle;
  display.drawCircle(coordCircle1_x, coordCircle1_y, radius, WHITE);
  float sinRaw = sin(attack_radian * 6.28318530718);
  float cosRaw = cos(attack_radian * 6.28318530718);
  float p1_x = coordCircle1_x + (sinRaw) * radius * 0.9;
  float p1_y = coordCircle1_y + (cosRaw) * radius * 0.9;
  float p2_x = coordCircle1_x + (sinRaw) * radius * 0.2;
  float p2_y = coordCircle1_y + (cosRaw) * radius * 0.2;
  display.drawLine(p1_x, p1_y, p2_x, p2_y, WHITE);
  if (paramValue <= 63)
  {
    display.setCursor(textOffset + coordCircle1_x - ( param_name1.length() /2) * 6, coordCircle1_y + radius * 1.35);
    display.print(param_name1);
    display.setCursor(coordCircle1_x - (String(paramValue).length() /2) * 6, (coordCircle1_y + radius * 1.35) + 9);
    display.print(paramValue);
  }
  else
  {
    display.setCursor(textOffset + coordCircle1_x - ( param_name2.length() /2) * 6, coordCircle1_y + radius * 1.35);
    display.print(param_name2);
    display.setCursor(coordCircle1_x - (String(paramValue - 63).length() /2) * 6, (coordCircle1_y + radius * 1.35) + 9);
    display.print(64 - (paramValue - 63));
  }
}
void drawAccentSeq(int channel)
{
  int paramOffset = 8;
  if (channel == 0)
  {
    uint16_t seq = setting->getParamArray(1, 71); 
    uint16_t accent_seq = setting->getParamArray(1, 74); 
    uint16_t seqB[16]; 
    uint16_t accentSeqB[16];
    uint8_t length = setting->getParamArray(1, paramOffset + 5);
    float ratio = 16.0 / float (length + 1);
    if (setting->getModel_2() == 3)
    {  
      int chasePos = stepSequencer[1]->getSeqPos();
        for (uint8_t j = 0; j < 16; j++)
        { 
          uint16_t rs = (seq & (1 << j)) >> j;
          seqB[j] = rs;
          uint16_t as = (accent_seq & (1 << j)) >> j;
          accentSeqB[j] = as;
        }
        uint8_t editSeqPos = setting->getSeqNum(0);
        display.drawRect(editSeqPos * 8 * ratio , 2, 8 * ratio, 6, WHITE);
          for (int i = 0; i < 16; i++)
          {
            if (i <= length)
            {
              display.drawRect(i * 8 * ratio , 10, 8 * ratio, 6, WHITE);
              if (seqB[i] == 1)
              {
                  display.fillRect(i * 8 * ratio + 2 * ratio, 11, 4 * ratio, 3, WHITE);
                  if (i == chasePos)
                  {
                    display.fillRect(i * 8 * ratio + 2 * ratio, 11, 4 * ratio, 3, BLACK);
                  }
              }
              else
              {
                  if (i == chasePos)
                  {
                    display.fillRect(i * 8 * ratio + 2 * ratio, 11, 4 * ratio, 3, WHITE);
                  }
              }
              if (accentSeqB[i] == true)
              {
                  display.fillRect(i * 8 * ratio + 2 * ratio, 4, 4 * ratio, 2, WHITE);
              }
            }
          }
    }
    else
    {
      display.setCursor(1, 1);
      display.print("Use a sequencer on");
      display.setCursor(1, 10);
      display.print("ch 2 for accent's seq");
    }
  }
  else if (channel == 1)
  {
    uint8_t length = setting->getParamArray(0, paramOffset + 5);
    float ratio = 16.0 / float (length + 1);
    uint16_t seq = setting->getParamArray(0, 71); 
    uint16_t accentSeqB[16];
    uint16_t accent_seq = setting->getParamArray(0, 74);
    uint16_t seqB[16]; 
    if (setting->getModel_1() == 3)
    {
        int chasePos = stepSequencer[0]->getSeqPos();
        for (uint8_t j = 0; j < 16; j++)
        { 
          uint16_t rs = (seq & (1 << j)) >> j;
          seqB[j] = rs;
          uint16_t as = (accent_seq & (1 << j)) >> j;
          accentSeqB[j] = as;
        }
        uint8_t editSeqPos = setting->getSeqNum(1);
        display.drawRect(editSeqPos * 8 * ratio , 2, 8 * ratio, 6, WHITE);
        for (int i = 0; i < 16; i++)
        {
          if (i <= length)
          {
            display.drawRect(i * 8 * ratio , 10, 8 * ratio, 6, WHITE);
            if (seqB[i] == 1)
            {
                display.fillRect(i * 8 * ratio + 2 * ratio, 11, 4 * ratio, 3, WHITE);
                if (i == chasePos)
                {
                  display.fillRect(i * 8 * ratio + 2 * ratio, 11, 4 * ratio, 3, BLACK);
                }
            }
            else
            {
               if (i == chasePos)
               {
                 display.fillRect(i * 8 * ratio + 2 * ratio, 11, 4 * ratio, 3, WHITE);
               }
            }
            if (accentSeqB[i] == 1)
            {
                  display.fillRect(i * 8 * ratio + 2 * ratio, 4, 4 * ratio, 2, WHITE);
            }
          }
        }
    }
    else
    {
      display.setCursor(1, 1);
      display.print("Use a sequencer on");
      display.setCursor(1, 10);
      display.print("ch 1 for accent's seq ");
    }
  }
}

void drawADSR( float attack, float decay, float sustain, float release, float attackPhase, float decayPhase, float releasePhase, float shape, int envelopeState, int channel, float outA, float outB, int trigMode)
{
      int y_offset = 16;
      float attackSize = attack / 3.0;
      float decaySize = decay/ 3.0;
      float releaseSize = release / 3.0;
      int chasePosX = 0.0;
      int chasePosY = 0.0;
      if(envelopeState == ATTACK)
      {
          chasePosX = attackPhase * 32.0;
      }
      else if(envelopeState == DECAY)
      {
          chasePosX = decayPhase * 32.0 + attackSize;
      }
      else if(envelopeState == SUSTAIN)
      {
          chasePosX = attackSize + decaySize;
      }
      else if(envelopeState == RELEASE)
      {
          chasePosX = attackSize + decaySize + releasePhase * 32.0;
      }
      if (channel == CHANNEL_A)
      {
          chasePosY = (outA * 6.4) + y_offset;
      }
      else if (channel == CHANNEL_B)
      {
          chasePosY = (outB * 6.4) + y_offset;
      }
      //display.drawLine( chasePosX, 16 , chasePosX, 48, WHITE);

      if (trigMode < 42)
      {
          display.drawLine( attackSize, 16 , attackSize, 48, WHITE);
      }
      else if (trigMode < 84)
      {
          display.drawLine( attackSize + decaySize, 16 , attackSize + decaySize, 48, WHITE);
      }
      else
      {
          display.drawLine( attackSize + decaySize + releaseSize, 16 , attackSize + decaySize + releaseSize, 48, WHITE);
      }
      display.fillRect( chasePosX - 2, 64.0- chasePosY - 3, 5, 5, WHITE);
      for (int i = 0; i < 16; i++)
      {
          display.drawLine( attackSize + 1, (i * 2) + y_offset, attackSize + 1, (i * 2) + y_offset + 1, WHITE);
          display.drawLine( attackSize + decaySize + 1, (i * 2) + y_offset, attackSize + decaySize + 1, (i * 2) + y_offset + 1, WHITE);
      }
      for (int i = 0; i < attackSize; i++)
      {
          float attackPhase = i / attackSize;
          float expPhase = (1.0 - attackPhase) * (1.0 - attackPhase);
          float invPhase = 1.0 - attackPhase;
          float finalPhase = shape * invPhase + (1.0 - shape) * expPhase;
          finalPhase = 1.0 - finalPhase;
          int attackPhaseScaled = finalPhase * 32.0;
          display.drawLine( i, 32 - attackPhaseScaled + y_offset, i + 1, 32 - attackPhaseScaled + y_offset, WHITE);
      }
      for (int i = 0; i < decaySize; i++)
      {
          float decayPhase = i / decaySize;
          float decayExpPhase = (1.0 - decayPhase) * ((1.0 - decayPhase));
          float decayInvPhase = 1.0 - decayPhase;
          float decayfinalPhase = shape * decayInvPhase + (1.0 - shape) * decayExpPhase;
          decayfinalPhase = 1.0 - decayfinalPhase;
          float decayValue = 1.0 - decayfinalPhase;
          float deltaDecay = 1.0 - (sustain / 127.0);
          decayValue *= deltaDecay;
          decayValue += sustain / 129.0;
          int decayPhaseScaled = decayValue * 32.0;
          display.drawLine( i + attackSize, 32 - decayPhaseScaled + y_offset, i + attackSize + 1, 32 - decayPhaseScaled + y_offset, WHITE);
      }
      for (int i = 0; i < releaseSize; i++)
      {
          float releasePhase = i / releaseSize;
          float releaseExpPhase = (1.0 - releasePhase) * ((1.0 - releasePhase));
          float releaseInvPhase = 1.0 - releasePhase;
          float releasefinalPhase = shape * releaseInvPhase + (1.0 - shape) * releaseExpPhase;
          float releaseValue = 1.0 - releasefinalPhase;
          float deltarelease = sustain / 127.0;
          releaseValue *= deltarelease;
          releaseValue = sustain / 129.0 - releaseValue;
          int releasePhaseScaled = releaseValue * 32.0;
          display.drawLine( i + attackSize + decaySize, 32 - releasePhaseScaled + y_offset, i  + attackSize + decaySize + 1, 32 - releasePhaseScaled + y_offset, WHITE);
      }
}

void draw_icone(int posX, int posY, int model,  int color)
{
  if (model == 0)
  {
    /*posX += 1;
    posY -= 9;
    display.drawLine(posX + 0, posY + 9, posX + 1, posY + 5, color);
    display.drawLine(posX + 1, posY + 5, posX + 2, posY + 3, color);
    display.drawLine(posX + 2, posY + 3, posX + 3, posY + 2, color);
    display.drawLine(posX + 3, posY + 2, posX + 5, posY + 1, color);
    display.drawLine(posX + 5, posY + 1, posX + 9, posY + 0, color);
    display.drawLine(posX + 9, posY + 0, posX + 13, posY + 1, color);
    display.drawLine(posX + 13, posY + 1, posX + 15, posY + 3, color);
    display.drawLine(posX + 15, posY + 3, posX + 16, posY + 4, color);
    display.drawLine(posX + 16, posY + 4, posX + 17, posY + 6, color);
    display.drawLine(posX + 17, posY + 6, posX + 18, posY + 9, color);
    posX += 18;
    posY += 20;
    display.drawLine(posX + 18, posY - 9, posX + 17, posY - 5, color);
    display.drawLine(posX + 17, posY - 5, posX + 16, posY - 3, color);
    display.drawLine(posX + 16, posY - 3, posX + 15, posY - 2, color);
    display.drawLine(posX + 15, posY - 2, posX + 13, posY - 1, color);
    display.drawLine(posX + 13, posY - 1,posX + 9 , posY - 0, color);
    display.drawLine(posX + 9, posY - 0,posX + 5 , posY - 1, color);
    display.drawLine(posX + 5, posY - 1,posX + 3 , posY - 3, color);
    display.drawLine(posX + 3, posY - 3,posX + 2 , posY - 4, color);
    display.drawLine(posX + 2, posY - 4,posX + 1 , posY - 6, color);
    display.drawLine(posX + 1, posY - 6,posX + 0 , posY - 9, color);*/
    // uncomment for style 2
    posY += 1;
    display.drawLine(posX, posY, posX+1, posY + 3, color);
    display.drawLine(posX+2, posY+3, posX+3, posY + 5, color);
    display.drawLine(posX+4, posY+5, posX+5, posY + 7, color);
    display.drawLine(posX+6, posY+7, posX+7, posY + 8, color);
    display.drawLine(posX+8, posY+8, posX+9, posY + 8, color);
    display.drawLine(posX+10, posY+8, posX+11, posY + 8, color);
    display.drawLine(posX+12, posY+8, posX+13, posY + 7, color);
    display.drawLine(posX+14, posY+7, posX+15, posY + 5, color);
    display.drawLine(posX+16, posY+5, posX+17, posY + 3, color);
    display.drawLine(posX+18, posY+3, posX+19, posY + 0, color);
    display.drawLine(posX+20, posY + 0, posX+21, posY - 3, color);
    display.drawLine(posX+22, posY-3, posX+23, posY - 5, color);
    display.drawLine(posX+24, posY-5, posX+25, posY - 7, color);
    display.drawLine(posX+26, posY-7, posX+27, posY - 8, color);
    display.drawLine(posX+28, posY-8, posX+29, posY - 8, color);
    display.drawLine(posX+30, posY-8, posX+31, posY - 8, color);
    display.drawLine(posX+32, posY-8, posX+33, posY - 7, color);
    display.drawLine(posX+34, posY-7, posX+35, posY - 5, color);
    display.drawLine(posX+36, posY-5, posX+37, posY - 3, color);
    display.drawLine(posX+38, posY-3, posX+39, posY - 0, color);
  }
  else if (model == 1)
  {
    display.drawLine(posX + 3, posY + 8, posX+11, posY -8, color);
    display.drawLine(posX + 11, posY - 8, posX + 18, posY - 1, color);
    display.drawLine(posX + 18, posY - 1, posX + 26, posY - 1, color);
    display.drawLine(posX + 26, posY - 1, posX + 35, posY + 8, color);
  }
  else if (model == 2)
  {
    display.drawLine(posX, posY , posX + 5, posY, color);
    display.drawLine(posX + 5, posY + 5, posX + 15, posY +5, color);
    display.drawLine(posX + 15, posY - 6, posX + 19, posY - 6, color);
    display.drawLine(posX + 19, posY + 1, posX + 26, posY + 1, color);
    display.drawLine(posX + 26, posY  + 8, posX + 40, posY + 8, color);
  }
  else if (model == 3)
  {
    display.fillRect(posX + 1, posY + 10 - 8, 3, 8, color);
    display.fillRect(posX + 6, posY + 10 - 4, 3, 4, color);
    display.fillRect(posX + 11, posY + 10 - 10, 3, 10, color);
    display.fillRect(posX + 16, posY + 10 - 12, 3, 12, color);
    display.fillRect(posX + 21, posY + 10 - 18, 3, 18, color);
    display.fillRect(posX + 26, posY + 10 - 15, 3, 15, color);
    display.fillRect(posX + 31, posY + 10 - 8, 3, 8, color);
    display.fillRect(posX + 36, posY + 10 - 13, 3, 13, color);
    /*display.drawCircle( posX + 1 + 3 , posY - 4, 4.0, color);
    display.drawLine(posX + 1 + 3, posY - 4 - 2 , posX + 1 + 3, posY - 4, color);
    display.drawCircle( posX + 11 + 3, posY - 4, 4.0, color);
    display.drawLine(posX + 11 + 3, posY - 4 - 2 , posX + 11 + 3, posY - 4, color);
    display.drawCircle( posX + 21 + 3, posY - 4, 4.0, color);
    display.drawLine(posX + 21 + 3, posY - 4 - 2 , posX + 21 + 3, posY - 4, color);
    display.drawCircle( posX + 31 + 3, posY - 4, 4.0, color);
    display.drawLine(posX + 31 + 3, posY - 4 - 2 , posX + 31 + 3, posY - 4, color);
    
    display.drawCircle( posX + 1 + 3, posY + 6, 4.0, color);
    display.drawLine(posX + 1+ 3, posY + 6 - 2 , posX + 1 + 3, posY + 6, color);
    display.drawCircle( posX + 11 + 3, posY + 6, 4.0, color);
    display.drawLine(posX + 11 + 3, posY + 6 - 2 , posX + 11 + 3, posY + 6, color);
    display.drawCircle( posX + 21 + 3, posY + 6, 4.0, color);
    display.drawLine(posX + 21 + 3, posY + 6 - 2 , posX + 21 + 3, posY + 6, color);
    display.drawCircle( posX + 31 + 3, posY + 6, 4.0, color);
    display.drawLine(posX + 31 + 3, posY + 6 - 2 , posX + 31 + 3, posY + 6, color);*/
  }
  else if (model == 4)
  {
    posX = posX + 1;
    posY = posY - 10;
    display.drawLine(posX + 0, posY + 2, posX + 0, posY + 18, color);
    display.drawLine(posX + 1, posY + 2, posX + 2, posY + 4, color);
    display.drawLine(posX + 2, posY + 4, posX + 3, posY + 6, color);
    display.drawLine(posX + 3, posY + 6, posX + 5, posY + 8, color);
    display.drawLine(posX + 5, posY + 8, posX + 6, posY + 9, color);
    display.drawLine(posX + 6, posY + 9, posX + 7, posY + 10, color);
    display.drawLine(posX + 7, posY + 10, posX + 9, posY + 11, color);
    display.drawLine(posX + 9, posY + 11, posX + 12, posY + 12, color);
    display.drawLine(posX + 12, posY + 12, posX + 15, posY + 13, color);
    display.drawLine(posX + 15, posY + 13, posX + 20, posY + 15, color);
    display.drawLine(posX + 20, posY + 15, posX + 25, posY + 16, color);
    display.drawLine(posX + 25, posY + 16, posX + 36, posY + 18, color);
  }
}
