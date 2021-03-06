#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <stdarg.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>
#include <stdio.h>
File writeFile;

/* Assign a unique ID to the sensors */
Adafruit_10DOF                dof   = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);

/* Update this with the correct SLP for accurate altitude measurements */
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;

/**************************************************************************/
/*!
    @brief  Initialises all the sensors used by this example
*/
/**************************************************************************/
void initSensors()
{
  if(!accel.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP180 ... check your connections */
    Serial.println("Ooops, no BMP180 detected ... Check your wiring!");
    while(1);
  }
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(115200);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  writeFile = SD.open("altitude.csv", FILE_WRITE);
  writeFile.println("altitude, pitch, orientation, heading, temperature");
  Serial.print("altitude, pitch, orientation, heading, temperature");
  /* Initialise the sensors */
  initSensors();
}

/**************************************************************************/
/*!
    @brief  Constantly check the roll/pitch/heading/altitude/temperature
*/
/**************************************************************************/
void loop(void)
{
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  sensors_event_t accel_event;
  sensors_event_t mag_event;
  sensors_event_t bmp_event;
  sensors_vec_t   orientation;

  /* Calculate pitch and roll from the raw accelerometer data */
  accel.getEvent(&accel_event);
  if (dof.accelGetOrientation(&accel_event, &orientation))
  {
    /* 'orientation' should have valid .roll and .pitch fields */
    //Serial.print(F("Roll: "));
    //Serial.print(orientation.roll);
    //Serial.print(F("; "));
    //Serial.print(F("Pitch: "));
    //Serial.print(orientation.pitch);
    //Serial.print(F("; "));
  }
  
  /* Calculate the heading using the magnetometer */
  mag.getEvent(&mag_event);
  if (dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation))
  {
    /* 'orientation' should have valid .heading data now */
    //Serial.print(F("Heading: "));
    //Serial.print(orientation.heading);
    //Serial.print(F("; "));
  }

  /* Calculate the altitude using the barometric pressure sensor */
  bmp.getEvent(&bmp_event);
  if (bmp_event.pressure)
  {
    /* Get ambient temperature in C */
    float temperature;
    bmp.getTemperature(&temperature);
    /* Convert atmospheric pressure, SLP and temp to altitude    */
    //Serial.print(F("Alt: "));
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        bmp_event.pressure,
                                        temperature) +String(", ")+ orientation.pitch +String(", ")+ orientation.roll +String(", ")+ orientation.heading +String(", ")+ temperature); 
    writeFile = SD.open("altitude.csv", FILE_WRITE);
    delay(200);
    writeFile.println(bmp.pressureToAltitude(seaLevelPressure,
                                        bmp_event.pressure,
                                        temperature) +String(", ")+ orientation.pitch +String(", ")+ orientation.roll +String(", ")+ orientation.heading +String(", ")+ temperature); 
    delay(200);
    writeFile.close();
    //Serial.print(F(" m; "));
    /* Display the temperature */
    //Serial.print(F("Temp: "));
    //Serial.print(temperature);
    //Serial.print(F(" C"));
  }
  
  Serial.println(F(""));
  delay(1000);
  
}
