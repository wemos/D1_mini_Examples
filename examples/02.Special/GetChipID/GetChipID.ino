/*  Get Chip ID
 *  wemos.cc
 *  
 *  
 */

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("");
  Serial.println("");
  Serial.println("Check ID in:");
  Serial.println("https://www.wemos.cc/verify_products");
  Serial.printf("Chip ID = %08X\n", ESP.getChipId());
  Serial.println("");
  Serial.println("");
  delay(5000);
}
