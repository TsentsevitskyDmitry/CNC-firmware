#include "SdFat.h"

#define SERIAL_SOURCE 0x00
#define SDFILE_SOURCE 0x01

class DeviceSelector
{
private:
  SdFile* sdfile;
  int selected;

public:
  DeviceSelector (SdFile* sdfile);
  void set(int index);
  int available();
  int read();
};
