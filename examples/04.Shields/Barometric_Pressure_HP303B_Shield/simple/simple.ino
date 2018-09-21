#include <LOLIN_HP303B.h>

LOLIN_HP303B HP303B;

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    //Address of the HP303B (0x77 or 0x76)
    HP303B.begin(); // I2C address = 0x77

    // HP303B.begin(0x76); //I2C address = 0x76

}

void loop()
{
    int32_t temperature;
    int32_t pressure;
    int16_t oversampling = 7;
    int16_t ret;
    Serial.println();

    //lets the HP303B perform a Single temperature measurement with the last (or standard) configuration
    //The result will be written to the paramerter temperature
    //ret = HP303B.measureTempOnce(temperature);
    //the commented line below does exactly the same as the one above, but you can also config the precision
    //oversampling can be a value from 0 to 7
    //the HP303B will perform 2^oversampling internal temperature measurements and combine them to one result with higher precision
    //measurements with higher precision take more time, consult datasheet for more information
    ret = HP303B.measureTempOnce(temperature, oversampling);

    if (ret != 0)
    {
        //Something went wrong.
        //Look at the library code for more information about return codes
        Serial.print("FAIL! ret = ");
        Serial.println(ret);
    }
    else
    {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" degrees of Celsius");
    }

    //Pressure measurement behaves like temperature measurement
    //ret = HP303B.measurePressureOnce(pressure);
    ret = HP303B.measurePressureOnce(pressure, oversampling);
    if (ret != 0)
    {
        //Something went wrong.
        //Look at the library code for more information about return codes
        Serial.print("FAIL! ret = ");
        Serial.println(ret);
    }
    else
    {
        Serial.print("Pressure: ");
        Serial.print(pressure);
        Serial.println(" Pascal");
    }

    //Wait some time
    delay(500);
}
