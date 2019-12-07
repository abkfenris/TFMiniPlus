/*
 * ReadData.ino
 *
 *  Created on: Feb 24, 2019
 *      Author: Karim Mansour
 * Example on how to read data from the TFMiniPlus.
 * More info available in the github readme
 * Released under the GPL-3.0
 *
 * https://github.com/senegalo/tfmini-plus
 */

#include "./TFMiniPlus.h"

SYSTEM_THREAD(ENABLED);

SerialLogHandler log_handler;

TFMiniPlus tfmini;
int LIDAR_ENABLE_PIN = D0;

unsigned long since_log_ms = millis() - 5000;

void setup()
{
  pinMode(LIDAR_ENABLE_PIN, OUTPUT);
  digitalWrite(LIDAR_ENABLE_PIN, HIGH);
  // Start serial port to communicate with the TFMini
  // Default baud rate is 115200
  Serial1.begin(115200);

  // Pass the Serial class initialized to the tfmini
  tfmini.begin(&Serial1);

  // read millimeters
  tfmini.setMeasurementTo(TFMINI_MEASUREMENT_MM);

  tfmini.setFrameRate(0);
}

void loop()
{
  if (millis() - since_log_ms > 5000)
  {
    tfmini.triggerDetection();
    // read the data frame sent by the mini
    if (tfmini.readData())
    {
      // Distance "default in CM"
      uint16_t distance = tfmini.getDistance();

      Log.info("mm: %d", distance);

      // // Sensor tempreture in celsius
      uint16_t temp = tfmini.getSensorTemperature();
      Log.info("temp: %d", temp);

      // // Signal Strength
      uint16_t strength = tfmini.getSignalStrength();
      Log.info("strength: %d", strength);

      since_log_ms = millis();
    }
  }
}