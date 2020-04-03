// 06.03.20 DAS 
// All rights not reservet
#include <Arduino.h>
#include "input.h"

// encode pins
#define ENCODE_PIN_A 4
#define ENCODE_PIN_G 5
#define ENCODE_PIN_B 6
#define ENCODE_PIN_PRESS 2
#define ENCODE_PIN_PRESS_G 3

using namespace Input;

class Encode
{
private:
  unsigned char encoder_A;
  unsigned char encoder_B;
  unsigned char encoder_A_prev=1;
  unsigned char encoder_PRESS;
  unsigned char encoder_PRESS_prev = 1;
  
public:
  Encode() 
  {
    pinMode(ENCODE_PIN_G, OUTPUT);
    pinMode(ENCODE_PIN_PRESS_G, OUTPUT);
    digitalWrite(ENCODE_PIN_G, LOW);
    digitalWrite(ENCODE_PIN_PRESS_G, LOW);
    pinMode(ENCODE_PIN_A, INPUT_PULLUP);
    pinMode(ENCODE_PIN_B, INPUT_PULLUP);
    pinMode(ENCODE_PIN_PRESS, INPUT_PULLUP);
  }

  InputEvent get(); 
};
