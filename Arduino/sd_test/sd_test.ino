#include <SD.h>

void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  
  Serial.println("TEST BEGIN");
  SD.begin(10);

  File f = SD.open("test.txt", FILE_WRITE);
  if(f) 
  {
    f.println("This was written successfully to file.");
    f.flush();
    f.close();
  }
  else 
  {
    Serial.println("Error creating file..");
  }
  File d = SD.open("test.txt", FILE_READ);
  if(d) 
  {
    byte data;
    while ((data = d.read()) >= 0) 
    {
      Serial.print(data);
    }
    d.close();
  }
  else 
  {
    Serial.println("Error opening file for read..");
  }
  Serial.println("TEST COMPLETE");
}

void loop() 
{

}
