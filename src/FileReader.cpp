#include "FileReader.h"
#include "SPIFFS.h"
using namespace std;

FileReader::FileReader(String fname)
{
    fileName = fname;
}


String FileReader::readFile()
{
    if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount SPIFFS");
  }

  // Open the file for reading
  File file = SPIFFS.open(fileName, "r");

  if (!file) {
    Serial.println("Failed to open file");
  }

  if (SPIFFS.exists("/morse_code.txt")) {
    Serial.println("File exists!");
  } else {
    Serial.println("File does not exist!");
  }

  String msg = "";
  // Read file contents into a String
  while (file.available()) {
    msg += (char)file.read();
  }
  file.close();

    // Print the file content
    Serial.println("File Content:");
    Serial.println(msg);
    
    return msg;
}