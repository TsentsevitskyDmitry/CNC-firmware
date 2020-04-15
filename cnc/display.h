#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

class Display {

private:
  const int clock = 11; // pin E
  const int data = 13; // pin R/W
  const int cs = 12;  // pin CS
  const int maxnumlines = 4;
  // U8G2_ST7920_128X64_2_SW_SPI
  U8G2_ST7920_128X64_F_SW_SPI u8g2;

public:
  Display() : u8g2(U8G2_R0, clock, data, cs){
    u8g2.begin();
    u8g2.setFontMode(0);    // enable transparent mode, which is faster  
  }
  ~Display(){
  }
    
  void list(String lines[4], int pos);
  void print(String lines[4]);
  int numlines() {return maxnumlines;}

  void showLogo();
};
