#include "display.h"

void Display::list(String lines[4], int pos)
{
  u8g2->firstPage();
  do {
      u8g2->setFont(u8g2_font_ncenB08_tr);
      u8g2->drawStr(2,10,lines[0].c_str());
      u8g2->drawStr(2,25,lines[1].c_str());
      u8g2->drawStr(2,40,lines[2].c_str());
      u8g2->drawStr(2,55,lines[3].c_str());
      u8g2->drawFrame(0,15*(pos%4), 128, 12);
//      u8g2->drawLine(10 + 15*(pos%4), 0 ,10 + 15*(pos%4) + 128, 0);
  } while ( u8g2->nextPage() );
}

void Display::print(String lines[4])
{
    u8g2->firstPage();
    do {
      u8g2->setFont(u8g2_font_ncenB08_tr);
      u8g2->drawStr(0,10,lines[0].c_str());
      u8g2->drawStr(0,25,lines[1].c_str());
      u8g2->drawStr(0,40,lines[2].c_str());
      u8g2->drawStr(0,55,lines[3].c_str());
    } while ( u8g2->nextPage() );
}  
