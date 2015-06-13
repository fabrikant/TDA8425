#include "TDA8425.h"
#include "Wire.h"

static byte tdaVolumeL; 
static byte tdaVolumeR;
static byte tdaBass;
static byte tdaTreble;
static byte tdaSwitch = B11101111;

TDA8425::TDA8425(){
  Wire.begin();
}

//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------

// void TDA8425::Init ()
// инициализация
void TDA8425::Init (boolean mute, byte volume, byte bass, byte treble, byte source)
{
  setVolume(volume);
  setBass(bass);
  setTreble(treble);
  setMute(mute);
  setSource(source);	
}

void TDA8425::setTreble(byte param)
{
  tdaTreble = setParam(TDA8425_TREBLE,BASS_PREF, BASS_MASK, param);
}

void TDA8425::setBass(byte param)
{
  tdaBass = setParam(TDA8425_BASS,BASS_PREF, BASS_MASK, param);
}


void TDA8425::setVolume(byte param)
{
  setVolumeL(param);
  setVolumeR(param);
}

void TDA8425::setVolumeL(byte param)
{
  tdaVolumeL = setParam(TDA8425_VOLL,VOLUME_PREF, VOLUME_MASK, param);
}

void TDA8425::setVolumeR(byte param)
{
  tdaVolumeR = setParam(TDA8425_VOLR,VOLUME_PREF, VOLUME_MASK, param);
}

void TDA8425::setMute(boolean param){
  if(param)
  {
    tdaSwitch |= TDA8425_MU_BIT;
  }
  else{
    tdaSwitch &= ~TDA8425_MU_BIT;
  }
  Write (TDA8425_SWITCH, tdaSwitch);
}

void TDA8425::setSource(byte param){
  if(param == TDA_IN1){
    tdaSwitch &= ~TDA8425_SOURCE_BIT;
    Write (TDA8425_SWITCH, tdaSwitch);
  } else if (param == TDA_IN2){
    tdaSwitch |= TDA8425_SOURCE_BIT;
    Write (TDA8425_SWITCH, tdaSwitch);
  }
}

boolean TDA8425::getMute() {
  byte res = tdaSwitch & TDA8425_MU_BIT;
  return res == TDA8425_MU_BIT;
}

byte TDA8425::getVolumeL() {
  return tdaVolumeL^VOLUME_PREF;
}

byte TDA8425::getVolumeR() {
  return boolean(tdaVolumeR^VOLUME_PREF);
}

byte TDA8425::getBass() {
  return tdaBass^BASS_PREF;
}

byte TDA8425::getTreble() {
  return tdaTreble^BASS_PREF;
}

byte TDA8425::getSource() {
  return tdaSwitch&TDA_IN2;
}
//------------------------------------------------------------------------------
// PRIVATE FUNCTIONS
//------------------------------------------------------------------------------

byte TDA8425::setParam(byte adr,byte pref, byte mask, byte volume){
  byte res = volume;
  if (res > mask) res = mask;
  res = pref | res;
  Write (adr, res);
  return res;
}

void TDA8425::Write (byte adr, byte value)
{
  Wire.beginTransmission(TDA8425_ADDRESS);
  Wire.write (adr);
  Wire.write (value);
  Wire.endTransmission();
}
