// 06.03.20 DAS 
// All rights not reservet
#include <Arduino.h>
#include <SPI.h>
#include "SdFat.h"

#define chipSelect 10
#define ROOT_PATH "/"
#define MAX_INDIR_FILES 32

typedef struct FileData
{
  char name[15];
  bool isDirectory;
} FileData;

class SDCrawler
{
private:
  SdFat sd;
  SdFile currentDir;
  char currentPath[32];
  FileData files[MAX_INDIR_FILES];
  int currentCount;
  
  void rewindCurrent();
  void go_back_path(char* path);
  void pathcat(char* path, char* dir);

public:
  SDCrawler() {}

  int getFilesCount(){
    return currentCount;
  }
  FileData* getFiles(){
    return files;
  }

  char* getPath(){
    return currentPath;
  }

  bool init();
  bool openDir(int index);
  void getFile(int index, SdFile& res);
};
