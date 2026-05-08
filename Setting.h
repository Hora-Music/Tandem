// Copyright 2020 Raphaël Hoffman.
//
// Author: Raphaël Hoffman (hora.music.contact@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// 
//
// -----------------------------------------------------------------------------
//
// Tandem, multimode CV generator.
#include "Arduino.h"
#include "SdFat.h"
#include "sdios.h"
#define LEFT_BUTTON 4
#define RIGHT_BUTTON 5
#define MAIN_PARAM1 0
#define MAIN_PARAM2 1
#define MAIN_PARAM3 2
#define MAIN_PARAM4 3
#define CV_PARAM1 4
#define CV_PARAM2 5
#define INT_CV_PARAM1 6
#define INT_CV_PARAM2 7
#define CHANNEL_A 0
#define CHANNEL_B 1
#define LFO_SYNC 8
#define SEQ_SHIFT 0
#define SEQ_ORDER 1
#define SEQ_LENGTH 2
#define SEQ_REPEAT 3
#define KNOB_SET_PERIOD 5000
/*#define ENV 0
#define LFO 1
#define HARMO_SEQ 2
#define BASSLINE_SEQ 3
#define BASSLINE_ENV 4*/

const uint8_t SD1_CS = PA11; 



/*SPIClass SPI_2B(2);
SdFat sd1(&SPI_2B);*/

class Setting {
private:
    int presetChangePeriod;
    int bankChangePeriod;
    int model1ChangePeriod;
    int model2ChangePeriod;
    char preset_names[33][12];
    String name1;
    String name2;
    String dispPresetName;
    String newPresetName;
    int paramArray[2][110];
    int param_F_Load[2][110];
    bool internalPatchMap[4][4];
    int pMap[16];
    int polarity[2];
    int currentPatchSource;
    int currentPatchDest;
    bool dual;
    int tempPresetNum ;
    int tempBankNum;
    int presetNum;
    int bankNum;
    int previousPresetNum;
    int previousBankNum;
    int preLoadedGeneratorModel_1;
    int preLoadedGeneratorModel_2;
    int tempGeneratorModel_1;
    int tempGeneratorModel_2;
    int generatorModel_1;
    int generatorModel_2;
    int previousGeneratorModel_1;
    int previousGeneratorModel_2;
    bool reset[2];
    int currentMenu;
    int edit_channel;
    int page;
    int paramLength[8];
    int numberOfPages[8];
    int cvControlledParam[2][2];
    int secondKnobMode[2];
    bool mainMenuOpened;
    bool routingMenuOpened;
    int charCount = 0;
    bool saving;
    bool loading;
    int destPreset;
    int last_preset_num;
    int last_bank_num;
    uint8_t mainButtonTrigCount;
    bool knobLocked[4];
    uint16_t knobValueOnChange[4];
    bool first_preset_loaded;
    uint8_t seqNum[2];
    uint8_t seqEditPos[2];
    uint8_t subParam[2];
    bool octMode[2];
    uint8_t seqIndex[2];
    int polarOptions[3];
    bool tempoSetting;
    bool modelChanged;
    bool confirmDialog;
    int buffModel;
    int buffModelNum;
    bool confirmSaving;
    uint8_t readMode[2];
    uint8_t seqDiv[2];
    uint8_t classicSeqLength[2];
    uint8_t modelOrder[5];
    bool keyboardMode[2];
    int noteNum;
public:
    Setting() :
      presetChangePeriod(0),
      bankChangePeriod(0),
      model1ChangePeriod(0),
      model2ChangePeriod(0),
      preset_names(),
      name1(),
      name2(),
      dispPresetName(),
      newPresetName(),
      paramArray(),
      param_F_Load(),
      internalPatchMap(),
      pMap(),
      polarity(),
      currentPatchSource(0),
      currentPatchDest(0),
      dual(false),
      tempPresetNum(0),
      tempBankNum(0),
      presetNum(0),
      bankNum(0),
      previousPresetNum(0),
      previousBankNum(0),
      preLoadedGeneratorModel_1(0),
      preLoadedGeneratorModel_2(0),
      tempGeneratorModel_1(0),
      tempGeneratorModel_2(0),
      generatorModel_1(0),
      generatorModel_2(0),
      previousGeneratorModel_1(0),
      previousGeneratorModel_2(0),
      reset(),
      currentMenu(0),
      edit_channel(0),
      page(0),
      paramLength(),
      numberOfPages(),
      cvControlledParam(),
      secondKnobMode(),
      mainMenuOpened(false),
      routingMenuOpened(false),
      charCount(0),
      saving(false),
      loading(false),
      destPreset(0),
      last_preset_num(0),
      last_bank_num(0),
      mainButtonTrigCount(0),
      knobLocked(),
      knobValueOnChange(),
      first_preset_loaded(false),
      seqNum(),
      seqEditPos(),
      subParam(),
      octMode(),
      seqIndex(),
      polarOptions(),
      tempoSetting(false),
      modelChanged(false),
      confirmDialog(false),
      buffModel(0),
      buffModelNum(0),
      confirmSaving(false),
      readMode(),
      seqDiv(),
      classicSeqLength(),
      modelOrder(),
      keyboardMode(),
      noteNum()
		      {

		      };
    void init();
    uint16_t bin2dec(const char *bin);
    uint8_t getSeqNum(uint8_t channel);
    uint8_t getSeqIndex(uint8_t channel);
    void setSeqNum(uint8_t channel, uint8_t num);
    bool getSeqMode(uint8_t channel);
    bool getOctMode(uint8_t channel);
    uint8_t getSubParam(uint8_t channel);
    void knobLock(uint16_t *knobValue);
    void scanKnobLock(uint16_t *knobValue);
    String loadPreset(int presetNum, int bankNum);
    int getModel_1();
    int getModel_2();
    void mainSetting(bool *knobMoved, uint16_t *knobValue, bool *buttonTrigged);
    void LFOSetting(bool *knobMoved,uint16_t *knobValue, bool *buttonTrigged);
    void envelopeSetting(bool *knobMoved,uint16_t *knobValue, bool *buttonTrigged);
    void SequencerSetting(bool *knobMoved, uint16_t *knobValue, bool *buttonTrigged);
    void classicSequencerSetting(bool *knobMoved, uint16_t *knobValue, bool *buttonTrigged, int seqPos1, int seqPos2);
    void bassLineEnvSetting(bool *knobMoved,uint16_t *knobValue, bool *buttonTrigged);
    //void sequencerSetting(bool *knobMoved,uint16_t *knobValue, bool *buttonTrigged, bool buttonValue3);
    uint16_t confirmValue(int bank_num, uint16_t knob_value, bool button_trigged);
    int getCurrentMenu();
    bool getMainMenuOpened();
    bool getRoutingMenuOpened();
    void setMainMenuOpened(bool open);
    void setRoutingMenuOpened(bool open);
    void set_reset(int channel, bool active);
    void setTempoSetting(bool active);
    int getParamArray(int model, int index);
    int getParamModel1(int index);
    int getParamModel2(int index);
    int getEditChannel();
    bool get_reset(int channel);
    bool isSaving();
    int getTempBankNum();
    int getBankNum();
    int getTempPresetNum();
    int getPresetNum();
    int getPage();
    int getTempGeneratorModel_1();
    int getTempGeneratorModel_2();
    int getCVControlledParam(int index, int channel);
    void commonSetting(bool *knobMoved,uint16_t *knobValue, bool *buttonTrigged, int model);
    int getSecondKnobMode(int channel);
    void savePreset(int c_presetNum, int c_bankNum, String c_dispPresetName);
    void setSavingState(bool state);
    void presetNameWriting(bool *buttonTrigged);
    void setPresetName(String presetName);
    int getDestinationPreset();
    void routingSetting(bool *knobMoved, uint16_t *knobValue, bool *buttonTrigged);
    int getCurrentDest();
    int getCurrentSource();
    int getPatchMapItem(int dest, int source);
    String getDispPresetName();
    void setLastPresetNum();
    void saveLastPresetNum(int presetNum_, int bankNum_);
    bool isLoading();
    void load();
    bool firstPresetLoaded();
    void transfertParams();
    int getPolarity(int channel);
    void setPolarity(int channel, int value);
    bool getConfirmDialog();
    bool getConfirmSaving();
    int confirmModel(int current_num, int knob_value, bool button_trigged, int channel);
    void loadDefaultLFO(int channel);
    void loadDefaultEnv(int channel);
    void loadDefaultClassicSeq(int channel);
    void loadDefaultSeq(int channel);
    void loadDefaultBasslineEnv(int channel);
    bool getKeyBoardMode(int channel);
    void setNoteNum(int num);
    void saveCvTable(uint16_t cvTable[2][120], String tableName, int index);
    void loadCvTable(uint16_t cvTable[2][120], int index);
    void initCvTableName(int index);
    String getCvTableName(int index);
    bool getDeviceReady();
};
