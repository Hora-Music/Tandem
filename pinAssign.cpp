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

#include "pinAssign.h"

void pinAssign::setup()
{
  
  ///////////////////////////////////////////////////// Registers setting ///////////////////////////////////////////
   // 3 means out, 8 means input f mean unchange
  
  GPIOA->regs->CRL = (GPIOA->regs->CRL & 0xFFF00000) | 0x00088888;
  GPIOA->regs->CRH = (GPIOA->regs->CRH & 0x0FF00FF0) | 0x80000008 | 0x00033000;
  GPIOB->regs->CRL = (GPIOB->regs->CRL & 0x00F00F00) | 0x80088088 | 0x03000000;
  GPIOB->regs->CRH = (GPIOB->regs->CRH & 0xFFF0FF00) | 0x00080008 | 0x03000030;
  GPIOA->regs->BSRR = 0b1110000100010000;
  GPIOB->regs->BSRR = 0b0001001110010000;

  //////////////////////////// PinModes (to verify : some maybe set yet by the registers setting) ///////////////////
  
  pinMode(PA8, OUTPUT);
  pinMode(PB8, OUTPUT);
  pinMode(PC13, INPUT_PULLUP);
  pinMode(PC14, INPUT_PULLUP);
  pinMode(PC15, INPUT_PULLUP);
  pinMode(PA6, OUTPUT);
  pinMode(PA3, OUTPUT);
  pinMode(PA5, OUTPUT);
  pinMode(PA7, OUTPUT);
  pinMode(SPI2_NSS_PIN, OUTPUT);
  pinMode(PB4, INPUT_PULLUP);
  digitalWrite(PB4, HIGH);
  //pinMode(SPI1_NSS_PIN, OUTPUT);
  digitalWrite(PA6, LOW);
   digitalWrite(PA3, LOW);
  digitalWrite(PA5, LOW);
  digitalWrite(PA7, LOW);
  pinMode(PA13, INPUT);
  pinMode(PA14, OUTPUT);
  //pinMode(PA9,OUTPUT);
  //pinMode(PA10,OUTPUT);
}
