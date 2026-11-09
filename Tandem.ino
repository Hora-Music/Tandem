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

/*
          O
        Extras
 
    O            O
   Tables    Table calib
    O            O
  Table calib
    O            O 
  Tables      CV calib
  
*/

//#include <MIDI.h>
#include "Arduino.h"
//#include <tone.h>
#include <Wire.h>                                                                             // External libraries
#include <STM32ADC.h>
#include <arduino.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <SH1106.h>
//#include "HardwareSerial.h"
//#include <SoftSerialSTM32.h>   


//MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midi2);
//SoftWire SWire(PA13, PA14, SOFT_FAST);
//#include <FixedPoints.h>
//#include <FixedPointsCommon.h>
//#include "MegunoLink.h"
#include "Filter.h" // MLP-master lib
#include "util.h"
#include "GC_controlScan.h"
#include "pinAssign.h"
#include "Setting.h" 
#include "GC_CV_mixer.h"                                                                       // Original libraries especially made for tandem
#include "GC_Sequencer.h"
#include "GC_StepSequencer.h"
#include "GC_OctaLFO.h"
#include "GC_gate_mixer.h"
#include "GC_Envelope.h"
//#include "pitches.h"

#define BUFF_OVERLOAD_DISPLAY false
#define MIDI_IN               false   // and set OLED_CS in pinAssing.h
//const uint8_t CLOCK_PIN[] = {PA8};


int amplitudeCv = 0;
boolean wasTuned = false;
boolean mount = false;
boolean bassON = false;
int bassPitch = 0;
byte bassNoteCount = 0;
byte noteCount = 0;
float bendfactor = 1;

/////////////////////////////////////////////////////////////////////////////////////// Instantiate/init objects ////////////////////////////////////////////////////////////////////////////////

SPIClass SPI_2(2);                    
//extern HardwareSerial Serial2; // serial2 depending on the lib used 
//SoftSerialSTM32 SWSerial0(PA3, PA15);
STM32ADC myADC(ADC1);
uint8 pins[] = {PA2,PA0,PA1,PA4, PB0, PB1};
Adafruit_SH1106 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
//MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midi2);
const int maxSamples = 6;
const int logoDuration = 4500;
uint16_t dataPoints[maxSamples];
ExponentialFilter<long> ADCFilterCV1(2, 0);
ExponentialFilter<long> ADCFilterCV2(2, 0);
ExponentialFilter<long> ADCFilterCV3(2, 0);
ExponentialFilter<long> ADCFilterCV4(2, 0);
ExponentialFilter<long> ADCFilterCV5(8, 0);
ExponentialFilter<long> ADCFilterCV6(8, 0);
ExponentialFilter<float> accentFilter1(98, 0);
ExponentialFilter<float> accentFilter2(98, 0);
//ExponentialFilter<long> scopeFilter1(24, 0);
GC_controlScan *controlScanner = new GC_controlScan();
util *utilities = new util();
pinAssign *pinSetting = new pinAssign();
Setting *setting = new Setting();
GC_CV_mixer *CVmixer = new GC_CV_mixer();
GC_OctaLFO *multiLFO[2] = {new GC_OctaLFO(), new GC_OctaLFO()};
GC_Envelope *ADSR[2] = {new GC_Envelope(), new GC_Envelope()};
GC_Envelope *accentEnvelope[2] = {new GC_Envelope(), new GC_Envelope()};
GC_gate_mixer *gateMixer = new GC_gate_mixer();
GC_Sequencer *sequencer[2] = {new GC_Sequencer(), new GC_Sequencer()};
GC_StepSequencer *stepSequencer[2] = {new GC_StepSequencer(), new GC_StepSequencer()};

//////////////////////////////////////////////// (buffer size: bigger buffer gives higher priority to the CV generator process, smaller buffer gives higher display refreshing priority //////////////////////////////////

const int BUFFER_SIZE = 32; 

//////////////////////////////////////////////////////////////////////////////////////////// Volatile variables ////////////////////////////////////////////////////////////////////////////////////////////////

volatile uint8_t trig_in_buffers[BUFFER_SIZE][2] ;
volatile uint16_t analog_in_buffers[64][6];
volatile uint16_t output_buffer_A[BUFFER_SIZE] = {0};
volatile uint16_t output_buffer_B[BUFFER_SIZE] = {0};
volatile uint8_t trig_output_buffer_A[BUFFER_SIZE] = {0};
volatile bool reset_A[BUFFER_SIZE] = {false};
volatile bool reset_B[BUFFER_SIZE] = {false};
volatile uint8_t trig_output_buffer_B[BUFFER_SIZE] = {0};
volatile bool input_buff_completely_read = false;
volatile bool input_buff_overload = false;
volatile bool output_buff_completely_written = false;
volatile bool output_buff_overload = false;
volatile uint8_t input_buff_head = 0;
volatile uint8_t input_buff_tail = 0;
volatile uint8_t output_buff_head = 0;
volatile uint8_t output_buff_tail = 0;
volatile uint16_t frameCount = 0;
volatile bool blinkState = false;
volatile uint16_t tempo = 10;
volatile uint16_t clockPhase = 0;
volatile uint16_t seqCvCalibrationTimer = 0;
volatile uint8_t seqCvCalibrationIndex = 0;
volatile uint8_t seqCvCalibrationVoltage1 = 0;
volatile uint8_t seqCvCalibrationVoltage2 = 0;
volatile uint8_t previousCalibVoltage1 = 0;
volatile uint8_t previousCalibVoltage2 = 0;
volatile bool calibDoublon1 = false;
volatile bool calibDoublon2 = false;
volatile bool fff = true;
uint16_t output_buffer_A_sample = 0;
uint16_t output_buffer_B_sample = 0;

//////////////////////////////////////////////////////////////////////////////////////////// Global variables //////////////////////////////////////////////////////////////////////////////////////////////////

bool scope_mode;
byte CV_accuracy_comp[2] = {0, 0};
byte CV_accuracy_comp_sign[2] = {0, 0};
uint16_t knobValue[6];
int param_mix[4][2];
float s_phase[2];
float phase[2]= {0.0, 0.0};
float t_pos[2];
float param_t_pos1 = 0;
float param_t_pos2 = 0;
float param_CV_mix_4B = 0;
float param_CV_mix_4A = 0;
float CV_int[2][2];
uint16_t staticScopeBuffer[128] = {0};
bool buttonValue[6] = {false, false, false, false, false, false};
bool buttonTrigged[7] = {false, false, false, false, false, false, false};
bool effectiveTrigged[7] = {false, false, false, false, false, false, false};
bool triggerInputValue[2];
bool knobMoved[4] = {false, false, false, false};
bool knobWasMoved[4] = {false, false, false, false};
float rate = 0.02;
float LFO_phase = 0;
int routingMap[4][4];
uint16_t output_A = 0;
uint16_t output_B = 0;
uint16_t gate_out1;
uint16_t gate_out2;
float rawEnvOut1 = 0;
float rawEnvOut2 = 0;
bool tableLoaded = false;
bool unlockButton[7] = {false, false, false, false, false, false, false};
bool firstFrame = true;
bool onSet = false;
int bankNum = 0;
int presetNum = 0;
uint8_t stringPos = 0;
String presetName_D = "";
bool firstSaveMenuFrame = true;
uint8_t mainButtonTrigCount = 1;
uint16_t destArray[2][2];
int gate_input[2];
int CV_input[2];
uint8_t trigInit_1 = 0;
uint8_t trigInit_2 = 0;
bool prevBut_0 = 0;
uint8_t prevKnob2;
bool button_4_hold = false;
uint16_t button_4_hold_count = 0;
bool externAccentState[2] = {false};
bool externSlideState[2] = {false};
bool seqCvCalibration = false;
bool waitingForCvCalibration = false;
bool calibrationConfirmed = false;
bool calibrationMode = false;                                                                  
uint16_t calibFrameCount = 0;
//uint8_t seqCvTable[60] = {0};

volatile uint16_t previousMeasure[2] = {0, 0};
volatile uint16_t measureStabity[2] = {0, 0};
volatile uint16_t bestSeqCalibCandidate[2] = {0, 0};
volatile uint16_t biggestMeasureStabity[2] = {0, 0};
volatile uint16_t secondSeqCalibCandidate[2] = {0, 0};
volatile uint16_t secondChoiceMeasureStabity[2] = {0, 0};
volatile uint16_t measureCalibCount[2] = {0, 0};
volatile uint16_t bestCandidate1 = 0;
volatile uint16_t bestCandidate2 = 0;
volatile uint16_t secondCandidate1 = 0;
uint16_t secondCandidate2 = 0;
bool seqCalibValueSet[2][2] = {{0, 0}, {0, 0}};
uint16_t bestCandidates[60][2] = {{0}, {0}};
uint16_t secondCandidates[60][2]  = {{0}, {0}};
uint16_t lowSecondCandidates[60][2] = {{0}, {0}};
uint16_t highSecondCandidates[60][2] = {{0}, {0}};
int tot = 1;
int tot_ = 1;
int midiInMessage;
int noteOnMessage;
int noteOffMessage;
int velocityMessage;
bool nextIsNoteOn = false;
bool nextIsNoteOff = false;
bool nextIsVelocity = false;
bool noteWritten = false;
bool isKeyPressed = false;
bool prevKbMode[2] = {false, false};
int blinkCounter = 0;
bool ledBlink = false;
bool tunerMode = false;
volatile int inc = 0;
uint16_t newData = 0;
uint16_t prevData = 0;

uint16_t newData2 = 0;
uint16_t prevData2 = 0;

//freq variables
unsigned int timer = 0;//counts period of wave
unsigned int timer_2 = 0;//counts period of wave
unsigned int period = 8;
int tunerFrequency;
int tunerFrequency2;
unsigned int period2 = 8;
int restartButtonCounter = 0;
String note_s = "ff"; 
String note_s_2 = "ff"; 
int scopePos = 0;
volatile bool forceDisplay = false;
volatile uint8_t prevGateIn_ = 0;
volatile uint8_t prevGateIn_2 = 0;
uint8_t gateIn_ = 0;
uint8_t gateIn_2 = 0;
bool extraModesButtonReady = true;
int scopeRate = 1;
int extraMode = 0;
const int TUNER = 0;
const int SCOPE = 1;
const int VOLTMETER = 2;
const int VCO = 3;
bool seqKeyModeTrigDetect;
int probingFreqIndex = 0;
volatile bool CvOutCalib = false;
volatile int index1 = 0;
int probingCV = 0;
int tuningDurationCount = 0;
const int CvTuningDuration = 1;
int macthingIndex = 0;
int prevMeasuredFreq = 100; 
int measureIndex = 0;
volatile int chan;
volatile int cvValueForCalib = 4095;
volatile bool valueHasChanged = true;
volatile int subState1 = 0;
volatile bool flipFlop1 = true;
volatile uint8_t flipCount1;
volatile int subState2 = 0;
volatile bool flipFlop2 = true;
volatile uint8_t flipCount2;
volatile float VCO_phase = 0.0f;
uint16_t cvOutTable[2][120];
int prevCvValueForCalib = 0;
bool cvOutcalibrationFinished = false;
int lastSavedFreq = 0;
volatile float M1 = 1.0f;
volatile float M2 = 1.0f;
volatile float M1_ = 1.0f;
volatile float M2_ = 1.0f;
volatile float d1 = 1.0f;
volatile float d2 = 1.0f;
volatile bool controlFrame = true;
const uint16_t cvNotesFromKb[60] = {513, 522, 530, 539, 547, 556, 564, 573, 581, 590, 598, 607, 615, 624, 632, 641, 649, 658, 666, 675, 683,
                               692, 700, 709, 717, 726, 734, 743, 751, 760, 768, 777, 785, 794, 802, 811, 819, 828, 836, 845, 853, 862, 870, 879, 889, 897, 905, 913, 921, 930, 938, 947, 957, 964, 972, 981, 990, 999, 1007, 1014};

uint16_t noteFrequencies[104] = {
    // Octave 0
    164,  // C0
    173,  // C#0/Db0
    184,  // D0
    194,  // D#0/Eb0
    206,  // E0
    218,  // F0
    231,  // F#0/Gb0
    245,  // G0
    260,  // G#0/Ab0
    275,  // A0
    291,  // A#0/Bb0
    309,  // B0

    // Octave 1
    327,  // C1
    347,  // C#1/Db1
    367,  // D1
    389,  // D#1/Eb1
    412,  // E1
    436,  // F1
    463,  // F#1/Gb1
    490,  // G1
    519,  // G#1/Ab1
    550,  // A1
    583,  // A#1/Bb1
    617,  // B1

    // Octave 2
    654,  // C2
    693,  // C#2/Db2
    734,  // D2
    778,  // D#2/Eb2
    824,  // E2
    873,  // F2
    925,  // F#2/Gb2
    980,  // G2
    1038, // G#2/Ab2
    1100, // A2
    1165, // A#2/Bb2
    1235, // B2

    // Octave 3
    1308, // C3
    1386, // C#3/Db3
    1468, // D3
    1556, // D#3/Eb3
    1648, // E3
    1746, // F3
    1850, // F#3/Gb3
    1960, // G3
    2076, // G#3/Ab3
    2200, // A3
    2331, // A#3/Bb3
    2470, // B3

    // Octave 4
    2616, // C4
    2772, // C#4/Db4
    2937, // D4
    3111, // D#4/Eb4
    3296, // E4
    3492, // F4
    3700, // F#4/Gb4
    3920, // G4
    4153, // G#4/Ab4
    4400, // A4
    4662, // A#4/Bb4
    4939, // B4

    // Octave 5
    5233, // C5
    5544, // C#5/Db5
    5873, // D5
    6223, // D#5/Eb5
    6592, // E5
    6985, // F5
    7400, // F#5/Gb5
    7840, // G5
    8306, // G#5/Ab5
    8800, // A5
    9323, // A#5/Bb5
    9878, // B5

    // Octave 6
    10465, // C6
    11087, // C#6/Db6
    11747, // D6
    12445, // D#6/Eb6
    13185, // E6
    13969, // F6
    14799, // F#6/Gb6
    15680, // G6
    16612, // G#6/Ab6
    17600, // A6
    18647, // A#6/Bb6
    19755, // B6

    // Octave 7
    20930, // C7
    22175, // C#7/Db7
    23493, // D7
    24890, // D#7/Eb7
    26370, // E7
    27938, // F7
    29600, // F#7/Gb7
    31360, // G7
    33224, // G#7/Ab7
    35200, // A7
    37293, // A#7/Bb7
    39511, // B7

    // Octave 8
    41860, // C8
    44349, // C#8/Db8
    46986, // D8
    49780, // D#8/Eb8
    52740, // E8
    55877, // F8
    59199, // F#8/Gb8
    62719, // G8
    /*66449, // G#8/Ab8
    70400, // A8
    74586, // A#8/Bb8
    79021, // B8

    // Octave 9
    83720, // C9
    88698, // C#9/Db9
    93973, // D9
    99561, // D#9/Eb9
    105481, // E9
    111753, // F9
    118398, // F#9/Gb9
    125439, // G9
    132897, // G#9/Ab9
    140800, // A9
    149172, // A#9/Bb9
    158043, // B9*/
};
int lastPlayedNote = 0; 
int initialFreq = 160;
bool intitialFreqSet = false;
bool calibWaiting = false;
String CV_tableName = ""; 
bool CvSlotSet = false;
bool CvTableNameSet = false;
int CV_slot = 0;
bool tableSelectedButtonReady = false;
/*String tableName1 = "";
String tableName2 = "";*/
bool ffff = true;
int cvTableNum = 0;
bool tableSelectorMode = false;
volatile float prevPhase = 0.0f;


void setup()
{
  ///////// CV inputs calibration, press and hold the second button on the left when powering on the module to launch the calibration process (see setup.ino for the calibration function) //////////
  pinMode(PA15, INPUT_PULLUP);
  pinMode(PC14, INPUT_PULLUP);
  pinMode(PC15, INPUT_PULLUP);
  pinMode(PB4, INPUT_PULLUP);
  delay(10);
  if (digitalRead(PB4) == LOW)
  {
    tunerMode = true;
  }
  if (digitalRead(PC14) == LOW)
  {
    CvOutCalib = true;
  }
  if (digitalRead(PC15) == LOW)
  {
    tableSelectorMode = true;
    tunerMode = true;
  }
  if (tunerMode == false && CvOutCalib == false)
  {
    if (digitalRead(PA15) == LOW)                                                                 
    {
      calibrationMode= true;
    }
    initBuffers();                                                                              
    pinSetting->setup();
    delay(20);
    set_SPI();
    delay(20);
    controlScanner->init();
    delay(20);
    utilities->init(); 
    delay(20);
    cvTableNum = loadCvTableNum();
    cv_table_loading(cvTableNum);     
    //display.dim(0);
    delay(20);
    set_ADC_DMA();
    delay(20);
    delay(20);
    setting->init();
    delay(20);
    set_Timer();
    delay(20);
    //Load_CV_Compensator();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.begin(SH1106_SWITCHCAPVCC);
    display.clearDisplay();
    display.setCursor(32, 32);
    display.print("HORA - TANDEM");
    display.display();
    
  }
  else
  {
    pinSetting->setup();
    set_SPI();
    delay(20);
    set_Timer();
    delay(20);
    display.begin(SH1106_SWITCHCAPVCC);
    delay(20);
    display.setTextSize(1);
    set_ADC_DMA();
    delay(20);
    setting->init();
    delay(20);
    //Load_CV_Compensator();  
    cvTableNum = loadCvTableNum();
    if (CvOutCalib)
    {
      GPIOA->regs->BRR = 0b0000000000001000;
      GPIOA->regs->BRR = 0b0000000001000000;
    }
    else
    {
      GPIOA->regs->BSRR = 0b0000000000001000;
      GPIOA->regs->BSRR = 0b0000000001000000;
    }
  }
}

void loop() 
{
  
  /////// If the input buffer isn't completly read and the output buffer isn't completly written ///////
  if (calibrationMode == true)
  {
    for (int i = 0; i < 6; i ++)
    {
      if (buttonTrigged[i] == true && i != 3)
      {
        calibrationConfirmed = true;
      }
    }
  }
  if (input_buff_completely_read == false && output_buff_completely_written == false && tunerMode == false && CvOutCalib == false)          
  {
    controlScanner->buttonScan();                                                             // Scan the button
    setKnobsState();                                                                          // Set knobValue array
    setting->scanKnobLock(knobValue);                                                         // Determine if knobs has been moved/delock since the last menu changing
    scanButtonPressing();                                                                     // Filtering Locked buttons 
    selectMenu();                                                                             // Select the current menu (main, save, routing, edit channel 1, edit channl 2) and his setting method (in setting.cpp)  
    if(setting->getKeyBoardMode(setting->getEditChannel()) == true)
    {
      int paramOffset = 8;
      int edge = false;
      if (gate_input[setting->getEditChannel()] > 0)
      {
          if (seqKeyModeTrigDetect == false)
          {
            seqKeyModeTrigDetect = true;
            edge = true;
            
          }
          noteOnMessage = setting->getEditChannel() == 0 ? getNote(analog_in_buffers[input_buff_tail][5]) : getNote(analog_in_buffers[input_buff_tail][4]);
          setting->setNoteNum(noteOnMessage);
          lastPlayedNote = noteOnMessage;
          isKeyPressed = true;
      }
      else if (gate_input[setting->getEditChannel()] == 0)
      {
         seqKeyModeTrigDetect = false;
         isKeyPressed = false;
      }
      
      if (edge)
      {
         setting->setNoteNum(noteOnMessage);
       }
    }
    if (setting->isLoading() == false && setting->firstPresetLoaded() == true)                // If the first preset is loaded and the unit isn't currently loading a preset
    {
      mapRouting();                                                                           // Routing for the internal CV patch
      controlRouting();                                                                       // Routing of the CV inputs and attenutation 
      output_buffer_A[output_buff_head] = output_buffer_A_sample = processorCycle1();         // Fill the output buffer, processCycle process the next step/frame for the current model of the 1st channel
      output_buffer_B[output_buff_head] = output_buffer_B_sample = processorCycle2();         // Fill the output buffer, processCycle process the next step/frame for the current model of the 2nd channel
      //}
      trig_output_buffer_A[output_buff_head] = utilities->triggCalibrer(trigInit_1, 7, 0);    // Fill the trigger output buffer (trig caliber -> 7ms trig length)
      trig_output_buffer_B[output_buff_head] = utilities->triggCalibrer(trigInit_2, 7, 1);    // Fill the trigger output buffer (trig caliber -> 7ms trig length)
      //if (frameCount % 2 == 0)
      //{
          fillScopeBuffer();                                                                  // Fill the LFO scope buffer each two frames to save some CPU load
      //} 
    }
    bufferInputUpdate();                                                                      // Update index, tail and head of the input buffer
    bufferOutputUpdate();                                                                     // Update index, tail and head of the output buffer
    firstFrame = false;
    if (BUFF_OVERLOAD_DISPLAY)
    {
      drawBufferWarning();                                                                    // Display warning if the buffer is overloaded
    }
  }
  
  //////// if the buffer is completly read or the output buffer is compleley written ///////
  
  else if (tunerMode == false && CvOutCalib == false)                                                                                        
  {
    if (digitalRead(PB4) == LOW)
    {
      restartButtonCounter++;
      if (restartButtonCounter > 200)
      {
        nvic_sys_reset();
      }
    }
    else
    {
      restartButtonCounter = 0;                                                                   // MAIN released: only a continuous hold restarts the module
    }
    if (setting->isLoading() == true)
    {
       Timer2.pause();
       setting->load();                                                                        // If loading state is high (see setting.cpp), use load to get the provisionnal preset name or load the preste if button 1 has been trigged
       setting->transfertParams();       
       if (setting->getModel_1() == 0)
       {
        GPIOA->regs->BSRR = 0b0000000000001000;
       }
       else
       {
        GPIOA->regs->BRR = 0b0000000000001000;
       }
       if (setting->getModel_2() == 0)
       {
        GPIOA->regs->BSRR = 0b0000000001000000;
       }
       else
       {
        GPIOA->regs->BRR = 0b0000000001000000;
       }                                                                                                                                                                 
    }   
    channelLedLightning();
    param_t_pos1 = setting->getParamArray(0, LFO_TRIG_POS) * 0.008;                            // Get some values we need even if the buffer isn't filling/reading
    param_t_pos2 = setting->getParamArray(1, LFO_TRIG_POS) * 0.008;
    bankNum = setting->getBankNum();                                                            
    presetNum = setting->getPresetNum();
    buttonValue[0] = controlScanner->getButtonValue(0);
    buttonValue[4] = controlScanner->getButtonValue(4);
    if (millis() > logoDuration)
    {
      draw();                                                                                // Refresh the display
    } 
    else
    {
      display.clearDisplay();
      display.setCursor(32, 32);
      display.print("HORA - TANDEM");
      display.display();
    }                                                                               
  }
  else // tuner mode
  {
    extraModes();
  }
}
