/*
 * TFMiniPlus.h
 *
 *  Created on: Feb 9, 2019
 *      Author: Karim Mansour
 * An Arduino driver for the TFMiniPlus Lidar System
 *
 * Released under the GPL-3.0
 *
 * https://github.com/senegalo/tfmini-plus
 */

#ifndef TFMINIPLUS_H_
#define TFMINIPLUS_H_

#include <cstddef>

#include "Particle.h"

#define TFMINI_MEASUREMENT_CM 0x0165
#define TFMINI_MEASUREMENT_MM 0x066A

using namespace std;

class TFMiniPlus
{
public:
  TFMiniPlus();
  void begin(Stream *serial);
  bool readData();
  uint16_t getDistance();
  double getSensorTemperature();
  uint16_t getSensorRawTemperature();
  uint16_t getSignalStrength();
  String getVersion();
  bool systemReset();
  bool setFrameRate(uint16_t rate);
  void triggerDetection();
  bool setMeasurementTo(uint16_t measurment);
  bool setBaudRate(uint32_t baud);
  bool setEnabled(bool state);
  bool restoreFactorySettings();
  bool saveSettings();

private:
  char _readDataBuffer[9];
  Stream *_stream;
  void write(const char buffer[], const size_t length);
  bool readCommandResponse(char buffer[], size_t buffer_size);
  void skipToFrameHeader(uint8_t farameHeader);

  static bool validateChecksum(const char buffer[], const size_t length);
  static uint8_t generateChecksum(const char buffer[], size_t length);
  static void resetBuffer(char buffer[], size_t length);
  static void copyBuffer(char buffer1[], const char buffer2[], size_t buffer_size, size_t length);
  static uint16_t readInt16FromBuffer(const char buffer[], size_t startIndex);
  static uint32_t readInt32FromBuffer(const char buffer[], size_t startIndex);
};

#endif