// 06.03.20 DAS 
// All rights not reservet
#ifndef INPUT_H
#define INPUT_H
#include <Arduino.h>

namespace Input{

  enum class InputEvent {None, Up, Down, Press}; 
  
  // input providers
  InputEvent waitInput(); // thread blocking func
  void checkInput();
  int isPending(); // check if new intup arrived via interrupt or check  
  InputEvent getInput();
}  
#endif
