/*
Basic_I2C.ino
Brian R Taylor
brian.taylor@bolderflight.com

Copyright (c) 2017 Bolder Flight Systems

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "MPU9250.h"

double Ym = 0;  // variable to store the y magnetic field value
double Xm = 0;  // variable to store the x magnetic field value
double heading = 0;  // variable to store the heading value
double declination = 0;  // variable to store the declination value
double headingDegrees = 0;  // variable to store the headingDegrees value
double headingFiltered = 0;  // variable to store the headingFiltered value

double myArray[10]={0, 0, 0, 0, 0 ,0, 0, 0, 0, 0};
int c = 0;
double Aheading = 0;


// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;

void setup() {
  // serial to display data
  Serial.begin(9600);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
}

void loop() {
  // read the sensor
  IMU.readSensor();
  // display the data
//  Serial.print("X Accel [m/s^2]: "); 
//  Serial.print(IMU.getAccelX_mss(),6);
//  Serial.print("\t");
//  Serial.print("Y Accel [m/s^2]: ");
//  Serial.print(IMU.getAccelY_mss(),6);
//  Serial.print("\t");
//  Serial.print("Z Accel [m/s^2]: ");
//  Serial.print(IMU.getAccelZ_mss(),6);
//  Serial.print("\t");
//  Serial.print("X Gyro [rads]: ");
//  Serial.print(IMU.getGyroX_rads(),6);
//  Serial.print("\t");
//  Serial.print("Y Gyro [rads]: ");
//  Serial.print(IMU.getGyroY_rads(),6);
//  Serial.print("\t");
//  Serial.print("Z Gyro [rads]: ");
//  Serial.print(IMU.getGyroZ_rads(),6);
//  Serial.print("\t");
  Serial.print("X mag [muT]: ");
  Serial.print(IMU.getMagX_uT(),6);
  Serial.print("\t");
  Serial.print("Y mag [muT]: ");
  Serial.print(IMU.getMagY_uT(),6);
  Serial.print("\t");
  Serial.print("Z mag [muT]: ");
  Serial.print(IMU.getMagZ_uT(),6);
  Serial.print("\t");
  Ym = IMU.getMagY_uT();
  Xm = IMU.getMagX_uT();
  //Calculating Heading
  heading = atan2(Ym, Xm);

  // Correcting the heading with the declination angle depending on your location
  // You can find your declination angle at: https://www.ngdc.noaa.gov/geomag-web/
  // At Glenn Martin location it's 10 degrees => 0.174533 rad
  declination = 0.174533; 
  heading += declination;
  
  // Correcting when signs are reveresed
  if(heading <0) heading += 2*PI;
  // Correcting due to the addition of the declination angle
  if(heading > 2*PI)heading -= 2*PI;
  headingDegrees = heading * 180/PI; // The heading in Degrees unit
  // Smoothing the output angle / Low pass filter 
  headingFiltered = headingFiltered*0.85 + headingDegrees*0.15;
  //Sending the heading value through the Serial Port to Processing IDE
  Serial.print("Heading [degrees]: ");
  Serial.print(headingDegrees,0);
  Serial.print("\t");
  Serial.print("HeadingFiltered [degrees]: ");
  Serial.println(headingFiltered,0);
//  Serial.print("Temp [C]: ");
//  Serial.println(IMU.getTemperature_C(),6);
  delay(1);
}
