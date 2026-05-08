
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
// -----------------------------------------------------------------------------
//
// Tandem, multimode CV generator.

#ifndef util_h
#define util_h
#include "Arduino.h"

class util {
private:
        uint16_t lastAnalogValue[6];
        uint16_t fluct[6];
        uint16_t incCount[6];
        uint16_t decCount[6];
        uint16_t lastIncValue[6];
        uint16_t lastDecValue[6];
        int trigFrame[2];
        bool trigDetected[2];
        bool previousGateIn[2];
     
public:
    util() :
                lastAnalogValue(),
                fluct(),
                incCount(),
                decCount(),
                lastIncValue(),
                lastDecValue(),
                trigFrame(),
                trigDetected(),
                previousGateIn()
                
		{

		};
        uint16_t antiFluct(uint16_t analogValue, int potNum);
        uint16_t triggCalibrer(int trigInit_1, int durationMillis, int channel);
        bool triggerActive(int gateIn, int channel);
        void init();
};
#endif
