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

////////////////////////////////////////////////////// Selection of the main or saving menu and calling of the good setting function (in setting.cpp) //////////////////////////////////////

void mainMenuSelect()
{
  if (buttonTrigged[6])
  {
      if (setting->getMainMenuOpened() == false)
      {
        setting->knobLock(knobValue);
        setting->setMainMenuOpened(true);
      }
      else if ( mainButtonTrigCount > 0 && setting->getRoutingMenuOpened() == false)
      {
        setting->setSavingState(true);
        firstSaveMenuFrame = true;
      }
      mainButtonTrigCount++;
  }
}

////// Using of the currentMenu (from getCurretnMenu in setting.cpp) to selct the good setting function (the drum sequencer case is a vestige from an experimentation druing the dev process) //////

void selectMenu()
{
  mainMenuSelect();
  if (setting->getRoutingMenuOpened() == true)
  {
     setting->routingSetting(knobMoved, knobValue, effectiveTrigged);
     button_4_hold = false;
  }
  else if (setting->getMainMenuOpened() == true)
  {
     setting->mainSetting(knobMoved, knobValue, effectiveTrigged);
     scope_mode = false;
  }
  else
  {
        mainButtonTrigCount = 0;
        onSet = true;
        switch (setting->getCurrentMenu())
        {
          case LFO :
             setting->LFOSetting(knobMoved, knobValue, effectiveTrigged);
             if (effectiveTrigged[0] == true)
             {
                scope_mode = !scope_mode;
             }
          break;
          case ENVELOPE :
              setting->envelopeSetting(knobMoved, knobValue, effectiveTrigged);
          break;
          case SEQUENCER :
              setting->SequencerSetting(knobMoved, knobValue, effectiveTrigged);
          break;
          case CLASSIC_SEQUENCER :
              setting->classicSequencerSetting(knobMoved, knobValue, effectiveTrigged, stepSequencer[0]->getSeqPos(), stepSequencer[1]->getSeqPos());
          break;
          case BASSLINE_ENVELOPE :
              setting->bassLineEnvSetting(knobMoved, knobValue, effectiveTrigged);
          break;
        }
  }
}
