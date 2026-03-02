#include "FastIMU.h"
#include <Wire.h>

#define IMU_ADDRESS 0x68    //Change to the address of the IMU
// #define PERFORM_CALIBRATION //Comment to disable startup calibration
MPU6500 IMU;               //Change to the name of any supported IMU! 

// Currently supported IMUS: MPU9255 MPU9250 MPU6886 MPU6500 MPU6050 ICM20689 ICM20690 BMI055 BMX055 BMI160 LSM6DS3 LSM6DSL QMI8658

calData calib = { 0 };  //Calibration data
AccelData accelData;    //Sensor data
GyroData gyroData;
MagData magData;
float TempData = 0.0;
int CMSData = 0;

void setup() {
  Wire.begin();
  Wire.setClock(400000); //400khz clock
  Serial.begin(115200);
  //waiting until serial is ready
  while (!Serial) {
    ;
  }
  Serial.println("Project Kurinda initializing...");
  //checking for connection with IMU
  int err = IMU.init(calib, IMU_ADDRESS);
  if (err != 0) {
    Serial.print("Error initializing IMU: ");
    Serial.println(err);
    while (true) {
      ;
    }
  }
//performs calibration for the IMU
  Serial.println("Project Kurinda calibration & data example");

  Serial.println("Keep IMU level.");
  delay(1000);
  IMU.calibrateAccelGyro(&calib);
  Serial.println("Calibration done!");
  // Serial.println("Accel biases X/Y/Z: ");
  // Serial.print(calib.accelBias[0]);
  // Serial.print(", ");
  // Serial.print(calib.accelBias[1]);
  // Serial.print(", ");
  // Serial.println(calib.accelBias[2]);
  // Serial.println("Gyro biases X/Y/Z: ");
  // Serial.print(calib.gyroBias[0]);
  // Serial.print(", ");
  // Serial.print(calib.gyroBias[1]);
  // Serial.print(", ");
  // Serial.println(calib.gyroBias[2]);

  IMU.init(calib, IMU_ADDRESS);

  //err = IMU.setGyroRange(500);      //USE THESE TO SET THE RANGE, IF AN INVALID RANGE IS SET IT WILL RETURN -1
  //err = IMU.setAccelRange(2);       //THESE TWO SET THE GYRO RANGE TO ±500 DPS AND THE ACCELEROMETER RANGE TO ±2g
  
  if (err != 0) {
    Serial.print("Error Setting range: ");
    Serial.println(err);
    while (true) {
      ;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  IMU.update();
  IMU.getAccel(&accelData);
  IMU.getGyro(&gyroData);
  TempData = IMU.getTemp();
  Serial.println((String)"Temperatre: "+TempData+" C");
  CMSData = analogRead(A0);  
  Serial.println((String)"Soil Moisture: "+CMSData);

  delay(1000);
}
