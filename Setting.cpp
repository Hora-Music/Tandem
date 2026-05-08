
#include "Setting.h"
extern SPIClass SPI_2B(2);
extern SdFat sd1(&SPI_2B);

void Setting::init() // init current preset, ban, models, presets names arrays,...
{
    keyboardMode[0] = false;
    keyboardMode[1] = false;
    polarity[0] = 0;
    polarity[1] = 0;
    polarOptions[0] = 2;
    polarOptions[1] = 3;
    polarOptions[2] = 2;
    presetChangePeriod = 0;
    bankChangePeriod = 0;
    model1ChangePeriod = 0;
    model2ChangePeriod = 0;
    previousGeneratorModel_1 = 0;
    previousGeneratorModel_1 = 0;
    sd1.begin(SD1_CS, SD_SCK_MHZ(18));
    paramLength[0] = 9;
    paramLength[1] = 10;
    paramLength[2] = 110;
    paramLength[3] = 110;
    paramLength[4] = 10;
    paramLength[5] = 5;
    paramLength[6] = 6;
    paramLength[7] = 16;
    numberOfPages[0] = 2; // number of pages for LFO
    numberOfPages[1] = 2; // number of pages for ENV
    numberOfPages[2] = 2; // number of pages for SEQ
    for (int i = 0; i < 2; i++)
    {
        classicSeqLength[i] = 15;
        reset[i] = false;
        secondKnobMode[i] = 0;
        for (int j = 0; j < 110; j++)
        {
            paramArray[i][j] = 0;
            param_F_Load[i][j] = 0;
        }
        seqNum[i] = 0;
        octMode[i] = false;
        seqEditPos[i] = 0;
        subParam[i] = 0;
        seqIndex[i] = 0;
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cvControlledParam[i][j] = 0;
        }
    }
    for (int i = 0; i < 4; i++)
    {
      knobLocked[i] = false;
      knobValueOnChange[i] = 0;
    }
    modelOrder[0] = 0;
    modelOrder[1] = 1;
    modelOrder[2] = 4;
    modelOrder[3] = 3;
    modelOrder[4] = 2;
    Timer2.pause();
    loading = true;
    setLastPresetNum();
    dispPresetName = loadPreset(last_preset_num, last_bank_num);
    loading = false;
    generatorModel_1 = preLoadedGeneratorModel_1;
    generatorModel_2 = preLoadedGeneratorModel_2;
    
    presetNum = last_preset_num;
    bankNum = last_bank_num;
    for (int i = 0; i < paramLength[generatorModel_1]; i++)
    {
        paramArray[0][i] = getParamModel1(i);
    }
    for (int i = 0; i < paramLength[generatorModel_2]; i++)
    {
        paramArray[1][i] = getParamModel2(i);
    }
    for (int i = 0; i < 4; i++)
    {
        internalPatchMap[0][i] = pMap[i];
    }
    for (int i = 0; i < 4; i++)
    {
        internalPatchMap[1][i] = pMap[i + 4];
    }
    for (int i = 0; i < 4; i++)
    {
        internalPatchMap[2][i] = pMap[i + 8];
    }
    for (int i = 0; i < 4; i++)
    {
        internalPatchMap[3][i] = pMap[i + 12];
    }
    cvControlledParam[0][0] = paramArray[0][CV_PARAM1];
    cvControlledParam[1][0] = paramArray[0][CV_PARAM2];
    cvControlledParam[0][1] = paramArray[1][CV_PARAM1];
    cvControlledParam[1][1] = paramArray[1][CV_PARAM2];
    tempBankNum = bankNum;
    tempPresetNum = presetNum;
    tempGeneratorModel_1 = generatorModel_1;
    tempGeneratorModel_2 = generatorModel_2;
    
    destPreset = presetNum;
    first_preset_loaded = true;
    
    for (int i = 0; i < 32; i ++)
    {
      String preset_name_at_i = loadPreset(i, bankNum); 
      for (int j = 0; j < 11; j++)
      {
        preset_names[i][j] = preset_name_at_i[j];
      }
    }   
    Timer2.resume();
    mainMenuOpened = true;
    if (generatorModel_1 == 0)
    {
     GPIOA->regs->BSRR = 0b0000000000001000;
    }
    else
    {
     GPIOA->regs->BRR = 0b0000000000001000;
    }
    if (generatorModel_2 == 0)
    {
     GPIOA->regs->BSRR = 0b0000000001000000;
    }
    else
    {
     GPIOA->regs->BRR = 0b0000000001000000;
    }                     
}
void Setting::saveLastPresetNum(int presetNum_, int bankNum_) // save the last preset number 
{
  String lastPresetNumFile = "P_MEM/pmem.pmem";
  const char *fname2 = lastPresetNumFile.c_str();
  ofstream sdout(fname2);
  if (sdout)
  {
    sdout << F(String(presetNum_).c_str());
    sdout << F(",");
    sdout << F(String(bankNum_).c_str());
    sdout << F(",");
    sdout << F(String(generatorModel_1).c_str());
    sdout << F(",");
    sdout << F(String(generatorModel_2).c_str());
    sdout << F(",");
  }
  sdout.close();
}

void Setting::setLastPresetNum() // set the last preset number
{
  int lineNum = 0;
  String lastPresetNumFile = "P_MEM/pmem.pmem";
  const char *fname2 = lastPresetNumFile.c_str();
  ifstream sdin(fname2);
  String str2 = "";
  char buffer2[18];
  const int line_buffer_size = 18;
  while (sdin.getline(buffer2, line_buffer_size, ',') || sdin.gcount()) 
  {
     str2 = String(buffer2);
     if (lineNum == 0)
     {
      last_preset_num = str2.toInt();
     }
     if (lineNum == 1)
     {
      last_bank_num = str2.toInt();
     }
     if (lineNum == 2)
     {
      generatorModel_1 = str2.toInt() > 3 ? 3 : str2.toInt();
     }
     if (lineNum == 3)
     {
      generatorModel_2 = str2.toInt() > 3 ? 3 : str2.toInt();
     }
     lineNum ++;
  }
  sdin.close();
}

void Setting::saveCvTable(uint16_t cvTable[2][120], String tableName, int index) 
{
  String tableFilePath[4] =  {"P_MEM/CV_tables/CV_Table01.cvt", "P_MEM/CV_tables/CV_Table02.cvt", "P_MEM/CV_tables/CV_Table03.cvt", "P_MEM/CV_tables/CV_Table04.cvt"} ;
  const char *fname1 = tableFilePath[index].c_str();
  ofstream sdout(fname1);
  if (sdout)
  {
    for(int i = 0; i < 104; i++)
    {
      sdout << F(String(cvTable[0][i]).c_str());
      sdout << F(",");
      sdout << F(String(cvTable[1][i]).c_str());
      if (i < 103)
      {
        sdout << F(",");
      }
    }
    sdout << F(tableName.c_str());
  }
  sdout.close();
  String nameFilePath2 =  "P_MEM/name_list_" + String(index) + ".cvt" ;
  const char *fname2 = nameFilePath2.c_str();
  ofstream sdout2(fname2);
  if (sdout2)
  {
    sdout2 << F(tableName.c_str());
  }
  sdout2.close();
}

String Setting::getCvTableName(int index)
{
  if (index == 0)
  {
    return name1;
  }
  else if (index == 1)
  {
    return name2;
  }
  else if (index == 2)
  {
    return dispPresetName;
  }
  else if (index == 3)
  {
    return newPresetName;
  }
  return "";
}

void Setting::initCvTableName(int index)
{
  String nameFilePath =  "P_MEM/name_list_" + String(index) + ".cvt" ;
  const char *fname2 = nameFilePath.c_str();
  ifstream sdin(fname2);
  String str = "";
  char buffer2[11];
  const int line_buffer_size = 11;
  if(sdin)
  {
    while (sdin.getline(buffer2, line_buffer_size, ',') || sdin.gcount()) 
    {
     str = String(buffer2);
     if (index == 0)
      {
        name1 =  str;
      }
      else if (index == 1)
      {
        name2 =  str;
      }
      else if (index == 2)
      {
        dispPresetName =  str;
      }
      else if (index == 3)
      {
        newPresetName =  str;
      }
    }
  }
  sdin.close();
}

void Setting::loadCvTable(uint16_t cvTable[2][120], int index) // set the last preset number
{
  String tableFilePath[4] =  {"P_MEM/CV_tables/CV_Table01.cvt", "P_MEM/CV_tables/CV_Table02.cvt", "P_MEM/CV_tables/CV_Table03.cvt", "P_MEM/CV_tables/CV_Table04.cvt"} ;
  const char *fname2 = tableFilePath[index].c_str();
  ifstream sdin(fname2);
  int lineNum = 0;
  int index1 = 0;
  int index2 = 0;
  String str2 = "";
  char buffer2[18];
  const int line_buffer_size = 18;
  while (sdin.getline(buffer2, line_buffer_size, ',') || sdin.gcount()) 
  {
     str2 = String(buffer2);
     if (lineNum < 208)
     {
      if (lineNum % 2 == 0)
     {
      cvTable[0][index1] = str2.toInt();
      index1++;
     }
     else
     {
      cvTable[1][index2] = str2.toInt();
      index2++;
     }
      lineNum ++;
     }
  }
  sdin.close();
}
//////////////////////////////////////////////////////////////////////// save a preset on SD card //////////////////////////////////////////////////////////////////////////////

void Setting::savePreset(int c_presetNum, int c_bankNum, String c_dispPresetName) 
{
        String pName = "noname";
        String balise1 =  "Model_2";
        String balise2 =  "Patch_Map";
        String str = "";
        String dirPath = "Presets/BANK_";
        char bankLetter[16] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
        dirPath += bankLetter[c_bankNum];
        String fileName = dirPath;
        fileName += "/preset_";
        String num = String(c_presetNum);
        if (c_presetNum < 10)
        {
            fileName += "0";
        }
        fileName += num;
        fileName += ".gcp";
        const char *fname = fileName.c_str();
        ofstream sdout(fname);
        if (sdout)
        {
            sdout << F(c_dispPresetName.c_str());
            sdout << F(",");
            sdout << F(String(generatorModel_1).c_str());
            sdout << F(",");
            sdout << F(String(generatorModel_2).c_str());
            sdout << F(",");
            for (int i = 0; i < paramLength[generatorModel_1]; i++)
            {
                 int d1 = paramArray[0][i] & 255;
                 int d2 = (paramArray[0][i]>> 8) & 255;
                 if (d2 != 0)
                 {
                  String str = String(d2, BIN);
                  sdout << F(str.c_str());
                 }
                 String str2 = String(d1, BIN);
                 for (int i = 0; i < 8 - str2.length(); i++)
                 {
                    sdout << F("0");
                 }
                 sdout << F(str2.c_str());
                 sdout << F(",");
            }
            sdout << F("Model_2,");
            for (int i = 0; i < paramLength[generatorModel_2]; i++)
            {
                 int d1 = paramArray[1][i] & 255;
                 int d2 = (paramArray[1][i]>> 8) & 255;
                 if (d2 != 0)
                 {
                  String str = String(d2, BIN);
                  sdout << F(str.c_str());
                 }
                 String str2 = String(d1, BIN);
                 for (int i = 0; i < 8 - str2.length(); i++)
                 {
                    sdout << F("0");
                 }
                 sdout << F(str2.c_str());
                 sdout << F(",");
            }
             sdout << F("Patch_Map,");
             for (int i = 0; i < 4; i++)
            {
                 sdout << F(String(internalPatchMap[0][i]).c_str());
                 sdout << F(",");
            }
            for (int i = 0; i < 4; i++)
            {
                 sdout << F(String(internalPatchMap[1][i]).c_str());
                 sdout << F(",");
            }
            for (int i = 0; i < 4; i++)
            {
                 sdout << F(String(internalPatchMap[2][i]).c_str());
                 sdout << F(",");
            }
            for (int i = 0; i < 4; i++)
            {
                 sdout << F(String(internalPatchMap[3][i]).c_str());
                 sdout << F(",");// << flush;
            }
            /*sdout << F("subModelsNum,");
            for (int i = 0; i < 2; i++)
            {
                 sdout << F(String(subModels[0]).c_str());
                 sdout << F(String(subModels[1]).c_str());
            }*/
            sdout.flush();
            sdout.close();
       }
       saving = false;
}

///////////// load a preset from SD card to param arrays (not those use by the cv processors, confimation by pushing button0 is needed to load this in the effective arrays), and return the preset name ///////////

String Setting::loadPreset(int presetNum_, int bankNum_) 
{
        keyboardMode[0] = false;
        keyboardMode[1] = false;
        String pName = "noname";
        bool secondModelReached = false;
        bool patchMapReached = false;
        bool subModelsNumReached = false;
        uint8_t model1Lines = 0;
        uint8_t model2Lines = 0;
        const uint8_t patchMapReachedMines = 16;
        String balise1 =  "Model_2";
        String balise2 =  "Patch_Map";
        String balise3 =  "subModelsNum";
        String str = "";
        String dirPath = "Presets/BANK_";
        char bankLetter[16] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
        dirPath += bankLetter[bankNum_];
        String fileName = dirPath;
        fileName += "/preset_";
        String num = String(presetNum_);
        if (presetNum_ < 10)
        {
            fileName += "0";
        }
        fileName += num;
        fileName += ".gcp";
        const char *fname = fileName.c_str();
        int lineNum = 0;
        ifstream sdin(fname);
        const int line_buffer_size = 18;
        char buffer[18];
        while (sdin.getline(buffer, line_buffer_size, ',') || sdin.gcount()) 
        {
            if (sdin.eof())
            {
              break;
            }
            if (sdin.fail()) 
            {
              break;
            }
            str = String(buffer);
            
            if (str == balise1)
            {
                secondModelReached = true;
            }
            else if (str == balise2)
            {
                patchMapReached = true;
            }
            else if (str == balise3)
            {
                patchMapReached = true;
            }
            if (lineNum == 0)
            {
                pName = str;
            }
            else if (lineNum == 1)
            {
                preLoadedGeneratorModel_1 = str.toInt();
            }
            else if (lineNum == 2)
            {
                preLoadedGeneratorModel_2 = str.toInt();
            }
            else if (str != balise1 && str != balise2 && str != balise3)
            {
                if (patchMapReached)
                {
                    int index = lineNum - model1Lines - model2Lines - 5;
                    pMap[index] = str.toInt();
                }
                else if (secondModelReached)
                {
                    int value = bin2dec(str.c_str());
                    param_F_Load[1][lineNum - 4 - model1Lines] = value;
                    if (model2Lines <= 69 || model2Lines >= 79)
                    {
                        if (param_F_Load[1][lineNum - 4 - model1Lines] > 127)
                        {
                          param_F_Load[1][lineNum - 4 - model1Lines] = 127;
                        }
                    }
                    model2Lines++;
                }
                else
                {
                    int value = bin2dec(str.c_str());
                    param_F_Load[0][lineNum - 3] = value;
                    if (model1Lines <= 69 || model1Lines >= 79)
                    {
                        if (param_F_Load[0][lineNum - 3] > 127)
                        {
                          param_F_Load[0][lineNum - 3] = 127;
                        }
                    }
                    model1Lines ++;
                }
            }
            lineNum ++;
        }
        // sdin.flush();
        sdin.close();
        saveLastPresetNum(presetNum_, bankNum_);
        return pName;
}

///////////////////////////////////////////////////////////////////// Binary to decimal ///////////////////////////////////////////////////////////////////////////////////////////

uint16_t Setting::bin2dec(const char *bin)
{
  uint16_t result=0;
  for(;*bin;bin++)
  {
    if((*bin!='0')&&(*bin!='1'))
      return -1;
    result=result*2+(*bin-'0');
    //if(result<=0) return -1;
  }
  return result;
}

///////////////////////////////////////////// Check for value confirmation by pressing a button (for preset, ban and models selection //////////////////////////////////////////////

uint16_t Setting::confirmValue(int bank_num, uint16_t knob_value, bool button_trigged)
{
    uint16_t num;
    if(button_trigged)
    {
        num = knob_value;
    }
    else
    {
        num = bank_num;
    }
    return num;
}

int Setting::getPolarity(int channel)
{
    return polarity[channel];
}
void Setting::setPolarity(int channel, int value)
{
   polarity[channel] = value;
}
int Setting::confirmModel(int current_num, int knob_value, bool button_trigged, int channel)
{
    int num;
    if(button_trigged)
    {
        buffModel = knob_value;
        buffModelNum = channel;
        num = current_num;
        confirmDialog = true;
    }
     else
    {
        num = current_num;
    }
    return num;
}
bool Setting::getConfirmDialog()
{
    return confirmDialog;
}
bool Setting::getConfirmSaving()
{
    return confirmSaving;
}
void Setting::loadDefaultLFO(int channel)
{
   paramArray[channel][0] = 76;
   paramArray[channel][1] = 0;
   paramArray[channel][2] = 0;
   paramArray[channel][3] = 0;
   paramArray[channel][4] = 0;
   paramArray[channel][5] = 0;
   paramArray[channel][6] = 0;
   paramArray[channel][7] = 0;
   paramArray[channel][8] = 0;
}
void Setting::loadDefaultEnv(int channel)
{
   paramArray[channel][0] = 1;
   paramArray[channel][1] = 60;
   paramArray[channel][2] = 52;
   paramArray[channel][3] = 127;
   paramArray[channel][4] = 1;
   paramArray[channel][5] = 127;
   paramArray[channel][6] = 127;
   paramArray[channel][7] = 127;
   paramArray[channel][8] = 127;
   paramArray[channel][9] = 0;
}
void Setting::loadDefaultBasslineEnv(int channel)
{
   paramArray[channel][0] = 1;
   paramArray[channel][1] = 60;
   paramArray[channel][2] = 0;
   paramArray[channel][3] = 90;
   paramArray[channel][4] = 1;
   paramArray[channel][5] = 127;
   paramArray[channel][6] = 90;
   paramArray[channel][7] = 90;
   paramArray[channel][8] = 127;
   paramArray[channel][9] = 90;
}
void Setting::loadDefaultSeq(int channel)
{
   const int paramInit[110]= {0b01111111,0b00000000,0b01111111,0b01111111,0b00101000,0b01111111,0b00101000,0b01111111,0b00010011,0b00001001,0b00011101,0b00000000,0b00000000,0b01111111,
   0b00000000,0b00111101,0b00001001,0b00100100,0b00000000,0b00000000,0b01111111,0b00000000,0b00101101,0b00010111,0b00011111,0b00000000,0b00000000,0b01111111,0b00000000,0b01010011,0b00011001,
   0b00100000,0b00000000,0b00000000,0b01111111,0b0000000,0b00000000,0b00000100,0b00100101,0b00000000,0b01010010,0b00011010,0b00011110,0b00000000,0b00010100,0b00100010,0b00000000,0b01010100,
   0b01000011,0b00010111,0b00000000,0b00001110,0b00011011,0b00000000,0b00000000,0b01111111,0b00000110,0b00000000,0b00001110,0b00011010,0b00000000,0b00000000,0b01111111,0b00000000,0b00000000,
   0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b1111010101001111,0b1111011011010111,0b1111011101010101,0b0000010011111111,0b1111111111111011,0b1111111111111111,
   0b1111111111111111,0b1111111111111111,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
   0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000001,0b00000001,0b00000000,0b00000000,0b00000000,0b00000000};
   for( int i = 0; i < 110; i++)
   {
       paramArray[channel][i] = paramInit[i];
   }
}
void Setting::loadDefaultClassicSeq(int channel)
{
   const int paramInit[110]= {0b01111111,0b00000000,0b01111111,0b01111111,0b00101000,0b01111111,0b00101000,0b01111111,0b00010011,0b00001001,0b00011101,0b00000000,0b00000000,0b00010000,
   0b00000000,0b00111101,0b00001001,0b00100100,0b00000000,0b00000000,0b01111111,0b00000000,0b00101101,0b00010111,0b00011111,0b00000000,0b00000000,0b01111111,0b00000000,0b01010011,0b00011001,
   0b00100000,0b00000000,0b00000000,0b01111111,0b0000000,0b00000000,0b00000100,0b00100101,0b00000000,0b01010010,0b00011010,0b00011110,0b00000000,0b00010100,0b00100010,0b00000000,0b01010100,
   0b01000011,0b00010111,0b00000000,0b00001110,0b00011011,0b00000000,0b00000000,0b01111111,0b00000110,0b00000000,0b00001110,0b00011010,0b00000000,0b00000000,0b01111111,0b00000000,0b00000000,
   0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b1111010101001111,0b1111011011010111,0b1111011101010101,0b0000010011111111,0b0111111111111011,0b0111111111111111,
   0b0111111111111111,0b0111111111111111,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
   0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000001,0b00000001,0b00000000,0b00000000,0b00000000,0b00000000};
   for( int i = 0; i < 110; i++)
   {
       paramArray[channel][i] = paramInit[i];
   }
   keyboardMode[channel] = false;
}
/////////////////////////////////////////////// Delock the knob if the value it returns is different enough from the value on last locking ////////////////////////////////////////////

void Setting::scanKnobLock(uint16_t *knobValue)
{
  for (int i = 0; i < 4; i++)
  {
    if (knobValue[i] > knobValueOnChange[i] + 10 || knobValue[i] < knobValueOnChange[i] - 10)
    {
      knobLocked[i] = false;
    }
  }
}

/////////////////////////////////////////////// Transfer the value from the array loaded from loadPreset(int presetNum_, int bankNum_) to those use by the cv processors ///////////

void Setting::transfertParams()
{
  generatorModel_1 = preLoadedGeneratorModel_1;
  generatorModel_2 = preLoadedGeneratorModel_2;
  tempGeneratorModel_1 = generatorModel_1;
  tempGeneratorModel_2 = generatorModel_2;
  for (int i = 0; i < paramLength[generatorModel_1]; i++)
  {
    paramArray[0][i] = getParamModel1(i);
  }
  for (int i = 0; i < paramLength[generatorModel_2]; i++)
  {
    paramArray[1][i] = getParamModel2(i);
  }
  for (int i = 0; i < 4; i++)
  {
    internalPatchMap[0][i] = pMap[i];
  }
  for (int i = 0; i < 4; i++)
  {
    internalPatchMap[1][i] = pMap[i + 4];
  }
  for (int i = 0; i < 4; i++)
  {
    internalPatchMap[2][i] = pMap[i + 8];
  }
  for (int i = 0; i < 4; i++)
  {
    internalPatchMap[3][i] = pMap[i + 12];
  }
  cvControlledParam[0][0] = paramArray[0][CV_PARAM1];
  cvControlledParam[1][0] = paramArray[0][CV_PARAM2];
  cvControlledParam[0][1] = paramArray[1][CV_PARAM1];
  cvControlledParam[1][1] = paramArray[1][CV_PARAM2];
  destPreset = presetNum;
}

/////////////////////////////////////////////// main setting (value setting for the main menu) /////////////////////////////////////////////////////////////////////////////////////

void Setting::mainSetting(bool *knobMoved, uint16_t *knobValue, bool *buttonTrigged)
{
    if (saving == false && confirmDialog == false && confirmSaving == false)
    {
        bool newBank = false; 
        mainButtonTrigCount = 0;
        if (knobMoved[0] && knobLocked[0] == false)
        {
            tempPresetNum  = knobValue[0] >> 2;

        }
        if (knobMoved[1] && knobLocked[1] == false)
        {
            tempBankNum = knobValue[1] >> 3;

        }
        if (knobMoved[2] && knobLocked[2] == false)
        {
            tempGeneratorModel_1 = modelOrder[int(knobValue[2]) / 36];
            
        }
        if (knobMoved[3] && knobLocked[3] == false)
        {
            tempGeneratorModel_2 = modelOrder[int(knobValue[3] / 36)];
           
        }
        if (bankNum != tempBankNum)
        {
          newBank = true;
          bankChangePeriod++;
        }
        if (presetNum != tempPresetNum)
        {
          presetChangePeriod++;
        }
        if (presetChangePeriod > KNOB_SET_PERIOD)
        {
          presetChangePeriod = 0;
          tempPresetNum = presetNum;
        }
         if (bankChangePeriod > KNOB_SET_PERIOD)
        {
          bankChangePeriod = 0;
          tempBankNum = bankNum;
        }
        if (tempGeneratorModel_1 != generatorModel_1)
        {
          model1ChangePeriod++;
        }
        if (model1ChangePeriod > KNOB_SET_PERIOD)
        {
          model1ChangePeriod = 0;
          tempGeneratorModel_1 = generatorModel_1;
        }
        if (tempGeneratorModel_2 != generatorModel_2)
        {
          model2ChangePeriod++;
        }
        if (model2ChangePeriod > KNOB_SET_PERIOD)
        {
          model2ChangePeriod = 0;
          tempGeneratorModel_2 = generatorModel_2;
        }
        
        presetNum = confirmValue(presetNum, tempPresetNum, buttonTrigged[0]);
        bankNum = confirmValue(bankNum, tempBankNum, buttonTrigged[0]);
        bool b1 = buttonTrigged[4];
        bool b2 = buttonTrigged[5];
        
        if (buttonTrigged[0])
        {
           Timer2.pause();
           if (newBank == true)
           {
            for (int i = 0; i < 32; i ++)
            {
              String preset_name_at_i = loadPreset(i, bankNum); 
              for (int j = 0; j < 11; j++)
              {
                preset_names[i][j] = preset_name_at_i[j];
              }
            }
           }
           loading = true;
        }
        if (buttonTrigged[1] && bankNum == tempBankNum)
        {
            tempPresetNum = presetNum;
            tempBankNum = bankNum;
            tempGeneratorModel_1 = generatorModel_1;
            tempGeneratorModel_2 = generatorModel_2;
            char charArray[12];
            for (int i = 0; i < 11; i++)
            {
              charArray[i] = preset_names[tempPresetNum][i];
            }
            String tempString(charArray);
            dispPresetName = tempString;
            routingMenuOpened = true;
            destPreset = presetNum;
        }
        if (tempPresetNum != previousPresetNum)
        {
            char charArray[12];
            for (int i = 0; i < 11; i++)
            {
              charArray[i] = preset_names[tempPresetNum][i];
            }
            String tempString(charArray);
            dispPresetName = tempString;
            presetChangePeriod = 0;
        }
        if (tempBankNum != previousBankNum)
        {
            bankChangePeriod = 0;
        }
        if (tempGeneratorModel_1 != previousGeneratorModel_1)
        {
          model1ChangePeriod = 0;
        }
        if (tempGeneratorModel_2 != previousGeneratorModel_2)
        {
          model2ChangePeriod = 0;
        }
        if (buttonTrigged[2] && tempGeneratorModel_1 == generatorModel_1)
        {
            tempGeneratorModel_2 = generatorModel_2;
            tempPresetNum = presetNum;
            tempBankNum = bankNum;
            char charArray[12];
            for (int i = 0; i < 11; i++)
            {
              charArray[i] = preset_names[tempPresetNum][i];
            }
            String tempString(charArray);
            dispPresetName = tempString;
            presetChangePeriod = 0;
            mainMenuOpened = false;
            currentMenu = generatorModel_1;
            page = 0;
            edit_channel = CHANNEL_A;
            knobLock(knobValue);
        }
        if (buttonTrigged[3] && tempGeneratorModel_2 == generatorModel_2)
        {
            tempGeneratorModel_1 = generatorModel_1;
            tempPresetNum = presetNum;
            tempBankNum = bankNum;
            for (int i = 0; i < 11; i++)
            {
              char charArray[12];
              charArray[i] = preset_names[tempPresetNum][i];
              String tempString(charArray);
              dispPresetName = tempString;
            }
            presetChangePeriod = 0;
            mainMenuOpened = false;
            currentMenu = generatorModel_2;
            page = 0;
            edit_channel = CHANNEL_B;
            knobLock(knobValue);
        }
        generatorModel_1 = confirmModel(generatorModel_1, tempGeneratorModel_1, b1, 0);
        generatorModel_2 = confirmModel(generatorModel_2, tempGeneratorModel_2, b2, 1);
        previousPresetNum = tempPresetNum;
        previousBankNum = tempBankNum;
        previousGeneratorModel_1 = tempGeneratorModel_1;
        previousGeneratorModel_2 = tempGeneratorModel_2;
    }
    else if (saving == true && confirmDialog == false && confirmSaving == false)
    {
        if (knobMoved[3])
        {
            destPreset = knobValue[3] / 4.0;
        }
        else if (knobMoved[2])
        {
            destPreset = knobValue[2] / 4.0;
        }
        if (buttonTrigged[1])
        {
            saving = false;
        }
        else if (buttonTrigged[6])
        {
            if (mainButtonTrigCount > 0 )
            {confirmSaving = true;}
            mainButtonTrigCount ++;
        }
    }
    else if (confirmDialog == true)
    {
        if (buttonTrigged[4] == true)
        {
            confirmDialog = false;
            if (buffModelNum == 0)
            {
                generatorModel_1 = buffModel;
                switch (generatorModel_1)
                {
                    case 0:
                        loadDefaultLFO(0);
                    break;
                    case 1:
                        loadDefaultEnv(0);
                    break;
                    case 2:
                        loadDefaultSeq(0);
                    break;
                    case 3:
                        loadDefaultClassicSeq(0);
                    break;
                    case 4:
                        loadDefaultBasslineEnv(0);
                    break;
                }
                polarity[0] = 0;
            }
            else
            {
                generatorModel_2 = buffModel;
                switch (generatorModel_2)
                {
                    case 0:
                        loadDefaultLFO(1);
                    break;
                    case 1:
                        loadDefaultEnv(1);
                    break;
                    case 2:
                        loadDefaultSeq(1);
                    break;
                    case 3:
                        loadDefaultClassicSeq(1);
                    break;
                    case 4:
                        loadDefaultBasslineEnv(1);
                    break;
                }
                polarity[1] = 0;
            }
        }
        else if (buttonTrigged[5] == true)
        {
            confirmDialog = false;

        }
    }
    else if (confirmSaving)
    {
        if (mainButtonTrigCount > 0 && buttonTrigged[4] == true)
        {
           Timer2.pause();
           setSavingState(false);
           savePreset(destPreset, bankNum, newPresetName);
           for (int i = 0; i < 32; i ++)
           {
             String preset_name_at_i = loadPreset(i, bankNum);
             for (int j = 0; j < 11; j++)
             {
                preset_names[i][j] = preset_name_at_i[j];
             }
           }
           dispPresetName = newPresetName;
           setSavingState(false);
           presetNum = destPreset;
           tempPresetNum = destPreset;
           confirmSaving = false;
           Timer2.resume();
        }
        else if (buttonTrigged[5])
        {
            setSavingState(false);
            confirmSaving = false;
        }
    }
}

///////////////////////////////////////////////////////////// store the knob Value on last locking //////////////////////////////////////////////////////////////////////////////////

void Setting::knobLock(uint16_t *knobValue)
{
  for(int i = 0; i < 4; i++)
  {
      knobLocked[i] = true;
      knobValueOnChange[i] = knobValue[i];
  }
}

////////////////////////////////////////////////////////////////////////// Setting for the internal patching menu //////////////////////////////////////////////////////////////////////

void Setting::routingSetting(bool *knobMoved, uint16_t *knobValue, bool *buttonTrigged)
{
        if (knobMoved[0] && knobLocked[0] == false)
        {
            currentPatchDest = int(knobValue[0] >> 5);
        }
        if (knobMoved[2] && knobLocked[2] == false)
        {
            currentPatchSource = int(knobValue[2] >> 5);
        }
        if (knobMoved[3] && knobLocked[3] == false)
        {
            currentPatchSource = int(knobValue[3] >> 5);
        }
        if (knobMoved[1] && knobLocked[1] == false)
        {
            currentPatchDest = int(knobValue[1] >> 5);
        }
        if (buttonTrigged[0] || buttonTrigged[2] || buttonTrigged[3])
        {
            internalPatchMap[currentPatchDest][currentPatchSource] = !internalPatchMap[currentPatchDest][currentPatchSource];
        }
        if (buttonTrigged[1])
        {
            routingMenuOpened = false;
            knobLock(knobValue);
        }
}

////////////////////////////// Return sequencer index, current internal patching destination/source, a value from the map of the internal patching, sequence number,... /////////////////

uint8_t Setting::getSeqIndex(uint8_t channel)
{
   return seqIndex[channel];
}

int Setting::getCurrentDest()
{
    return currentPatchDest;
}
int Setting::getCurrentSource()
{
    return currentPatchSource;
}

int Setting::getPatchMapItem(int dest, int source)
{
    return internalPatchMap[dest][source];
}

uint8_t Setting::getSeqNum(uint8_t channel)
{
    return seqNum[channel];
}

void Setting::setSeqNum(uint8_t channel, uint8_t num)
{
    seqNum[channel] = num;
}
bool Setting::getOctMode(uint8_t channel)
{
  return octMode[channel];
}

uint8_t Setting::getSubParam(uint8_t channel)
{
    return subParam[channel];
}

////////////////////////////////////////////////////////////////////// Setting for the LFO editing menu //////////////////////////////////////////////////////////////////////////////////

void Setting::LFOSetting(bool *knobMoved, uint16_t *knobValue, bool *buttonTrigged)
{
    commonSetting(knobMoved, knobValue, buttonTrigged, 0);
    if (knobMoved[1] && page == 0 && knobLocked[1] == false)
    {
        paramArray[edit_channel][MAIN_PARAM2] = knobValue[1];
    }
    switch (page)
    {
        case 0:
            if (buttonTrigged[1])
            {
                if (paramArray[edit_channel][LFO_SYNC] == 0)
                {
                    paramArray[edit_channel][LFO_SYNC] = 1;
                }
                else
                {
                    paramArray[edit_channel][LFO_SYNC] = 0;
                }
            }
        break;
    }
}

////////////////////////////////////////////////////////////////////// Setting for the sequencer editing menu ////////////////////////////////////////////////////////////////////////////

void Setting::SequencerSetting(bool *knobMoved, uint16_t *knobValue, bool *buttonTrigged)
{
  const int numberOfParams = 7;
  const int paramOffset = 8;
  const int paramOffsetForSeq = paramOffset + 8 * numberOfParams + numberOfParams;
  const int paramOffsetForClock = paramOffsetForSeq + 16 + 16;
  int floorParam = 0;
  floorParam = paramOffset + seqNum[edit_channel] * numberOfParams;
  
  if (buttonTrigged[0])
  {
    seqNum[edit_channel]++;
  }
  if (seqNum[edit_channel] > 7)
  {
    seqNum[edit_channel] = 0;
  }
  if (knobMoved[3] && knobLocked[3] == false)
  {
    seqEditPos[edit_channel] = knobValue[3] >> 3;
  }
  if (knobMoved[3] && knobLocked[3] == false)
  {
    seqIndex[edit_channel] = knobValue[3] >> 3; 
  }
  
  if (buttonTrigged[3])
  {
    uint16_t seq_length = paramArray[edit_channel][floorParam + 5] >> 3;
    uint16_t param_index = paramOffsetForSeq + seqNum[edit_channel];
    uint16_t current_shift = paramArray[edit_channel][floorParam + 3] >> 3;
    uint16_t index;
    
    if (seq_length + 1 > current_shift)
    {
      index = (seqIndex[edit_channel] + (current_shift))% (seq_length + 1); 
    }
    else
    {
      index = ((seqIndex[edit_channel] + (current_shift - (seq_length + 1)))); 
    }
    
    uint16_t rythmSeq = paramArray[edit_channel][param_index];
    uint16_t actBit = (rythmSeq & (1 << index)) >> index;
    
    if (actBit == 0)
    {
      paramArray[edit_channel][param_index] = (1 << index) | rythmSeq;
    }
    else
    {
      paramArray[edit_channel][param_index] = ~(1 << index) & rythmSeq;
    }
  }
  if (buttonTrigged[1])
  {
      octMode[edit_channel] = !octMode[edit_channel];
  }
  if (buttonTrigged[2])
  {
      subParam[edit_channel] ++;
  }
  if (subParam[edit_channel]  > 3)
  {
     subParam[edit_channel] = 0;
  }
  
  if (knobMoved[0] && knobLocked[0] == false)
  {
     int ind = floorParam + 0; //+ extraPnum;
     paramArray[edit_channel][ind] = knobValue[0] ;
  }
  if (knobMoved[1] && knobLocked[1] == false)
  {
     if (octMode[edit_channel] == false)
     {
       int ind = floorParam + 1; //+ extraPnum;
       paramArray[edit_channel][ind] = knobValue[1];
     }
     else
     {
       int ind = floorParam + 2; //+ extraPnum;
       paramArray[edit_channel][ind] = knobValue[1];
     }
  }
  if (knobMoved[2] && knobLocked[2] == false)
  {
     if (subParam[edit_channel] == SEQ_SHIFT)
     {
       int ind = floorParam + 3; //+ extraPnum;
       paramArray[edit_channel][ind] = knobValue[2];
     }
     else if (subParam[edit_channel] == SEQ_ORDER)
     {
       int ind = floorParam + 4; //+ extraPnum;
       paramArray[edit_channel][ind] = knobValue[2];
     }
     else if (subParam[edit_channel] == SEQ_LENGTH)
     {
       int ind = floorParam + 5; //+ extraPnum;
       paramArray[edit_channel][ind] = knobValue[2];
     }
     else if (subParam[edit_channel] == SEQ_REPEAT)
     {
       int ind = floorParam + 6; //+ extraPnum;
       paramArray[edit_channel][ind] = knobValue[2];
     }
  }
  if (buttonTrigged[4])
   {
      if (edit_channel == CHANNEL_A)
      {
          edit_channel = CHANNEL_B;
          currentMenu = generatorModel_2;
          knobLock(knobValue);
      }
      else if (edit_channel == CHANNEL_B)
      {
          edit_channel = CHANNEL_A;
          currentMenu = generatorModel_1;
          knobLock(knobValue);
      }
   }
  if (buttonTrigged[5])
  {
    paramArray[edit_channel][paramOffsetForClock + 2] = !paramArray[edit_channel][paramOffsetForClock + 2];
  }
}

void Setting::setNoteNum(int num)
{
  noteNum = num;
}

void Setting::classicSequencerSetting(bool *knobMoved, uint16_t *knobValue, bool *buttonTrigged, int seqPos1, int seqPos2)
{
  if (buttonTrigged[RIGHT_BUTTON])
  {
    knobLock(knobValue);
    if(page > 0)
    {
       page --;
    }
    else
    {
       page = 1;
    }
  }
  const int numberOfParams = 7;
  const int paramOffset = 8;
  const int paramOffsetForSeq = paramOffset + 8 * numberOfParams + numberOfParams;
  const int paramOffsetForClock = paramOffsetForSeq + 16 + 16;
  
  if (page == 0)
  {
    int floorParam = 0;
    if ((knobMoved[0] && knobLocked[0] == false) || keyboardMode[edit_channel] == true)
    {
        int num = paramOffset + 5; //+ extraPnum;
        if (keyboardMode[edit_channel] == false)
        {
          seqNum[edit_channel] = (knobValue[0] >> 3) * float (((paramArray[edit_channel][num]) + 1) / 16.0);
        }
        else
        {
          if (edit_channel == 0)
          {
            seqNum[edit_channel] = seqPos1; 
          }
          else
          {
            seqNum[edit_channel] = seqPos2; 
          }
        }
    }
    if(seqNum[edit_channel] > classicSeqLength[edit_channel])
    {
      seqNum[edit_channel] = classicSeqLength[edit_channel];
    }
    if ((knobMoved[1] && knobLocked[1] == false) || keyboardMode[edit_channel] == true)
    {
       if (seqNum[edit_channel] < 8)
       {
         floorParam = paramOffset + seqNum[edit_channel] * numberOfParams;
         int ind = floorParam + 0; //+ extraPnum;
         if (keyboardMode[edit_channel] == false)
         {
          paramArray[edit_channel][ind] = knobValue[1] / 4;
         }
         else
         {
          paramArray[edit_channel][ind] = noteNum;
         }
       }
       else
       {
         floorParam = paramOffset + (seqNum[edit_channel] - 8) * numberOfParams;
         int ind = floorParam + 1; //+ extraPnum;
         if (keyboardMode[edit_channel] == false)
         {
          paramArray[edit_channel][ind] = knobValue[1] / 4;
         }
         else
         {
          paramArray[edit_channel][ind] = noteNum;
         }
       }
    }
    if (knobMoved[2] && knobLocked[2] == false)
    {
       int ind = paramOffset + 4; //+ extraPnum;
       paramArray[edit_channel][ind] = (knobValue[2] / 5) + 10; 
    }
    if (knobMoved[3] && knobLocked[3] == false)
    {
       classicSeqLength[edit_channel] = knobValue[3] >> 3; 
       int ind = paramOffset + 5; //+ extraPnum;
       paramArray[edit_channel][ind] = knobValue[3] >> 3; 
    }
    if (buttonTrigged[0])
    {
      uint16_t param_index = paramOffsetForSeq + 0;
      uint16_t rythmSeq = paramArray[edit_channel][param_index];
      int seqPos_ = seqNum[edit_channel];
      uint16_t actBit = (rythmSeq & (1 << seqPos_)) >> seqPos_;
      if (actBit == 0)
      {
        paramArray[edit_channel][param_index] = (1 << seqPos_) | rythmSeq;
      }
      else
      {
        paramArray[edit_channel][param_index] = ~(1 << seqPos_) & rythmSeq;
      }
    }
    if (buttonTrigged[1])
    {
      uint16_t param_index = paramOffsetForSeq + 1;
      uint16_t rythmSeq = paramArray[edit_channel][param_index];
      int seqPos_ = seqNum[edit_channel];
      uint16_t actBit = (rythmSeq & (1 << seqPos_)) >> seqPos_;
      if (actBit == 0)
      {
        paramArray[edit_channel][param_index] = (1 << seqPos_) | rythmSeq;
      }
      else
      {
        paramArray[edit_channel][param_index] = ~(1 << seqPos_) & rythmSeq;
      }
    }
    if (buttonTrigged[4])
    {
      uint16_t param_index = paramOffsetForSeq + 2;
      uint16_t rythmSeq = paramArray[edit_channel][param_index];
      int seqPos_ = seqNum[edit_channel];
      uint16_t actBit = (rythmSeq & (1 << seqPos_)) >> seqPos_;
      if (actBit == 0)
      {
        paramArray[edit_channel][param_index] = (1 << seqPos_) | rythmSeq;
      }
      else
      {
        paramArray[edit_channel][param_index] = ~(1 << seqPos_) & rythmSeq;
      }
    }
    if (buttonTrigged[3])
    {
       edit_channel = CHANNEL_B;
       currentMenu = generatorModel_2;
       knobLock(knobValue);
    }
    if (buttonTrigged[2])
    {
      edit_channel = CHANNEL_A;
      currentMenu = generatorModel_1;
      knobLock(knobValue);
    }
  }
  else if (page == 1)
  {
    if (buttonTrigged[0])
    {
       seqDiv[edit_channel]++;
       if (seqDiv[edit_channel] > 7)
       {
          seqDiv[edit_channel] = 0;
       }
       int ind = paramOffset + 6; //+ extraPnum;
       paramArray[edit_channel][ind] = seqDiv[edit_channel];
    }
    if (buttonTrigged[1])
    {
      // --> keyboard mode keyboardMode[edit_channel] =!keyboardMode[edit_channel];
    }
    if (buttonTrigged[4])
    {
      readMode[edit_channel]++;
      if (readMode[edit_channel] > 2)
      {
         readMode[edit_channel] = 0;
      }
      int ind = paramOffset + 3; //+ extraPnum;
      paramArray[edit_channel][ind] = readMode[edit_channel] ;
    }
  }
}
////////////////////////////////////////////////////////////////////// Unused /////////////////////////////////////////////////////////////

void Setting::setTempoSetting(bool active)
{
  tempoSetting = active;
}
bool Setting::getKeyBoardMode(int channel_)
{
  // --> keyboard mode return keyboardMode[channel_];
  return false;
}
/////////////////////////////////////////////////////////// Setting for the envelope generator editing menu /////////////////////////////////

void Setting::envelopeSetting(bool *knobMoved,uint16_t *knobValue, bool *buttonTrigged)
{
    commonSetting(knobMoved, knobValue, buttonTrigged, 1);
    
    if (buttonTrigged[1] && page == 0)
    {
        secondKnobMode[edit_channel] ++;
        if (secondKnobMode[edit_channel] > 2)
        {
            secondKnobMode[edit_channel] = 0;
        }
    }
    if (knobMoved[1] && knobLocked[1] == false && page == 0)
    {
        if (secondKnobMode[edit_channel] == 1)
        {
            paramArray[edit_channel][8] = knobValue[1];
        }
        else if (secondKnobMode[edit_channel] == 2)
        {
            paramArray[edit_channel][9] = knobValue[1];
        }
        else if (secondKnobMode[edit_channel] == 0)
        {
            paramArray[edit_channel][MAIN_PARAM2] = knobValue[1];
        }
    }
}

void Setting::bassLineEnvSetting(bool *knobMoved,uint16_t *knobValue, bool *buttonTrigged)
{
    if (buttonTrigged[1] && page == 0)
    {
        secondKnobMode[edit_channel] ++;
        if (secondKnobMode[edit_channel] > 2)
        {
            secondKnobMode[edit_channel] = 0;
        }
    }
    paramArray[edit_channel][INT_CV_PARAM1 + 0] = 0;
    paramArray[edit_channel][INT_CV_PARAM1 + 1] = 0;
    const int paramOffset = 8;
    const int numberOfParams = 7;
    const int paramOffsetForSeq = paramOffset + 8 * numberOfParams + numberOfParams;
    if ((generatorModel_2 == 3 && edit_channel == 0) || (generatorModel_1 == 3 && edit_channel == 1))
    {
      if (knobMoved[0] && knobLocked[0] == false)
      {
          int num = paramOffset + 5; //+ extraPnum;
          if (edit_channel == 0)
          {
            seqNum[edit_channel] = (knobValue[0] >> 3) * float (((paramArray[1][num]) + 1) / 16.0);
          }
          else if (edit_channel == 1)
          {
            seqNum[edit_channel] = (knobValue[0] >> 3) * float (((paramArray[0][num]) + 1) / 16.0);
          }
      }
      if (buttonTrigged[0])
      {
        if (edit_channel == 0 && generatorModel_2 == 3)
        {
          uint16_t param_index = paramOffsetForSeq + 3;
          uint16_t accSeq = paramArray[1][param_index];
          int seqPos_ = seqNum[edit_channel];
          uint16_t actBit = (accSeq & (1 << seqPos_)) >> seqPos_;
          if (actBit == 0)
          {
            paramArray[1][param_index] = (1 << seqPos_) | accSeq;
          }
          else
          {
            paramArray[1][param_index] = ~(1 << seqPos_) & accSeq;
          }
        }
        else if (edit_channel == 1 && generatorModel_1 == 3)
        {
          uint16_t param_index = paramOffsetForSeq + 3;
          uint16_t rythmSeq = paramArray[0][param_index];
          int seqPos_ = seqNum[edit_channel];
          uint16_t actBit = (rythmSeq & (1 << seqPos_)) >> seqPos_;
          if (actBit == 0)
          {
            paramArray[0][param_index] = (1 << seqPos_) | rythmSeq;
          }
          else
          {
            paramArray[0][param_index] = ~(1 << seqPos_) & rythmSeq;
          }
        }
      }
    }
    if (knobMoved[0] && knobLocked[0] == false)
    {
        paramArray[edit_channel][MAIN_PARAM1] = knobValue[0];
    }
     if (knobMoved[2] && knobLocked[2] == false)
    {
       paramArray[edit_channel][MAIN_PARAM3] = knobValue[2];
    }
    if (knobMoved[3] && knobLocked[3] == false)
    {
        paramArray[edit_channel][MAIN_PARAM4] = knobValue[3];
    }
    if (knobMoved[1] && knobLocked[1] == false)
    {
        if (secondKnobMode[edit_channel] == 1)
        {
            paramArray[edit_channel][8] = knobValue[1];
        }
        else if (secondKnobMode[edit_channel] == 2)
        {
            paramArray[edit_channel][9] = knobValue[1];
        }
        else if (secondKnobMode[edit_channel] == 0)
        {
            paramArray[edit_channel][MAIN_PARAM2] = knobValue[1];
        }
    }
    if (buttonTrigged[0])
    {
        reset[edit_channel] = true;
     }
    if (buttonTrigged[2])
    {
        edit_channel = CHANNEL_A;
        currentMenu = generatorModel_1;
        knobLock(knobValue);
     }
     if (buttonTrigged[3])
     {
        edit_channel = CHANNEL_B;
        currentMenu = generatorModel_2;
        knobLock(knobValue);
     }
}

//////////////////////////////////////////////// Common setting (for the LFO and the envelope generator models ///////////////////////////////

void Setting::commonSetting(bool *knobMoved,uint16_t *knobValue, bool *buttonTrigged, int model)
{
    cvControlledParam[0][0] = paramArray[0][CV_PARAM1];
    cvControlledParam[1][0] = paramArray[0][CV_PARAM2];
    cvControlledParam[0][1] = paramArray[1][CV_PARAM1];
    cvControlledParam[1][1] = paramArray[1][CV_PARAM2];
    switch (page)
    {
        case 0:
            if (knobMoved[0] && knobLocked[0] == false)
            {
                paramArray[edit_channel][MAIN_PARAM1] = knobValue[0];
            }
            if (knobMoved[2] && knobLocked[2] == false)
            {
                paramArray[edit_channel][MAIN_PARAM3] = knobValue[2];
            }
            if (knobMoved[3] && knobLocked[3] == false)
            {
                paramArray[edit_channel][MAIN_PARAM4] = knobValue[3];
            }
            if (buttonTrigged[0])
            {
                reset[edit_channel] = true;
            }
            if (buttonTrigged[2])
            {
                edit_channel = CHANNEL_A;
                currentMenu = generatorModel_1;
                knobLock(knobValue);
            }
            if (buttonTrigged[3])
            {
                edit_channel = CHANNEL_B;
                currentMenu = generatorModel_2;
                knobLock(knobValue);
            }
        break;
        case 1:
            for (int i = 0; i < 2; i++)
            {
                if (knobMoved[i])
                {
                    paramArray[edit_channel][CV_PARAM1 + i] = knobValue[i] / 32.0;
                }
                if (knobMoved[i + 2])
                {
                    paramArray[edit_channel][INT_CV_PARAM1 + i] = knobValue[i + 2];
                }
            }
        break;
    }

    if (buttonTrigged[LEFT_BUTTON])
    {
      knobLock(knobValue);
        if(page > 0)
        {
            page --;
        }
        else
        {
            page = numberOfPages[model] - 1;
        }
    }
    if (buttonTrigged[RIGHT_BUTTON])
    {
        polarity[edit_channel]++;
        if (edit_channel == 0)
        {
            if (polarity[edit_channel] >= polarOptions[generatorModel_1])
            {
                polarity[edit_channel] = 0;
            }
        }
        else
        {
            if (polarity[edit_channel] >= polarOptions[generatorModel_2])
            {
               polarity[edit_channel] = 0;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////// Return a value to know if the first preset has been loaded /////////////

bool Setting::firstPresetLoaded()
{
  return first_preset_loaded;
}

///////////////////////////////////////////////// Load a new preset from the SD card, set loading boolean to false and resume the timer ///////

void Setting::load()
{
  dispPresetName = loadPreset(tempPresetNum, tempBankNum);
  loading = false;
  Timer2.resume();
}

////////////////////////////////////////////////////////////////////////////////// Getters and setters /////////////////////////////////////////

void Setting::setPresetName(String presetName)
{
    newPresetName = presetName;
}

bool Setting::isSaving()
{
    return saving;
}

bool Setting::isLoading()
{
   return loading;
}

void Setting::setSavingState(bool state)
{
    if (state == true)
    {
       tempPresetNum = presetNum;
       tempBankNum = bankNum;
       tempGeneratorModel_1 = generatorModel_1;
       tempGeneratorModel_2 = generatorModel_2;
    }
    saving = state;
}
int Setting::getParamModel1(int index)
{
    return param_F_Load[0][index];
}

int Setting::getParamModel2(int index)
{
    return param_F_Load[1][index];
}

int Setting::getSecondKnobMode(int channel)
{ 
    return secondKnobMode[channel];
}

int Setting::getCurrentMenu()
{
    return currentMenu;
}
int Setting::getDestinationPreset()
{
    return destPreset;
}

bool Setting::getMainMenuOpened()
{
    return mainMenuOpened;
}
bool Setting::getRoutingMenuOpened()
{
    return routingMenuOpened;
}

int Setting::getParamArray(int channel, int index)
{
    return paramArray[channel][index];
}

int Setting::getModel_1()
{
    return generatorModel_1;
}

int Setting::getModel_2()
{
    return generatorModel_2;
}
void Setting::setMainMenuOpened(bool open)
{
    mainMenuOpened = open;
}

void Setting::setRoutingMenuOpened(bool open)
{
    routingMenuOpened = open;
}

int Setting::getEditChannel()
{
    return edit_channel;
}

bool Setting::get_reset(int channel)
{
    return reset[channel];
}

void Setting::set_reset(int channel, bool active)
{
    reset[channel] = active;
}

int Setting::getTempBankNum()
{
    return tempBankNum;
}
int Setting::getBankNum()
{
    return bankNum;
}

int Setting::getTempPresetNum()
{
    return tempPresetNum;
}

int Setting::getPresetNum()
{
    return presetNum;
}

int Setting::getPage()
{
    return page;
}

int Setting::getCVControlledParam(int index, int channel)
{
    return cvControlledParam[index][channel];
}

int Setting::getTempGeneratorModel_1()
{
    return tempGeneratorModel_1;
}

int Setting::getTempGeneratorModel_2()
{
    return tempGeneratorModel_2;
}

String Setting::getDispPresetName()
{
    return dispPresetName;
}
