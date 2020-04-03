#include <Arduino.h>
#include "sdcrawler.h"
#include "input.h"
#include "display.h"

class FileGetter
{
private:
  SDCrawler crawler;
  Display* disp;
  
public:
  FileGetter(Display* pdisp){
      crawler.init();
      disp = pdisp;
  }

  void get(SdFile& s);
  void show(SdFile& s);
};
