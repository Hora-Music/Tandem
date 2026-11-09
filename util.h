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
