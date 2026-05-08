
////////////////////////////////// Main draw funciton basically used to select the drawing function corresponding the current menu /////////////////////////////////

void draw()
{
  display.setTextSize(1);
  bool calibrationDisplay = calibrationMode == true || seqCvCalibration == true || waitingForCvCalibration == true ? true : false;
  if (calibrationDisplay)
  {
    display.setTextColor(WHITE);
    display.clearDisplay();
    if (calibrationMode == true)
    {
      if (calibrationConfirmed == false)
      {
        display.setCursor(0, 24);
        display.print("unplug the jacks");
        display.setCursor(0, 38);
        display.print("then press one of");
        display.setCursor(0, 50);
        display.print("the buttons");
      }
      else
      {
        display.setCursor(58, 32);
        display.print(calibFrameCount / 100);
        display.setCursor(82, 32);
        display.print("%");
      }
    }
    else if(waitingForCvCalibration == true)
    {
      /*display.setCursor(0, 2);
      display.print("Connect each cv out");
      display.setCursor(0, 14);
      display.print("to the cv in above it");
      display.setCursor(0, 30);
      display.print("then  press one of");
      display.setCursor(0, 42);
      display.print("the button");*/
      display.setCursor(0, 2);
      display.print("Calibration ");
      display.setCursor(0, 14);
      display.print("done");
      /*display.setCursor(0, 30);
      display.print("then  press one of");
      display.setCursor(0, 42);
      display.print("the button");*/
    }
    else if(seqCvCalibration == true)
    {
      if (calibDoublon1 == true)
      {
        display.setCursor(4, 24);
        display.print("Ch 1 calib failed");
      }
      else if (calibDoublon2 == true)
      {
        display.setCursor(4, 24);
        display.print("Ch 2 calib failed");
      }
      else
      {
        display.setCursor(26, 12);
        display.print(seqCvCalibrationIndex * 100 / 60);
        display.setCursor(48, 12);
        display.print("%");

        display.setCursor(60, 12);
        display.print("note:");
        display.setCursor(100, 12);
        display.print(seqCvCalibrationIndex);


        display.setCursor(2, 24);
        display.print(CV_input[1]);
        display.setCursor(98, 24);
        display.print(CV_input[0]);
        display.setCursor(2, 36);
        display.print(bestCandidate2);
        display.setCursor(98, 36);
        display.print(bestCandidate1);
        display.setCursor(2, 44);
        display.print(secondCandidate2);
        display.setCursor(98, 44);
        display.print(secondCandidate1);

        for (int i = 0; i < 2 ; i ++)
        {
          if( CV_accuracy_comp_sign[i] == 0)
          {
            display.setCursor(26 + i * 48, 48);
            display.print(CV_accuracy_comp[i]);
          }
          else
          {
            display.setCursor(26 + i * 48, 48);
            display.print("-");
            display.setCursor(34 + i * 48, 48);
            display.print(CV_accuracy_comp[i]);
          }
        }
      }
    }
    display.display();
  }
  else
  {
    if (setting->getRoutingMenuOpened() == true)
    {
       drawRoutingMenu();
    }
    else if (setting->getMainMenuOpened() == true)
    {
      drawMainMenu();
      /*display.clearDisplay();
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print(bestCandidates[0][1]);
      display.setCursor(24, 0);
      display.print(bestCandidates[1][1]);
      display.setCursor(48, 0);
      display.print(bestCandidates[2][1]);
      display.setCursor(72, 0);
      display.print(bestCandidates[3][1]);
      display.setCursor(96, 0);
      display.print(bestCandidates[4][1]);

      display.setCursor(0, 10);
      display.print(bestCandidates[5][1]);
      display.setCursor(24, 10);
      display.print(bestCandidates[6][1]);
      display.setCursor(48, 10);
      display.print(bestCandidates[7][1]);
      display.setCursor(72, 10);
      display.print(bestCandidates[8][1]);
      display.setCursor(96, 10);
      display.print(bestCandidates[9][1]);

      display.setCursor(0, 20);
      display.print(bestCandidates[10][1]);
      display.setCursor(24, 20);
      display.print(bestCandidates[11][1]);
      display.setCursor(48, 20);
      display.print(bestCandidates[12][1]);
      display.setCursor(72, 20);
      display.print(bestCandidates[13][1]);
      display.setCursor(96, 20);
      display.print(bestCandidates[14][1]);

      display.setCursor(0, 30);
      display.print(bestCandidates[15][1]);
      display.setCursor(24, 30);
      display.print(bestCandidates[16][1]);
      display.setCursor(48, 30);
      display.print(bestCandidates[17][1]);
      display.setCursor(72, 30);
      display.print(bestCandidates[18][1]);
      display.setCursor(96, 30);
      display.print(bestCandidates[19][1]);

      display.setCursor(0, 40);
      display.print(bestCandidates[20][1]);
      display.setCursor(24, 40);
      display.print(bestCandidates[21][1]);
      display.setCursor(48, 40);
      display.print(bestCandidates[22][1]);
      display.setCursor(72, 40);
      display.print(bestCandidates[23][1]);
      display.setCursor(96, 40);
      display.print(bestCandidates[24][1]);

      display.setCursor(0, 50);
      display.print(bestCandidates[25][1]);
      display.setCursor(24, 50);
      display.print(bestCandidates[26][1]);
      display.setCursor(48, 50);
      display.print(bestCandidates[27][1]);
      display.setCursor(72, 50);
      display.print(bestCandidates[28][1]);
      display.setCursor(96, 50);
      display.print(bestCandidates[29][1]);
      
      display.display();*/
    }
    else
    {
       switch (setting->getCurrentMenu())
       {
           case LFO :
            drawLFOMenu();
           break;
           case ENVELOPE :
            drawEnvelopeMenu();
           break;
           case SEQUENCER :
            drawSequencerMenu();
           break;
           case CLASSIC_SEQUENCER :
            drawClassicSequencerMenu();
           break;
           case BASSLINE_ENVELOPE :
            drawBasslineEnvelopeMenu();
           break;
       }
    }
  }
}


////////////////////////////////////////////////////////////////////////// char array to String ////////////////////////////////////////////////////////////////////////

String convertToString(char* a, int size) 
{ 
    int i; 
    String s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

/////////// Encode and return the new preset name (for saving menu, used by the saving menu drawing function in drawmainMenu()) + display the corresponding string //////

String encodeName(String currentPresetName)
{ 
  int scale = 8;
  if (knobValue[1] != prevKnob2)
  {
    stringPos = uint8_t(knobValue[1] / 12);
  }
  int cursorPos = int(knobValue[0] / 3);
  char line1[17] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
  char line2[17] = {'Q','R','S','T','U','V','W','X','Y','Z', '0', '1', '2', '3','4', '5'};
  char line3[7] = {'6', '7', '8', '9','_',' '}; 
  String presetName = currentPresetName;
  int initial_perset_length = presetName.length();
  if(cursorPos < 16)
  {
    display.fillRect(cursorPos * scale - 0, 12 + 3, scale, scale + 1, WHITE);
  }
  else if(cursorPos < 32)
  {
    display.fillRect((cursorPos - 16) * scale - 0, 20 + 3, scale, scale + 1, WHITE);
  }
  else 
  {
    if(cursorPos > 37)
    {
      cursorPos = 37;
    }
    display.fillRect((cursorPos - 32) * scale - 0, 28 + 3, scale, scale + 1, WHITE);
  }
  for (int i = 0; i < 16; i++)
  {
    if(cursorPos < 16 && cursorPos == i)
    {
      display.setTextColor(BLACK);
    }
    display.setCursor((i * scale) + 1, 16);
    display.print(line1[i]);
    display.setTextColor(WHITE);
  }
  for (int i = 0; i < 16; i++)
  {
    if(cursorPos < 32 && cursorPos >=  16 && cursorPos == i + 16)
    {
      display.setTextColor(BLACK);
    }
    display.setCursor((i * scale) + 1, 24);
    display.print(line2[i]);
    display.setTextColor(WHITE);
  }
  for (int i = 0; i < 6; i++)
  {
    if(cursorPos >= 32 && cursorPos < 38 && cursorPos == i + 32)
    {
      display.setTextColor(BLACK);
    }
    display.setCursor((i * scale) + 1, 32);
    display.print(line3[i]);
    display.setTextColor(WHITE);
  }
  if (buttonValue[0] == true && prevBut_0 == false) 
  {
    if(cursorPos < 16)
    {
      presetName[stringPos] = line1[cursorPos]; 
      char char_array[12];
      strcpy(char_array, presetName.c_str()); 
      if (stringPos > presetName.length() - 1)
      {
         strcat(char_array,&line1[cursorPos]);
      }
      for(int i = initial_perset_length; i < 11; i++)
      {
        char_array[i-1] = ' ';
      }
      presetName = convertToString(char_array, 11);
    /*  else
      {
         presetName = convertToString(char_array, presetName.length()); 
      }*/
      
    }
    else if(cursorPos < 32)
    {
      presetName[stringPos] = line2[cursorPos - 16]; 
      char char_array[11];
      strcpy(char_array, presetName.c_str()); 
      if (stringPos > presetName.length())
      {
         strcat(char_array,&line2[cursorPos - 16]);
      }
      for(int i = initial_perset_length; i < 11; i++)
      {
        char_array[i-1] = ' ';
      }
       presetName = convertToString(char_array, 11); 
    }
    else 
    {
      presetName[stringPos] = line3[cursorPos - 32]; 
      char char_array[11];
      strcpy(char_array, presetName.c_str()); 
      if (stringPos > presetName.length())
      {
         strcat(char_array,&line3[cursorPos - 32]);
      }
      for(int i = initial_perset_length; i < 11; i++)
      {
        char_array[i-1] = ' ';
      }
      presetName = convertToString(char_array, 11); 
    }
  }
  if (buttonValue[0] == true && prevBut_0 == false)
  {
    if (stringPos < 10)
    {
      stringPos ++;
    }
    else
    {
      stringPos = 0;
    }
  }
  String presetNameTrunc = presetName;
  display.setTextColor(WHITE);
  for (int i = 0; i < 11; i++)
  {
    display.setCursor(11 + i * 8, 43);
    display.print(presetNameTrunc[i]);
  }
  display.fillRect(stringPos * 8 + 11, 51, 5, 2, WHITE);
  prevBut_0 = buttonValue[0];
  prevKnob2 = knobValue[1];
  return presetNameTrunc;
}

////////////////////////////////////////////////////////////////////////////////////////////// draw main and saving menu ////////////////////////////////////////////////

void drawMainMenu()
{
  bool confirmDialog = setting->getConfirmDialog();
  bool confirmSaving = setting->getConfirmSaving();
  bool isSavingB = setting->isSaving(); 
  int tempGeneratorModel_1 = setting->getTempGeneratorModel_1(); 
  int tempGeneratorModel_2 = setting->getTempGeneratorModel_2(); 
  String dispPresetName = setting->getDispPresetName();
  int bankNum = setting->getBankNum();
  int tempBankNum = setting->getTempBankNum(); 
  int presetNum = setting->getPresetNum();
  int tempPresetNum = setting->getTempPresetNum(); 
  int model_1 = setting->getModel_1();
  int model_2 = setting->getModel_2();
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(40, 0);
  //if(MIDI_IN == true) 
  // {
    //display.print(midiInMessage);
  //}
   
  /*display.setCursor(64, 2);
  display.print(int(float(analog_in_buffers[input_buff_tail][5]) / 1.07));*/
  if (isSavingB == true && confirmDialog == false && confirmSaving == false)
  {
     if (firstSaveMenuFrame)
     {
         presetName_D = setting->getDispPresetName();
         firstSaveMenuFrame = false;
     }
     String SAVING = "SAVE TO :";
     char BACK [5] = "<<";
     presetName_D = encodeName(presetName_D);
     
     display.setCursor(111, 0);
     display.print(BACK);
     display.setCursor(7, 68 - 11);
     display.print(SAVING);
     display.setCursor(17, 47 - 8);
     //display.print(PRESET_NAME);
     if (setting->getPresetNum() == setting->getDestinationPreset())
     {
        display.setCursor(91, 68 - 11);
        display.print(setting->getDestinationPreset());
     }
     else if (setting->getPresetNum() != setting->getDestinationPreset())
     {
        display.setCursor(91, 68 - 11);
        display.setTextColor(blinkState);
        display.print(setting->getDestinationPreset());
        display.setTextColor(WHITE);
     }
     setting->setPresetName(presetName_D);
  }
  else if (confirmDialog == false && confirmSaving == false)
  {
    firstFrame = true;
    int m1 = tempGeneratorModel_1;
    int m2 = tempGeneratorModel_2;
    int yOffset = 8;
    drawRoutingIcone();
    String presetNameArray = dispPresetName;
    char BANK_string[16] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'};
    char BANK = BANK_string[tempBankNum];
    if (presetNum == tempPresetNum)
    {
      display.fillRect(7, 16, 71, 12, WHITE);
      display.setTextColor(BLACK);
      display.setCursor(9, 31 - yOffset - 5);
      display.print(presetNameArray);
    }
    else
    {
      display.drawRect(7, 16, 72, 12, WHITE);
      display.setTextColor(WHITE);
      display.setCursor(10, 31 - yOffset - 5);
      display.print( presetNameArray);
    }
    display.drawRect(27, 2, 23, 12, WHITE);
    display.setTextColor(WHITE);
    display.setCursor(30, 17 - yOffset - 5);
    display.print(tempPresetNum);
    
    if (bankNum == tempBankNum)
    {
      display.fillRect(88, 2, 11, 12, WHITE);
      display.setTextColor(BLACK);
      display.setCursor(90, 9 - 5);
      display.print(BANK);
      display.setTextColor(WHITE);
    }
    else
    {
      display.drawRect(88, 2, 11, 12, WHITE);
      display.setTextColor(WHITE);
      display.setCursor(90, 9 - 5);
      display.print(BANK);
    }
    display.setTextColor(WHITE);
    if(model_1 == m1 || bankNum != tempBankNum || presetNum != tempPresetNum)
    {
      display.drawRect(7,34, 48, 30,  WHITE);
      draw_icone(11, 48, m1, WHITE);
    }
    else
    {
      //display.fillRect(73,36, 44, 26, WHITE);
      draw_icone(11, 48, m1, blinkState);
    }
    if(model_2 == m2 || bankNum != tempBankNum || presetNum != tempPresetNum)
    {
      display.drawRect(71,34, 48, 30,  WHITE);
      draw_icone(75, 48, m2, WHITE);
    }
    else
    {
      //display.fillRect(73,36, 44, 26, WHITE);
      draw_icone(75, 48, m2, blinkState);
    }
  }
  else if (confirmDialog == true && confirmSaving == false)
  {
      display.setCursor(18, 5);
      display.print("DO YOU WANT");
      
      display.setCursor(18, 20);
      display.print("TO CONFRIM THE");
     
      display.setCursor(18, 35);
      display.print("SELECTED MODEL?");
     
      display.setCursor(18, 55);
      display.print("YES");

      display.setCursor(100, 55);
      display.print("NO");
  }
  else if (confirmSaving == true)
  {
      display.setCursor(58, 20);
      display.print("SAVE?");
      
      display.setCursor(18, 55);
      display.print("YES");
     
      display.setCursor(100, 55);
      display.print("NO");
  }
  display.setTextColor(WHITE);
  if (BUFF_OVERLOAD_DISPLAY == true)
  {
    display.fillRect(58, 3, 45, 28, BLACK);
    int buffMarge = abs(output_buff_head - output_buff_tail);
    if (buffMarge < BUFFER_SIZE / 2)
    {
      buffMarge = BUFFER_SIZE - buffMarge;
    }
    display.setTextSize(3);
    display.setCursor(60, 20 - 8);
    display.println(buffMarge);
    display.fillRect(58,33, 45, 28, BLACK);
    int buffMarge2 = abs(input_buff_head - input_buff_tail);
    if (buffMarge2 < BUFFER_SIZE / 2)
    {
      buffMarge2 = BUFFER_SIZE - buffMarge2;
    }
    display.setTextSize(3);
    display.setCursor(60, 52 - 8);
    display.println(buffMarge2);
    display.setTextSize(1);
  }
  display.display();
}

/////////////////////////////////////////////////////////////////////// Routing menu (internal patching) drawing /////////////////////////////////////////////////////////////////////////

void drawRoutingMenu()
{
    display.clearDisplay();
    int currentDest = setting->getCurrentDest();
    int currentSource = setting->getCurrentSource();
    display.setCursor(113, 8 - 8);
    display.print("<<");
    drawRoutingMenuFrame(currentDest, currentSource);
    
    int dist = 28;
    if (routingMap[currentDest][currentSource] == false)
    {
        display.drawLine(23.0 + currentDest * dist , 19, 23.0 + currentSource * dist, 53.0, blinkState);
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (routingMap[i][j] == true)
            {
                display.drawLine(23.0 + i * dist , 19, 23.0 + j * dist, 53.0, WHITE);
            }
        }
    }
    display.display();
}

/////////////////////////////////////////////////////////////////////////// LFO menu (internal patching) drawing /////////////////////////////////////////////////////////////////////////

void drawLFOMenu()
{
  display.clearDisplay();
  //drawBufferWarning();
  int page = setting->getPage();
  int y_offset = 16;
  int channel = setting->getEditChannel();
  if (page == 0)
  {
      
      int y_offset = 8;
      int x_offset = 0;
      //display.drawLine( 0 , 13, 128, 13, WHITE);
      display.setCursor(3.0, 57);
      display.print("CV");
      display.setCursor(27.0, 57);
      display.print("PHASE");
      display.setCursor(78.0, 57);
      display.print("TRIG");

      int pol = setting->getPolarity(channel);
      switch (pol)
      {
          case 0:
             display.setCursor(115.0, 57);
             display.print("Bi"); 
          break;
        case 1:
             display.setCursor(110.0, 57);
             display.print("Uni"); 
            break;
      }
      
      int LFO_rate = setting->getParamArray(channel, LFO_RATE);
      //float LFO_wave = ((setting->getParamArray(channel, LFO_WAVE)) / 18.0) + 1.0;
      int LFO_phase = setting->getParamArray(channel, LFO_PHASE);
      int LFO_tPos = setting->getParamArray(channel, LFO_TRIG_POS);
      if (knobMoved[1] == true || knobWasMoved[1] == true)
      {
          //display.setCursor(87.0, 0);
          int valueToDisplay = int(floor(setting->getParamArray(channel, LFO_WAVE) / 16));
          switch (valueToDisplay)
          {
            case 0:
              display.drawLine(86 - 2, 4, 86 - 2, 2, WHITE);
              display.drawLine(86 - 2, 2, 87 - 2, 0, WHITE);
              display.drawLine(88 - 2, 0, 90 - 2, 2, WHITE);
              display.drawLine(90 - 2, 2, 90 - 2, 6, WHITE);
              display.drawLine(90 - 2, 6, 92 - 2, 8, WHITE);
              display.drawLine(92 - 2, 8, 94 - 2, 6, WHITE);
              display.drawLine(94 - 2, 6, 94 - 2, 4, WHITE);
            break;
            case 1:
              display.drawLine(86 - 2, 8, 86 - 2, 0, WHITE);
              display.drawLine(86 - 2, 0, 94 - 2, 8, WHITE);
            break;
            case 2:
              display.drawLine(86 - 2, 8, 86 - 2, 5, WHITE);
              display.drawLine(87 - 2, 4, 87 - 2, 3, WHITE);
              display.drawLine(88 - 2, 2, 89 - 2, 1, WHITE);
              display.drawLine(89 - 2, 1, 90 - 2, 1, WHITE);
              display.drawLine(91 - 2, 2, 92 - 2, 3, WHITE);
              display.drawLine(92 - 2, 4, 93 - 2, 5, WHITE);
              display.drawLine(93 - 2, 6, 93 - 2, 8, WHITE);
            break;
            case 3:
              display.drawLine(86 - 2, 8, 90 - 2, 0, WHITE);
              display.drawLine(90 - 2, 0, 94 - 2, 8, WHITE);
            break;
            case 4:
              display.drawLine(86 - 2, 8, 90 - 2, 8, WHITE);
              display.drawLine(90 - 2, 8, 90 - 2, 0, WHITE);
              display.drawLine(90 - 2, 0, 94 - 2, 0, WHITE);
            break;
            case 5:
              display.drawLine(86 - 2, 1, 86 - 2, 4, WHITE);
              display.drawLine(87 - 2, 5, 87 - 2, 6, WHITE);
              display.drawLine(88 - 2, 7, 89 - 2, 8, WHITE);
              display.drawLine(89 - 2, 8, 90 - 2, 8, WHITE);
              display.drawLine(91 - 2, 7, 92 - 2, 6, WHITE);
              display.drawLine(92 - 2, 5, 93 - 2, 4, WHITE);
              display.drawLine(93 - 2, 3, 93 - 2, 1, WHITE);
            break;
            case 6:
              display.drawLine(86 - 2, 8, 94 - 2, 0, WHITE);
              display.drawLine(94 - 2, 0, 94 - 2, 8, WHITE);
            break;
            case 7:
              display.drawLine(86 - 2, 6, 88 - 2, 6, WHITE);
              display.drawLine(88 - 2, 8, 90 - 2, 8, WHITE);
              display.drawLine(90 - 2, 0, 92 - 2, 0, WHITE);
              display.drawLine(92 - 2, 4, 94 - 2, 4, WHITE);
            break;
          }
          //display.print(LFO_wave);
      }
      else
      {
          display.setCursor(78.0, 0);
          display.print("WAV");
      }
      if (channel == 0 || (channel == 1 && setting->getModel_1() != LFO))
      {
        display.setCursor(103.0, 1.0);
        if (setting->getParamArray(channel, LFO_SYNC) == false)
        {
          display.print("Snap");
        }
        else
        {
          display.fillRect(101, 0, 26, 9, WHITE);
          display.setTextColor(BLACK);
          display.print("Snap");
          display.setTextColor(WHITE);
        }
      }
      if (channel == 1)
      {
        drawCommonMenuFrames(channel);
      }
      if (scope_mode == false && channel == 0)
      {
        display.setCursor(0.0, 0);
        display.print("Scop");
      }
      else if (channel == 0)
      {
        display.setCursor(0.0, 0);
        display.print("Lfo");
      }
      int xPos = int(s_phase[channel]);
      int xp = int(xPos) / 2;
      int rectYPos = staticScopeBuffer[xp] + 4 + y_offset * 2;
      int rectYPos2 = staticScopeBuffer[xPos] + 4 + y_offset * 2;
      
      int trigPos = int(t_pos[channel]); 
      display.fillRect(0, 15, 128, 37, BLACK);
      //display.fillRect( xPos + x_offset, 15, 1, 39, WHITE);
      display.fillRect( xPos + x_offset - 2, rectYPos2 - 2, 5, 5, WHITE);
      for (int i = 0; i < 64; i++)
      {
          int yPos = staticScopeBuffer[i * 2] + 21;
          int yPos2;
          if (i == 63)
          {
            yPos2 = staticScopeBuffer[0] + 21;
          }
          else
          {
            yPos2 = staticScopeBuffer[i * 2 + 1] + 21;
          }
          if (yPos < 16)
          {
              yPos = 16;
          }
          if (yPos2 < 16)
          {
              yPos2 = 16;
          }
          display.drawLine( (i * 2) + x_offset, yPos, (i * 2) + 1.0 + x_offset, yPos2, WHITE);
      }
      if (setting->getEditChannel() == 1 && setting->getModel_1() == LFO)
      {
          if (setting->getParamArray(1, LFO_SYNC) == true)
          {
              display.setCursor(25, 0);
              display.print("SYNC");
          }
          else
          {
              if (knobMoved[0] == true || knobWasMoved[0] == true)
              {
                  display.setCursor(30, 8 - 8);
                  display.print(LFO_rate);
              }
              else
              {
                  display.setCursor(29, 0);
                  display.print("RATE");
              }
          }
          display.setCursor(120, 0);
          display.print("S");
      }
      else
      {
          if (knobMoved[0] == true || knobWasMoved[0] == true)
          {
              display.setCursor(30, 0);
              display.print(LFO_rate);
          }
          else
          {
              display.setCursor(28, 0);
              display.print("RATE");
          }
      }
      
      int resetPos = 0;
      if (channel == 0)
      {
          resetPos = param_mix[2][0];
      }
      else
      {
          resetPos = param_mix[2][1];
      }
      
  
      if (resetPos < 100)// && (knobMoved[2] == true || knobWasMoved[2] == true))
      {
        //if (knobMoved[2] == true || knobWasMoved[2] == true)
        //{
          display.fillRect(resetPos + 3, 15, 30, 10, WHITE);
          display.setTextColor(BLACK);
          display.setCursor(resetPos + 5, 16);
          display.print(resetPos);
        //}
        
        display.drawLine( resetPos + x_offset, 22 - y_offset, resetPos + x_offset, 62 - y_offset, WHITE);
      }
      else //if (knobMoved[2] == true  || knobWasMoved[2] == true)
      {
        if (knobMoved[2] == true || knobWasMoved[2] == true)
        {
          display.fillRect(resetPos -26, 15, 30, 10, WHITE);
          display.setTextColor(BLACK);
          display.setCursor(resetPos -24, 16);
          display.print(LFO_phase);
        }
        display.drawLine( resetPos + x_offset, 22 - y_offset, resetPos + x_offset, 62 - y_offset, WHITE);
      }
      if (trigPos < 100 )//&& (knobMoved[3] == true || knobWasMoved[3] == true))
      {
        if (knobMoved[3] == true || knobWasMoved[3] == true)
        {
          display.fillRect(trigPos +3, 25, 30, 10, WHITE);
          display.setTextColor(BLACK);
          display.setCursor(trigPos + 5, 26);
          display.print(LFO_tPos);
        }
        display.drawLine( trigPos + x_offset, 22 - y_offset, trigPos + x_offset, 62 - y_offset, WHITE);
      }
      else //if (knobMoved[3] == true|| knobWasMoved[3] == true)
      {
        if (knobMoved[3] == true || knobWasMoved[3] == true)
        {
          display.fillRect(trigPos -26, 25, 30, 10, WHITE);
          display.setTextColor(BLACK);
          display.setCursor(trigPos - 24, 26);
          display.print(LFO_tPos);
        }
        display.drawLine( trigPos + x_offset, 22 - y_offset, trigPos + x_offset, 62 - y_offset, WHITE);
      }
      display.setTextColor(WHITE);
      if (resetPos < 123)
      {
          display.drawTriangle(resetPos + 5, 15.0, resetPos, 18.0, resetPos, 12.0, WHITE);
      }
      if (resetPos > 5)
      {
          display.drawTriangle( resetPos - 5, 15.0, resetPos, 18.0, resetPos, 12.0, WHITE);
      }
  }
  else if (page == 1)
  {
      scope_mode = false;
      String param_string[4] = {"RATE", "WAVE", "PHASE", "T-POS"};
      int ind1 = setting->getCVControlledParam(0, channel);
      int ind2 = setting->getCVControlledParam(1, channel);
      if (ind1 > 3)
      {
        ind1 = 3;
      }
      if (ind2 > 3)
      {
        ind2 = 3;
      }
      String CV_PARAM_1 = param_string[ind1];
      String CV_PARAM_2 = param_string[ind2];
      int level1 = (setting->getParamArray(channel, INT_CV_PARAM1));
      int level2 = (setting->getParamArray(channel, INT_CV_PARAM2));
      drawCVMenu( CV_PARAM_1, CV_PARAM_2, level1, level2);
  }
  display.display();
}

/////////////////////////////////////////////////////////////////////////// Env menu (internal patching) drawing /////////////////////////////////////////////////////////////////////////

void drawEnvelopeMenu()
{
  display.clearDisplay();
  int y_offset = 11;
  int x_offset = 0;
  int page = setting->getPage();
  int channel = setting->getEditChannel();
  
  if (page == 0)
  {
      drawCommonMenuFrames(channel);
      display.drawLine(115 , 15 - y_offset, 128, 15 - y_offset, WHITE);
      display.drawTriangle(110.0, 4.0, 115.0, 7.0, 115.0, 1.0, WHITE);
      //display.drawLine(0 , 13, 128, 13, WHITE);
      float attackPhase = ADSR[channel]->getAttackPhase();
      float decayPhase = ADSR[channel]->getDecayPhase();
      float releasePhase = ADSR[channel]->getReleasePhase();
      int envelopeState = ADSR[channel]->getState();
      float attack = 0;
      float decay = 0;
      float sustain = 0;
      float release = 0;
      if (channel == 0)
      {
        attack = param_mix[0][0];
        decay = param_mix[1][0];
        sustain = param_mix[2][0];
        release = param_mix[3][0];
      }
      else
      {
        attack = param_mix[0][1];
        decay = param_mix[1][1];
        sustain = param_mix[2][1];
        release = param_mix[3][1];
      }
      float shape = setting->getParamArray(channel, 8) / 127.0;
      float outB = rawEnvOut2 * 5;
      float outA = rawEnvOut1 * 5;
      int trigMode = setting->getParamArray(channel, 9);
      display.fillRect(0, 15, 128, 37, BLACK);
      drawADSR(attack, decay, sustain, release, attackPhase, decayPhase, releasePhase, shape, envelopeState, channel, outA, outB, trigMode);
      int attack_knob_param = setting->getParamArray(channel, 0);
      int decay_knob_param = setting->getParamArray(channel, 1);
      int sustain_knob_param = setting->getParamArray(channel, 2);
      int release_knob_param = setting->getParamArray(channel, 3);

      if (knobMoved[0] == true || knobWasMoved[0] == true)
      {
        display.setCursor(29, 0);
        display.print(attack_knob_param);
      }
      else
      {
        display.setCursor(29, 1);
        display.print("ATT");
      }
      /*if (knobMoved[1] == true || knobWasMoved[1] == true)
      {
          if (setting->getSecondKnobMode(channel) == 0)
          {
            display.setCursor(80, 1);
            display.print(decay_knob_param);
          }
          if (setting->getSecondKnobMode(channel) == 2)
          {
            if (trigMode < 42)
            {
              display.setCursor(84, 1);
              display.print("EOA");
            }
            else if (trigMode < 84)
            {
              display.setCursor(84, 1);
              display.print("EOD");
            }
            else
            {
              display.setCursor(84, 1);
              display.print("EOR");
            }
          }
      }*/
      //else
      {
        if (setting->getSecondKnobMode(channel) == 0)
        {
          display.setCursor(80, 1);
          display.print("DEC");
        }
        else if (setting->getSecondKnobMode(channel) == 1)
        {
          display.setCursor(72, 1);
          display.print("SHAPE");
        }
        else if (setting->getSecondKnobMode(channel) == 2)
        {
          display.setCursor(84, 1);
          display.print("TRIG");
        }
      }

      if (knobMoved[2] == true || knobWasMoved[2] == true)
      {
        display.setCursor(28, 57);
        display.print(sustain_knob_param);
      }
      else
      {
        display.setCursor(28, 57);
        display.print("SUS");
      }

      if (knobMoved[3] == true || knobWasMoved[3] == true)
      {
        display.setCursor(80, 57);
        display.print(release_knob_param);
      }
      else
      {
        display.setCursor(80, 57);
        display.print("REL");
      }
      display.setCursor(3.0, 57);
      display.print("CV");
      int pol = setting->getPolarity(channel);
      switch (pol)
      {
        case 0:
            display.setCursor(110, 57);
            display.print("Uni"); 
        break;
        case 1:
            display.setCursor(115, 57);
            display.print("Bi"); 
        break;
        case 2:
            display.setCursor(110, 57);
            display.print("Inv"); 
        break;
      }
  }
  else if (page == 1)
  {
      String param_string[4] = {"Attack", "Decay", "Sustain", "Release"};
      int ind1 = setting->getCVControlledParam(0, channel);
      int ind2 = setting->getCVControlledParam(1, channel);
      if (ind1 > 3)
      {
        ind1 = 3;
      }
      if (ind2 > 3)
      {
        ind2 = 3;
      }
      String CV_PARAM_1 = param_string[ind1];
      String CV_PARAM_2 = param_string[ind2];
      int level1 = (setting->getParamArray(channel, INT_CV_PARAM1));
      int level2 = (setting->getParamArray(channel, INT_CV_PARAM2));
      drawCVMenu(CV_PARAM_1, CV_PARAM_2, level1, level2);
  }
  display.display();
}

/////////////////////////////////////////////////////////////////////////// Seq menu (internal patching) drawing /////////////////////////////////////////////////////////////////////////

void drawSequencerMenu()
{
  int channel = setting->getEditChannel();
  display.clearDisplay();
  if (setting->getPage() == 0)
  {
     displaySeqParams(channel);
  }
  else
  {
    displaySeqTempo(channel);
  }
  display.display();
}

void drawClassicSequencerMenu()
{
  if (setting->getPage() == 0)
  {
    int channel = setting->getEditChannel();
    display.clearDisplay();
    displayClassicSeqParams(channel);
    display.display();
  }
  else
  {
    const int paramOffset = 8;
    int channel = setting->getEditChannel();
    display.clearDisplay();
    uint8_t clockDiv = setting->getParamArray(channel, paramOffset + 6);
    uint8_t readMode = setting->getParamArray(channel, paramOffset + 3);
    bool kbdMode = setting->getKeyBoardMode(channel);
    if (clockDiv == 0)
    {
      display.setCursor(2, 2);
      display.print("1");
    }
    else if (clockDiv == 1)
    {
      display.setCursor(2, 2);
      display.print("1/2");
    }
    else if (clockDiv == 2)
    {
      display.setCursor(2, 2);
      display.print("1/3");
    }
    else if (clockDiv == 3)
    {
      display.setCursor(2, 2);
      display.print("1/4");
    }
    else if (clockDiv == 4)
    {
      display.setCursor(2, 2);
      display.print("1/6");
    }
    else if (clockDiv == 5)
    {
      display.setCursor(2, 2);
      display.print("1/8");
    }
    else if (clockDiv == 6)
    {
      display.setCursor(2, 2);
      display.print("1/12");
    }
    else if (clockDiv == 7)
    {
      display.setCursor(2, 2);
      
      display.print("1/16");
    } 
    display.setCursor(2, 58);
    if (readMode == 0)
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
    }
    display.setCursor(70, 2);
    // --> keyboard mode
    /*if (kbdMode == true)
    {
      display.print("Key Mode");
    }
    else
    {
      display.print("Knob Mode");
    }*/
    display.display();
  }
  /*display.clearDisplay();
  display.setCursor(50, 25);
  display.print(tot_);
  display.display();*/
}

void drawBasslineEnvelopeMenu()
{
  display.clearDisplay();
  int channel = setting->getEditChannel();
  drawAccentSeq(channel);
  int accentLevel = setting->getParamArray(channel, 1);
  int accentLength = setting->getParamArray(channel, 9);
  int accentHardness = setting->getParamArray(channel, 8);
  int attack = setting->getParamArray(channel, 2);
  int decay = setting->getParamArray(channel, 3);
  int coordCircle2_y = 0;
  int coordCircle3_y = 0;
  int coordCircle1_y = coordCircle2_y = coordCircle3_y = 34;
  int coordCircle1_x = 22;
  int coordCircle2_x = 64;
  int coordCircle3_x = 106;
  int radius = 10;
  drawPot(radius, coordCircle1_x, coordCircle1_y, attack, "attack", 0);
  drawPot(radius, coordCircle2_x, coordCircle2_y, decay, "decay", -3);
  if (setting->getSecondKnobMode(channel) == 0)
  {
    drawDualPot(radius, coordCircle3_x, coordCircle3_y, accentLevel, "accent", "gap",0);
  }
  if (setting->getSecondKnobMode(channel) == 1)
  {
    drawPot(radius, coordCircle3_x, coordCircle3_y, accentHardness, "Hard.", 0);
  }
  if (setting->getSecondKnobMode(channel) == 2)
  {
    drawPot(radius, coordCircle3_x, coordCircle3_y, accentLength, "Length", 0);
  }
  display.display();
}

void channelLedLightning()
{
  if (setting->getMainMenuOpened() == false)
  {
    if (setting->getEditChannel() == 0)
    {
       GPIOA->regs->BSRR = 0b0000000100000000; 
       GPIOB->regs->BRR = 0b0000000100000000;    
    }
    else
    {
       GPIOA->regs->BRR = 0b0000000100000000;    
       GPIOB->regs->BSRR = 0b0000000100000000;    
    }
  }    
  else
  {
     //if (ledBlink)
     //{
        GPIOA->regs->BRR = 0b0000000100000000;  
     //}
     //else
     //{
        GPIOB->regs->BRR = 0b0000000100000000;
     //}             
  }
}
