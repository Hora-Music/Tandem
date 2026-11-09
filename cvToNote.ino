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

int getNote(int cvValue)
{
  int playingNote = 0;
  for (int i = 0; i < 60; i++)
  {
    if (isBetween(cvValue, cvNotesFromKb[i] - 4, cvNotesFromKb[i] + 4) == true)
    {
      return i;
    }
  }
  return 0;
}

bool isBetween(int val, int x, int y)
{
  if (val > x && val < y)
  {
    return true;
  }
  else
  {
    return false;
  }
}
