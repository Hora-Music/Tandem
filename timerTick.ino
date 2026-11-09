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

void timerTick(void) {

  //////////////////////////////////////////// Filling of the inputs buffers ///////////////////////////////////////////////////
  if (tunerMode == false && CvOutCalib == false )
  {
  if (input_buff_overload == false)
  {
    int knobValueT[6];
    uint16_t RawValue1 = dataPoints[0] >> 5;
    ADCFilterCV1.Filter(RawValue1);
    knobValueT[0] = ADCFilterCV1.Current(); 
    
    uint16_t RawValue2 = dataPoints[1] >> 5;
    ADCFilterCV2.Filter(RawValue2);
    knobValueT[1] = ADCFilterCV2.Current(); 
    
    uint16_t RawValue3 = dataPoints[2] >> 5;
    ADCFilterCV3.Filter(RawValue3);
    knobValueT[2] = ADCFilterCV3.Current(); 
    
    uint16_t RawValue4 = dataPoints[3] >> 5;
    ADCFilterCV4.Filter(RawValue4);
    knobValueT[3] = ADCFilterCV4.Current(); 
    
    if (((setting->getModel_2() == CLASSIC_SEQUENCER) || seqCvCalibration) && calibrationMode == false)
    {
      ADCFilterCV5.SetWeight(32);
      uint16_t RawValue5 = dataPoints[4] >> 2;
      ADCFilterCV5.Filter(RawValue5);
      knobValueT[4] = ADCFilterCV5.Current(); 
    }
    else
    {
      ADCFilterCV5.SetWeight(8);
      uint16_t RawValue5 = dataPoints[4] >> 5;
      ADCFilterCV5.Filter(RawValue5);
      knobValueT[4] = ADCFilterCV5.Current(); 
    }

    if (((setting->getModel_1() == CLASSIC_SEQUENCER) || seqCvCalibration) && calibrationMode == false)
    {
      ADCFilterCV6.SetWeight(32);
      uint16_t RawValue6 = dataPoints[5] >> 2;
      ADCFilterCV6.Filter(RawValue6);
      knobValueT[5] = ADCFilterCV6.Current(); 
    }
    else
    {
      ADCFilterCV6.SetWeight(8);
      uint16_t RawValue6 = dataPoints[5] >> 5;
      ADCFilterCV6.Filter(RawValue6);
      knobValueT[5] = ADCFilterCV6.Current(); 
    }
   
    for (int i = 0 ; i < 6; i++)
    {
      analog_in_buffers[input_buff_head][i] = utilities->antiFluct(knobValueT[i], i);
    }
    trig_in_buffers[input_buff_head][0] = !(GPIOB->regs->IDR & 0b0001000000000000);
    trig_in_buffers[input_buff_head][1] = !(GPIOB->regs->IDR & 0b0000000010000000);
    input_buff_head ++;
    if (input_buff_head >= BUFFER_SIZE)
    {
      input_buff_head = 0;
    }
     if (input_buff_head == input_buff_tail)
    {
      input_buff_overload = true;
    }
    input_buff_completely_read = false;
  }

  /////////////////////////////// Using of the outputs buffers and send the values to the dac using the SPI DMA /////////////////
  
  if (output_buff_overload == false)
  {
    // DAC outputs
    int outA = output_buffer_A[output_buff_tail];
    byte lValA = outA;
    byte hValA = outA >> 8;
    hValA = hValA | DAC_FLAGS_A;
    int outB = output_buffer_B[output_buff_tail];
    byte lValB = outB;
    byte hValB = outB >> 8;
    hValB = hValB | DAC_FLAGS_B;
    GPIOB->regs->BRR = 0b0000001000000000;
    SPI_2.dmaSend(&hValA, 1, 1);
    SPI_2.dmaSend(&lValA, 1, 1);
    GPIOB->regs->BSRR = 0b0000001000000000;
    GPIOB->regs->BRR = 0b0000001000000000;
    SPI_2.dmaSend(&hValB, 1, 1);
    SPI_2.dmaSend(&lValB, 1, 1);
    GPIOB->regs->BSRR = 0b0000001000000000;
    
    //////////////////////////// Using of the trigger outputs buffers and set the pins by using GPIO registers /////////////////
    
    if (trig_output_buffer_A[output_buff_tail])
    {
      GPIOB->regs->BSRR = 0b0000000001000000;
    }
    else
    {
      GPIOB->regs->BRR = 0b0000000001000000;
    }
     if (trig_output_buffer_B[output_buff_tail])
    {
        GPIOA->regs->BSRR = 0b0001000000000000;
    }
    else
    {
        GPIOA->regs->BRR = 0b0001000000000000;
    }
 
    ///////////////////////////////////////////////////////// output buffer update //////////////////////////////////////////////
    
    output_buff_tail ++;
    if (output_buff_tail >= BUFFER_SIZE)
    {
      output_buff_tail = 0;
    }
    if( output_buff_tail == output_buff_head)
    {
      output_buff_overload = true;
    }
    output_buff_completely_written = false;
  }

  /////////////////////////////////////////// Set the blinkState used for blinking element on the display ////////////////////////
  
  int  period = 100;
  if (frameCount > period)
  {
    blinkState = !blinkState;
    frameCount = 0;
  }

  //////// Count the frames because a fex cycle has to pass before the buffer values can be used by the calibration process ///////
  
  //if (seqCvCalibration == true)
  //{
    /*if (measureCalibCount[0] < 1)
    {
      secondSeqCalibCandidate[0] = bestSeqCalibCandidate[0];
    }
    if (measureCalibCount[1] < 1)
    {
      secondSeqCalibCandidate[1] = bestSeqCalibCandidate[1];
    }*/
    /*
    if (seqCvCalibrationTimer >= 5000)
    {
      seq_CV_in_calibration();
      seqCvCalibrationTimer = 0;
      seqCvCalibrationIndex++;
      
      biggestMeasureStabity[0] = 0;
      biggestMeasureStabity[1] = 0;
      secondChoiceMeasureStabity[0] = 0; 
      secondChoiceMeasureStabity[1] = 0; 
      measureStabity[0] = 0;
      measureStabity[1] = 0;
      measureCalibCount[0] = 0;
      measureCalibCount[1] = 0;
      seqCalibValueSet[0][0] = false;
      seqCalibValueSet[1][0] = false;
      seqCalibValueSet[0][1] = false;
      seqCalibValueSet[1][1] = false;
    }
    else if (seqCvCalibrationTimer >= 2000)
    {
      seq_CV_in_calibration_collector();
    }
    seqCvCalibrationTimer++;
  }*/
  
  if (calibrationMode == true && calibrationConfirmed == true)
  {
    calibFrameCount ++;
    CV_in_calibration();
  }
  
  //////// icrement the frame count ///////////
  frameCount++;
  }
  else
  {
    if (extraMode == TUNER || CvOutCalib == true)
    {
      prevData = newData;//store previous value
      newData = dataPoints[5] >> 2;
      /*ADCFilterCV1.Filter(RawValue6);
      newData = ADCFilterCV1.Current(); */
      prevGateIn_ = gateIn_;
      gateIn_ = !(GPIOB->regs->IDR & 0b0001000000000000);
      if (gateIn_ != 0 && prevGateIn_ == 0)
      {
        period = timer + 1;//get period
        timer = 0;//reset timer
        if (flipCount1 > 0 && CvOutCalib == false)
        {
         flipCount1 = 0;
         flipFlop1 =!flipFlop1;
          int outA = subState1;
          byte lValA = outA;
          byte hValA = outA >> 8;
          hValA = hValA | DAC_FLAGS_A;
          GPIOB->regs->BRR = 0b0000001000000000;
          SPI_2.dmaSend(&hValA, 1, 1);
          SPI_2.dmaSend(&lValA, 1, 1);
          GPIOB->regs->BSRR = 0b0000001000000000;
          valueHasChanged = false;
        }
        //else
        //{
          flipCount1++;
        //}
        if (flipFlop1 == true)
        {
          subState1 = 0;
        }
        else
        {
          subState1 = 4095;
        }
      }
      /*else if (prevData < 512 && newData >= 512)
      {
        period = timer;//get period
        timer = 0;//reset timer
      }*/
      else
      {
        timer++;//increment timer at rate of 40kHz
        if (timer > 65000)
        {
          timer = 0;
        }
      }
      
      prevData2 = newData2;//store previous value
      newData2 = dataPoints[4];

      prevGateIn_2 = gateIn_2;
      gateIn_2 = !(GPIOB->regs->IDR & 0b0000000010000000);
      /*ADCFilterCV2.Filter(RawValue5);
      newData2 = ADCFilterCV2.Current(); */
      if (gateIn_2 != 0 && prevGateIn_2 == 0)
      {//if increasing and crossing midpoint
        period2 = timer_2 + 1;//get period
        timer_2 = 0;//reset timer
        if (flipCount2 > 0 && CvOutCalib == false)
        {
         flipCount2 =  0;
         flipFlop2 =!flipFlop2;
          int outB = subState2;
          byte lValB = outB;
          byte hValB = outB >> 8;
          hValB = hValB | DAC_FLAGS_B;
          GPIOB->regs->BRR = 0b0000001000000000;
          SPI_2.dmaSend(&hValB, 1, 1);
          SPI_2.dmaSend(&lValB, 1, 1);
          GPIOB->regs->BSRR = 0b0000001000000000;
          valueHasChanged = false;
        }
        //else
        //{
         // flipCount2++;
        //}
        if (flipFlop2 == true)
        {
          subState2 = 0;
        }
        else
        {
          subState2 = 4095;
        }
      }
      else
      {
         timer_2++;//increment timer at rate of 40kHz*/
         if (timer_2 > 65000)
        {
          timer_2 = 0;
        }
      }
      inc++;
      if (CvOutCalib && valueHasChanged)
      {
        if (fff == true)
        {
          int outB = 4095;
          byte lValB = outB;
          byte hValB = outB >> 8;
          hValB = hValB | DAC_FLAGS_B;
          GPIOB->regs->BRR = 0b0000001000000000;
          SPI_2.dmaSend(&hValB, 1, 1);
          SPI_2.dmaSend(&lValB, 1, 1);
          GPIOB->regs->BSRR = 0b0000001000000000;
          valueHasChanged = false;
          fff = false;
        }
        if(chan == 0)
        {
          int outA = cvValueForCalib;
          byte lValA = outA;
          byte hValA = outA >> 8;
          hValA = hValA | DAC_FLAGS_A;
          GPIOB->regs->BRR = 0b0000001000000000;
          SPI_2.dmaSend(&hValA, 1, 1);
          SPI_2.dmaSend(&lValA, 1, 1);
          GPIOB->regs->BSRR = 0b0000001000000000;
          valueHasChanged = false;
        }
        else
        {
          int outB = cvValueForCalib;
          byte lValB = outB;
          byte hValB = outB >> 8;
          hValB = hValB | DAC_FLAGS_B;
          GPIOB->regs->BRR = 0b0000001000000000;
          SPI_2.dmaSend(&hValB, 1, 1);
          SPI_2.dmaSend(&lValB, 1, 1);
          GPIOB->regs->BSRR = 0b0000001000000000;
          valueHasChanged = false;
        }
      }
      /*
      else if (CvOutCalib == false) 
      {
        int outA = subState1;
        byte lValA = outA;
        byte hValA = outA >> 8;
        hValA = hValA | DAC_FLAGS_A;
        GPIOB->regs->BRR = 0b0000001000000000;
        SPI_2.dmaSend(&hValA, 1, 1);
        SPI_2.dmaSend(&lValA, 1, 1);
        GPIOB->regs->BSRR = 0b0000001000000000;
        valueHasChanged = false;

        int outB = subState2;
        byte lValB = outB;
        byte hValB = outB >> 8;
        hValB = hValB | DAC_FLAGS_B;
        GPIOB->regs->BRR = 0b0000001000000000;
        SPI_2.dmaSend(&hValB, 1, 1);
        SPI_2.dmaSend(&lValB, 1, 1);
        GPIOB->regs->BSRR = 0b0000001000000000;
        valueHasChanged = false;
      }*/
    }
    else if (extraMode == SCOPE)
    {
        inc++;
        if (inc > 0)
        {
          prevData = newData;//store previous value
          //newData = (dataPoints[5] >> 4;
          uint16_t RawValue6 = dataPoints[5] >> 4;
          ADCFilterCV5.Filter(RawValue6);
          uint16_t f_pole = ADCFilterCV5.Current();
          uint16_t RawValue7 = f_pole;
          ADCFilterCV6.Filter(RawValue7);
          newData = ADCFilterCV6.Current();
          
          
          scopeRate = (dataPoints[3] >> 4);
          uint8_t weight = 54;
          ADCFilterCV5.SetWeight(weight);
          ADCFilterCV6.SetWeight(weight);
          ADCFilterCV1.SetWeight(weight);
          ADCFilterCV2.SetWeight(weight);

          uint16_t RawValue = dataPoints[4] >> 4;
          ADCFilterCV1.Filter(RawValue);
          uint16_t f_pole_ = ADCFilterCV1.Current();
          uint16_t RawValue_ = f_pole_;
          ADCFilterCV2.Filter(RawValue_);
          newData2 = ADCFilterCV2.Current();
          
          prevData2 = newData2;//store previous value
          //newData2 = dataPoints[4] >> 4;
           /*if (prevData < 127 && newData >= 127)
           {//if increasing and crossing midpoint
              forceDisplay = true;
           }*/
        }
    }
    else if (extraMode == VOLTMETER)
    {
          prevData = newData;//store previous value
          //newData = (dataPoints[5] >> 2;
          uint16_t RawValue6 = dataPoints[5] >> 2;
          ADCFilterCV5.Filter(RawValue6);
          uint16_t f_pole = ADCFilterCV5.Current();
          uint16_t RawValue7 = f_pole;
          ADCFilterCV6.Filter(RawValue7);
          newData = ADCFilterCV6.Current();
          
          scopeRate = (dataPoints[3] >> 2);
          uint8_t weight = 2;
          ADCFilterCV5.SetWeight(weight);
          ADCFilterCV6.SetWeight(weight);
          ADCFilterCV1.SetWeight(weight);
          ADCFilterCV2.SetWeight(weight);

          uint16_t RawValue = dataPoints[4] >> 2;
          ADCFilterCV1.Filter(RawValue);
          uint16_t f_pole_ = ADCFilterCV1.Current();
          uint16_t RawValue_ = f_pole_;
          ADCFilterCV2.Filter(RawValue_);
          newData2 = ADCFilterCV2.Current();
          prevData2 = newData2;//store previous value
    }
    else if (extraMode == VCO)
    {
      uint16_t RawValue5 = dataPoints[5] >> 2;
      ADCFilterCV5.Filter(RawValue5);
      uint16_t cv1 = ADCFilterCV5.Current();
      uint16_t cv2 = dataPoints[4] >> 5;
      for (int i = 0; i < 60; i++)
      {
        bool between = false;
        if (cv1 > (cvNotesFromKb[i] - 4) && cv1 < (cvNotesFromKb[i] + 4))
        {
          between = true;
        }
        if (between == true)
        {
          index1 = i;
        }
      }
      int mode = dataPoints[3] >> 11;
      int freq1 = index1 > 60 ? noteFrequencies[60] : noteFrequencies[index1 + 24 + (dataPoints[0] >> 10) * 12];
      float f = float(freq1);
      if (cv2 > 63)
      {
       if (mode == 0)
        {
          float mult = (cv2 - 63.5f) / 63.5f;
           mult = mult > 1.0f ? 1.0f : mult;
           mult = mult < 0.0f ? 0.0f : mult;
           float finalMult = 1.0f + mult;
           freq1 *= finalMult;
        }
        f = float(freq1);
      }
      else
      {
        float mult = (63.5f - cv2) / 63.5;
        mult = mult > 1.0f ? 1.0f : mult;
        mult = mult < 0.0f ? 0.0f : mult;
        float finalDiv = 1.0f / (1.0f + mult);
        f = float(freq1);
        if (mode == 0)
       {
          f *= finalDiv;
        }
      }
      float rate1 = f / 10000.0f;
      VCO_phase += rate1;
      float maxRate = 20;
      if (controlFrame)
      {
        controlFrame = false;
        d1 = 0.01f + (float((dataPoints[1] >> 7))/ 65.0f);
        d2 = 0.01f + (float((dataPoints[2] >> 7)) / 65.0f);
        if (mode == 1)
        {
          int d2_ = d2 + ((cv2 - 63.5f) / 63.5f);
          int d2__ = d2_ > 0.5 ? 0.5 : d2_; 
          d2 = d2__ < 0.0 ? 0.0 : d2__; 
        }
        /*float R1 = rate1 /d1; 
        float R2 = rate1 /d2; 
        float ratio1 = maxRate / R1;
        float ratio2 = maxRate / R2;
        if (ratio1 < 1)
        {
          d1 = d1 / ratio1;
        }
        if (ratio2 < 1)
        {
          d2 = d2 / ratio2;
        }*/
        M1 = 1.0 / d1;
        M2 = 1.0 / d2;
        M1_ = 1.0 / (1.0 - d1);
        M2_ = 1.0 / (1.0 - d2);
      }
      float M = 1.0f;
      float M_ = 1.0f;
      float d = 0.5f;
      float v = 0.5f;
      float phaseV1;
      float phaseV2;
      
      if (VCO_phase >= 100.0f)
      {
       fff =!fff;
       if (fff)
       {
           controlFrame = true; 
       }
        VCO_phase -= 100.0f;
      }
      if(fff == true)
      {
        M = M1;
        M_ = M1_;
        d = d1;
      }
      else
      {
        M = M2;
        M_ = M2_;
        d = d2;
      }
      if (VCO_phase <= (d * 100.0f))
      {
        phaseV1 = 0.5 * (VCO_phase * M);
      }
      else if(VCO_phase > (d * 100.0f))
      {
        phaseV1 = 0.5f * ((VCO_phase - (d * 100)) * M_) + 50;
      }
      while (phaseV1 >= 100.0f)
      {
        phaseV1 -= 100.0f;
      }
      float TP = phaseV1 / 25.0f;
      float sine = 0.0f;
      //sine = ((1.0f - TP) * (1.0f - TP)) - 1.0f;
      if (TP < 1.0f)
      {
         sine = ((TP) * (TP)) - 1.0f;
      }
      else if (TP < 2.0f)
      {
        sine = 0.0f - (((1.0f - (TP - 1.0f)) * (1.0f - (TP - 1.0f))) - 1.0f);
      }
      else if (TP < 3.0f)
      {
        sine = 0.0f - (((TP - 2.0f) * (TP - 2.0f)) - 1.0f);
      }
      else if (TP < 4.0f)
      {
        sine = ((1.0f - (TP - 3.0f)) * (1.0f - (TP - 3.0f))) - 1.0f;
      }
      int outA = 4095 - int(((sine + 1.0f) / 2.0f) * 4095.0f);
      //int outA = 4095 - int((TP / 100.0f) * 4095.0f);
      byte lValA = outA;
      byte hValA = outA >> 8;
      hValA = hValA | DAC_FLAGS_A;
      GPIOB->regs->BRR = 0b0000001000000000;
      SPI_2.dmaSend(&hValA, 1, 1);
      SPI_2.dmaSend(&lValA, 1, 1);
      GPIOB->regs->BSRR = 0b0000001000000000;
      /*if (VCO_phase > 50.0f && prevPhase <= 50.0f)
      {
          int outA = 4095 - int(float((rate1 * 4095.0f)) / 50.0f);
          byte lValA = outA;
          byte hValA = outA >> 8;
          hValA = hValA | DAC_FLAGS_A;
          GPIOB->regs->BRR = 0b0000001000000000;
          SPI_2.dmaSend(&hValA, 1, 1);
          SPI_2.dmaSend(&lValA, 1, 1);
          GPIOB->regs->BSRR = 0b0000001000000000;
          GPIOB->regs->BSRR = 0b0000000001000000;
      }
      else if (VCO_phase < 50.0f && prevPhase > 50.0f)
      {
          GPIOB->regs->BRR = 0b0000000001000000;
      }*/
      prevPhase = VCO_phase;
      

          
      /*int outB = (VCO_phase[1] - 0.5f) * 4095;;
          byte lValB = outB;
          byte hValB = outB >> 8;
          hValB = hValB | DAC_FLAGS_B;
          GPIOB->regs->BRR = 0b0000001000000000;
          SPI_2.dmaSend(&hValB, 1, 1);
          SPI_2.dmaSend(&lValB, 1, 1);
          GPIOB->regs->BSRR = 0b0000001000000000;
          valueHasChanged = false;*/
    }
   }
} 
