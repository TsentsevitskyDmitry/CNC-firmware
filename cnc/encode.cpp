#include "encode.h"

InputEvent Encode::get()
{
  InputEvent event = InputEvent::None;
  while (1)
  { 
      encoder_A = digitalRead(ENCODE_PIN_A);      // считываем состояние выхода А энкодера 
      encoder_B = digitalRead(ENCODE_PIN_B);      // считываем состояние выхода B энкодера    
      encoder_PRESS = digitalRead(ENCODE_PIN_PRESS);      // считываем состояние выхода B энкодера    

      if (!encoder_PRESS && encoder_PRESS_prev)
        event = InputEvent::Press;
        
      if((!encoder_A) && (encoder_A_prev)) // если состояние изменилось с положительного к нулю
      {  
        if(encoder_B){
          event = InputEvent::Up; 
          }              
        else {
         event = InputEvent::Down; 
         }
      }
         
      encoder_A_prev = encoder_A;     // сохраняем значение А для следующего цикла 
      encoder_PRESS_prev = encoder_PRESS;
      if(event != InputEvent::None)
        break;
  }
  return event;                       
}
