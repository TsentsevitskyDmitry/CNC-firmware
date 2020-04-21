#include "DeviceSelector.h"
  
DeviceSelector::DeviceSelector (SdFile* sdfile)
{
  this->sdfile = sdfile;
}

void DeviceSelector::set(int index)
{
  selected = index;  
}

int DeviceSelector::available()
{
  switch (selected)
  {
    case SERIAL_SOURCE:
      return Serial.available();

    case SDFILE_SOURCE:
      return sdfile->available();  
  } 
}

int DeviceSelector::read()
{
  switch (selected)
  {
    case SERIAL_SOURCE:
      return Serial.read();

    case SDFILE_SOURCE:
      return sdfile->read();  
  } 
}
