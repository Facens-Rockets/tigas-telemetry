#ifndef INCLUDE_TASKS_SAVE_FILE_H__
#define INCLUDE_TASKS_SAVE_FILE_H__
#include <LITTLEFS.h>
#include <time.h>

#include "FS.h"
#include "heltec.h"
#include "setup_tasks.hpp"

#define FORMAT_LITTLEFS_IF_FAILED true

void listDir(fs::FS& fs, const char* dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");

#ifdef CONFIG_LITTLEFS_FOR_IDF_3_2
      Serial.println(file.name());
#else
      Serial.print(file.name());
      time_t t = file.getLastWrite();
      struct tm* tmstruct = localtime(&t);
      Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n",
                    (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1,
                    tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min,
                    tmstruct->tm_sec);
#endif

      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");

#ifdef CONFIG_LITTLEFS_FOR_IDF_3_2
      Serial.println(file.size());
#else
      Serial.print(file.size());
      time_t t = file.getLastWrite();
      struct tm* tmstruct = localtime(&t);
      Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n",
                    (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1,
                    tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min,
                    tmstruct->tm_sec);
#endif
    }
    file = root.openNextFile();
  }
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("- failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("- message appended");
    } else {
        Serial.println("- append failed");
    }
    file.close();
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }

    Serial.println("- read from file:");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void save_file_code(void* parameters) {
  if (!LITTLEFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    Serial.println("LITTLEFS Mount Failed");
    return;
  }

  listDir(LITTLEFS, "/", 0);
  uint64_t timer = millis();
  appendFile(LITTLEFS, "/hello.txt", "World!\r\n");
  Serial.print("time to append: "); Serial.println(millis() - timer);
  readFile(LITTLEFS, "/hello.txt");



  while (true) {
    vTaskDelay(1);
  }
}

#endif  // INCLUDE_TASKS_SAVE_FILE_H__
