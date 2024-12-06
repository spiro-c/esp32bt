// /**
//  * @file streams-a2dp-serial.ino
//  * @author Phil Schatzmann
//  * @brief see https://github.com/pschatzmann/arduino-audio-tools/blob/main/examples/examples-stream/streams-a2dp-serial/README.md
//  *
//  * @author Phil Schatzmann
//  * @copyright GPLv3
//  *
//  */
#include "Arduino.h"
#include "AudioTools.h"
#include "AudioTools/AudioLibs/A2DPStream.h"
AudioInfo from(44100, 2, 16);
AudioInfo to(22050, 1, 16);
I2SStream i2sStream; // Access I2S as stream
A2DPStream a2dpStream;
FormatConverterStream conv(i2sStream);
//ResampleStream resample(i2sStream);
StreamCopy copier(conv, a2dpStream); // copy  a2dpStream to i2sStream

// Arduino Setup
void setup(void)
{
  Serial.begin(115200);
  while (!Serial)
    ;
  AudioLogger::instance().begin(Serial, AudioLogger::Error);

  // start i2s input
  auto cfg = i2sStream.defaultConfig(TX_MODE);
  cfg.i2s_format = I2S_STD_FORMAT;
  cfg.sample_rate = 44100;
  cfg.is_master = false;
  i2sStream.begin(cfg);

  conv.begin(from, to);

  auto cfgA2DP = a2dpStream.defaultConfig(RX_MODE);
  cfgA2DP.name = "Esp32Bluetooth";
  //cfg.sample_rate = 44100;
  // set intial volume
  a2dpStream.setVolume(0.5);

  a2dpStream.begin(cfgA2DP);
}

// Arduino loop - copy data
void loop()
{
  copier.copy();
}
