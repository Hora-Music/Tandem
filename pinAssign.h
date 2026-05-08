
#ifndef pinAssign_h
#define pinAssign_h
#include "Arduino.h"
#define DAC_CS    PB9
#define pot1 PA2
#define pot2 PA0
#define pot3 PA1
#define pot4 PA4
#define button1 PA8
#define button2 PB8
#define button3 PC14
#define button4 PC13
#define button5 PC15
#define button6 PA15
#define mainButton PB4
#define trigIn1 PB12
#define trigIn2 PB7
#define trigOut1 PB6
#define trigOut2 PA12
#define CVIn1 PB1
#define CVIn2 PB0
#define DAC_FLAGS_A 0b00110000
#define DAC_FLAGS_B 0b10110000
#define SPI2_NSS_PIN PB9  


#define OLED_MOSI  PA10
#define OLED_CLK   PA9
#define OLED_DC    PB10
#define OLED_CS    PB5
#define OLED_RESET  PB11
#define OFFSET_SWITCH_A PA6
#define OFFSET_SWITCH_B PA3
#define LFO 0
#define ENVELOPE 1
#define SEQUENCER 2
#define BASSLINE_ENVELOPE 4
#define CLASSIC_SEQUENCER 3
#define LFO_RATE 0
#define LFO_WAVE 1
#define LFO_PHASE 2
#define LFO_TRIG_POS 3
#define ATTACK 0
#define DECAY 1
#define SUSTAIN 2
#define RELEASE 3
#define CHANNEL_A 0
#define CHANNEL_B 1
#define INT_CV_PARAM1 6
#define INT_CV_PARAM2 7

class pinAssign {
private:

public:
    pinAssign()
		{

		};
    void setup();
};
#endif
