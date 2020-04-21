#include "ListChecker.h"

ListChecker::ListChecker(Display* disp)
{
  this->disp = disp;
}

int ListChecker::check_base(bool header, String* list, size_t count)
{
  int pos = header;
  int fsett = 0;
  count += header;
  int numlines = disp->numlines();    

  while(1){
    fsett = pos / numlines;
    int ln = (count - fsett*numlines) < numlines ? count%numlines : numlines;

    String lines[numlines];
    
    int i = 0;
    for(; i < ln; ++i){
      lines[i] = list[fsett*numlines + i];    
    }
    for(; i < numlines; ++i){
      lines[i] = "";    
    }
    
    disp->list(lines, pos);

    Input::InputEvent st = Input::waitInput();
    if (st == Input::InputEvent::Down && pos < count-1) pos += 1;
    if (st == Input::InputEvent::Up && pos > header) pos -= 1;
    if (st == Input::InputEvent::Press) 
      return pos - header;
  }
}

int ListChecker::check(String* list, size_t count)
{
  return check_base(false, list, count);
}

int ListChecker::header_check(String* list, size_t count)
{
  return check_base(true, list, count);
}
