#include "filegetter.h"
SdFile binFile;

void setup()
{
  Serial.begin(9600);

  // setup 
  Display disp;
  disp.showLogo();
  FileGetter getter(&disp);

  // getting file with display and encoder
  getter.get(binFile);
  getter.show(binFile);

  // work with file
  Serial.println("file");
  char buff[32];
  binFile.getName(buff, 32);
  Serial.println(buff);
  Serial.println("file size");
  Serial.println(binFile.fileSize());
  Serial.println("file available");
  Serial.println(binFile.available());
  Serial.println("firts byte");
  Serial.println((int)(binFile.read()));

  // any stuff
  pinMode(LED_BUILTIN, OUTPUT);
}

 
void loop()
{
  analogWrite(LED_BUILTIN, (sin((millis()%1300)/100.0) + 1.0) * 127);   // turn the LED on (HIGH is the voltage level) 
}
