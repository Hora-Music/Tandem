
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


