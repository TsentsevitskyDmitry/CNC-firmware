#include "sdcrawler.h"

void debugLog(char* msg)
{
  #ifdef USART_OUTPUT
  Serial.println(msg);
  #endif
}

bool SDCrawler::init()
{
  debugLog("Initializing SD card...");
  pinMode(chipSelect, OUTPUT);
  
  while (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    debugLog("initialization failed!");
//    return false;
  }
  debugLog("initialization done.");
  
  strcpy(files[0].name, "..");
  files[0].isDirectory = true;
  strcpy(currentPath, ROOT_PATH);
  currentDir.open(currentPath);
  rewindCurrent();
  return true;
}

void SDCrawler::go_back_path(char* path)
{
  char* last_slash;
  while(*path != 0){
    if(*path == '/' && *(path + 1) != 0)
      last_slash = path;
    ++path;
  }
  *(last_slash + 1) = 0;
}

void SDCrawler::pathcat(char* path, char* dir)
{
  while(*path != 0) path++;
  while(*dir != 0){
    *path = *dir;
    ++path;
    ++dir;
  }
  *path = '/';
  *(path + 1) = 0;
}

bool SDCrawler::openDir(int index)
{
  if (!files[index].isDirectory || index >= MAX_INDIR_FILES || index < 0)
    return false;
    
  if (index != 0)
    pathcat(currentPath, files[index].name);
  else if (currentPath[strlen(ROOT_PATH)] != 0)
    go_back_path(currentPath);
  else
    return true;   

  currentDir.close();
  currentDir.open(currentPath);
  rewindCurrent();
  return true;
}

void SDCrawler::rewindCurrent()
{
    currentCount = 1;
    currentDir.rewind();
    SdFile entry; 
      
    while(true) {
     bool res = entry.openNext(&currentDir, O_RDONLY);
     if (!res) break;
          
     entry.getName(files[currentCount].name, 15);
     files[currentCount].isDirectory = false;
     
     if (entry.isDir())
      files[currentCount].isDirectory = true;

     entry.close();
     currentCount++;
   }
}

void SDCrawler::getFile(int index, SdFile& res)
{
  if (files[index].isDirectory || index >= MAX_INDIR_FILES || index < 0)
    return false;  

  int i = 1;
  currentDir.rewind();
  while(true){
      res.openNext(&currentDir, O_RDONLY);

      if(i == index) break;
      else           res.close();

      ++i;
    }
}

SDCrawler::~SDCrawler()
{
  currentDir.close();
}
