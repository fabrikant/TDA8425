#ifndef TDA8425_h
#define TDA8425_h

#include "Arduino.h"
#include "Wire.h"
//===========================================================

#define   TDA8425_ADDRESS   0x41   

//===========================================================

#define   TDA8425_VOLL      0x00
#define   TDA8425_VOLR      0x01
#define   TDA8425_BASS      0x02
#define   TDA8425_TREBLE    0x03
#define   TDA8425_SWITCH    0x08
//===========================================================
#define   TDA8425_ML0_BIT   1<<1
#define   TDA8425_ML1_BIT   1<<2
#define   TDA8425_STL_BIT   1<<3
#define   TDA8425_EFL_BIT   1<<4
#define   TDA8425_MU_BIT    0x20
#define   TDA8425_SOURCE_BIT    1
#define   VOLUME_MASK      0x3F
#define   VOLUME_PREF      0xC0
#define   BASS_MASK        0x0F
#define   BASS_PREF        0xF0
#define   TDA_IN1          0
#define   TDA_IN2          1

class TDA8425

{
public:
  TDA8425 ();
  static void Init (boolean mute, byte volume, byte bass, byte treble, byte source);
  static void setVolume(byte param);
  static void setVolumeL(byte param);
  static void setVolumeR(byte param);
  static void setBass(byte param);
  static void setTreble(byte param);
  static void setMute(boolean param);
  static void setSource(byte param);
  static boolean getMute();
  static byte getVolumeL();
  static byte getVolumeR();
  static byte getBass();
  static byte getTreble();
  static byte getSource();
private:
  static void Write (byte adr, byte value);
  static byte setParam(byte adr,byte pref, byte mask, byte volume);

};
#endif
