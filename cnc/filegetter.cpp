#include "filegetter.h"

void FileGetter::get(SdFile& s)
{
  int pos = 0;
  int fsett = 0;

  while(1){
    int numlines = disp->numlines();
    int filescount = crawler.getFilesCount();
    FileData* files = crawler.getFiles();
    String lines[numlines];
    
    fsett = pos / numlines;
    int ln = (filescount - fsett*numlines) < numlines ? filescount%numlines : numlines;
    
    int i = 0;
    for(; i < ln; ++i){
      String dir = files[fsett*numlines + i].isDirectory ? "/" : "";
      lines[i] = files[fsett*numlines + i].name + dir;    
    }
    for(; i < numlines; ++i){
      lines[i] = "";    
    }
    
    disp->list(lines, pos);

    Input::InputEvent st = Input::waitInput();
    if (st == Input::InputEvent::Down && pos < filescount-1) pos += 1;
    if (st == Input::InputEvent::Up && pos > 0) pos -= 1;
    if (st == Input::InputEvent::Press) 
      if(files[pos].isDirectory) {
        crawler.openDir(pos); 
        pos = 0;
        }
      else {
       return crawler.getFile(pos, s);
      }
  }
}

void FileGetter::show(SdFile& s)
{
  int numlines = disp->numlines();
  String lines[numlines] = {};
  lines[0] = "File inside:";

  char c = 0;
  int i = 1;
  while(s.available() && i < numlines){
    c = s.read();
    if(c == '\n') i++;
    else lines[i] += c;
  }  
      
  s.rewind();
  disp->print(lines);
}
