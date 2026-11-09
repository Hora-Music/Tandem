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

////////////////////////////////////////////////// Update index, tail and head of the input and output buffers ///////////////////////////////////////////////

void bufferInputUpdate()
{
    input_buff_tail ++;
    if (input_buff_tail >= BUFFER_SIZE)
    {
      input_buff_tail = 0;
    }
    if (input_buff_head == input_buff_tail)
    {
      input_buff_completely_read = true;
    }
    input_buff_overload = false;
}

void bufferOutputUpdate()
{
    output_buff_head ++;
    if (output_buff_head >= BUFFER_SIZE)
    {
      output_buff_head = 0;
    }
    if (output_buff_head == output_buff_tail - 1) // -1 because we use previous output for the internal cv/gate routing
    {
      output_buff_completely_written = true;
    }
    output_buff_overload = false;
}


