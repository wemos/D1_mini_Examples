#include <TFT_eSPI.h>  // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include "WiFi.h"

#include "button.h"

#include "FastIMU.h"
#include "Wire.h"
#include "ir.h"


#define IR 9


#define IMU_ADDRESS 0x6B     //Change to the address of the IMU
#define PERFORM_CALIBRATION  //Comment to disable startup calibration
QMI8658 IMU;                 //Change to the name of any supported IMU!

calData calib = { 0 };  //Calibration data
AccelData accelData;    //Sensor data
GyroData gyroData;


TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define BTN0 0
#define BTN47 47
#define BTN48 48

Button btn_left(BTN0);
Button btn_ok(BTN47);
Button btn_right(BTN48);


#define RGB_LED 8

int page_state = 0;
const int MAX_PAGE_NUM = 3;


int rgb_state = 0;

void clean_tft() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(0, 0, 2);
  tft.setTextSize(1);
}

void printwifi(int n) {
  clean_tft();
  if (n == 0) {
    tft.setTextColor(TFT_RED);
    tft.println("no networks");
  } else if (n > 0) {
    tft.setTextColor(TFT_GREEN);
    tft.print(n);
    tft.println(" networks");

    tft.setTextColor(TFT_WHITE);

    for (int i = 0; i < 5; ++i) {
      // Print SSID and RSSI for each network found
      tft.printf("%d", i + 1);
      tft.print(" ");
      tft.printf("%-8.8s", WiFi.SSID(i).c_str());
      tft.print(" ");
      tft.printf("%4ld\n", WiFi.RSSI(i));
    }

    WiFi.scanDelete();
  }
}

void scanwifi() {

  neopixelWrite(RGB_LED, 0, 0, 0);  // turn off rgb_led

  clean_tft();

  while (1) {

    int n = WiFi.scanComplete();

    if (n >= 0) {
      printwifi(n);
    } else {
      if (n == WIFI_SCAN_FAILED) {
        WiFi.scanNetworks(true);
        tft.print("SCAN WIFI...");
      } else if (n = WIFI_SCAN_RUNNING) {
        tft.print(".");
      }
    }
    delay(500);
    if (n >= 0) break;
    if (btn_left.checkPressed()) {
      page_state--;
      break;
    }
  }
  if (page_state == 1) test();
}



void imu_test() {
  digitalWrite(RGB_POWER, 1);
  neopixelWrite(RGB_LED, 0, 0, 0);  // turn off rgb_led
  
  clean_tft();

  tft.setTextColor(TFT_GREEN);

  tft.println("IMU & RGB");

  int err = IMU.init(calib, IMU_ADDRESS);

  while (1) {
    IMU.update();
    tft.setCursor(0, 16, 2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK,true);
    IMU.getAccel(&accelData);
    tft.printf("a_X=%12lf\r\na_Y=%12lf\r\na_Z=%12lf\r\n", accelData.accelX, accelData.accelY, accelData.accelZ);
    IMU.getGyro(&gyroData);
    tft.printf("g_X=%12lf\r\ng_Y=%12lf\r\ng_Z=%12lf\r\n", gyroData.gyroX, gyroData.gyroY, gyroData.gyroZ);

    rgb_test();

    delay(500);
    if (btn_ok.checkPressed() || btn_right.checkPressed()) {
      page_state++;
      break;
    }
  }
  test();
}

void rgb_test() {
  switch (rgb_state) {
    case 0:
      neopixelWrite(RGB_LED, 3, 0, 0);
      break;
    case 1:
      neopixelWrite(RGB_LED, 0, 3, 0);
      break;
    case 2:
      neopixelWrite(RGB_LED, 0, 0, 3);
      break;
  }

  rgb_state++;
  if (rgb_state > 2)
    rgb_state = 0;
}

void ir_test() {

  neopixelWrite(RGB_LED, 0, 0, 0);  // turn off rgb_led
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(0, 0, 2);
  tft.setTextSize(1);
  tft.println("IR Test");
  tft.setTextColor(TFT_WHITE);
  tft.println("OK - SEND");

  send_NEC(0x5F,0x41);
  rmtWrite(IR, send_data, RMT_SYMBOLS_OF(send_data), RMT_WAIT_FOR_EVER);
  

}


void disp_bottom() {
  tft.setCursor(0, 112);
  tft.setTextColor(TFT_WHITE);
  tft.print("<");
  tft.setCursor(56, 112);
  tft.setTextColor(TFT_BLUE);
  tft.print("OK");
  tft.setCursor(119, 112);
  tft.setTextColor(TFT_WHITE);
  tft.print(">");
}

void test() {
  switch (page_state) {

    case 0:
      imu_test();
      break;
    case 1:
      ir_test();
      Serial.println("SEND IR");
      break;
    case 2:
      scanwifi();
      break;
  }
}

void setup(void) {


  Wire.setPins(12, 11);
  Wire.begin();
  Wire.setClock(400000);  //400khz clock


  btn_left.begin();
  btn_ok.begin();
  btn_right.begin();

  pinMode(IR, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.scanNetworks(true);


  tft.init();

  Serial.begin(115200);

  rmtInit(IR, RMT_TX_MODE, RMT_MEM_NUM_BLOCKS_1, 1000000);  //1us
  rmtSetCarrier(IR, true, false, 38000, 0.33);

  test();

}

void loop() {

  if (btn_left.checkPressed()) {
    if (page_state > 0) {
      page_state--;
      test();
    }
  }

  if (btn_right.checkPressed()) {

    if (page_state < MAX_PAGE_NUM - 1) {
      page_state++;
      test();
    }
  }

  if (btn_ok.checkPressed()) {
    delay(20);
    test();
  }
}
