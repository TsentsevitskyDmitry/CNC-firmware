#include "display.h"
#include "input.h"

class ListChecker
{
private:
  Display* disp;
  int check_base(bool header, String* list, size_t count);

public:
  ListChecker(Display* disp);

  int check(String* list, size_t count);
  int header_check(String* list, size_t count);
};
