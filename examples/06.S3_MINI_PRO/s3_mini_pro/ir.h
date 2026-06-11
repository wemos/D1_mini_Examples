rmt_data_t data_START = { 9000, 1, 4500, 0 };  //9ms 1, 4.5ms 0
rmt_data_t data_HIGH = { 560, 1, 1690, 0 };
rmt_data_t data_LOW = { 560, 1, 560, 0 };
rmt_data_t data_END = { 280, 1, 280, 1 };  //562.5us

rmt_data_t send_data[34]={0};

void rmt_build_item(rmt_data_t* item, uint32_t cmd_data) {
  
  int n=0;
  item[n]=data_START;
  n++;
  

  // parse from left to right up to 32 bits (0x80000000)
  for (unsigned long mask = 1UL << (32 - 1); mask; mask >>= 1) {
    if (cmd_data & mask) {
      item[n]=data_HIGH;
    }

    else {
      item[n]=data_LOW;
    }
    n++;
  }
  item[n]=data_END;
  
}

void send_NEC(uint8_t address, uint8_t cmd)
{
  uint32_t data=0;
  data=(address<<24)|(uint8_t(~address)<<16)|(cmd<<8)|uint8_t(~cmd);
  Serial.println(data,HEX);
  rmt_build_item(send_data,data);
}
