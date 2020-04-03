#include "input.h"
#include "input.h"
#include "encode.h"

InputEvent Input::waitInput()
{
	InputEvent event = InputEvent::None;

  static Encode enc;
  event = enc.get(); 
	
	return event;
}
