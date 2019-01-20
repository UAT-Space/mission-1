#include <SD.h>
#include <SoftwareSerial.h>

#define gpsRX  0  // UART RX (GPS/PC)
#define gpsTX  1  // UART TX (GPS/PC)
#define ticTok 2  // 1Hz Interrupt
#define servoA 3  // Servo A
#define servoB 5  // Servo B
#define servoC 6  // Servo C
#define ssRX   7  // SoftwareSerial RX (Radio RX)
#define ssTX   8  // SoftwareSerial TX (Radio TX)
#define SDcs   10 // SD card Chip Select pin

// Time keeping variable
volatile int second = 0;

SoftwareSerial radio = SoftwareSerial(ssRX, ssTX);

//-----------------------------------------------------

void incrementSecond();
void initializeFilesystem();
//void logMessage(char message);
void recordData(char data);
void transmit(char message);


//-----------------------------------------------------

void setup() 
{
  // start radio connection
  pinMode(ssRX, INPUT);
  pinMode(ssTX, OUTPUT);
  radio.begin(9600);

  transmit("Eagle Online..");
  transmit("==============");

  transmit("Starting SD..");

  if (!SD.begin(SDcs)) 
  {
    transmit("SD FAILED to start..");
    while (1); // do nothing - reboot needed
  }

  transmit("Done.");
  transmit("Starting Filesystem..");

  initializeFilesystem();

  transmit("Done.");

  // interrupt to track time (in seconds)
  attachInterrupt(digitalPinToInterrupt(ticTok), incrementSecond, CHANGE);  // mode unsure

  transmit("Starting GPS..");

  pinMode(gpsRX, INPUT);
  pinMode(gpsTX, OUTPUT);
  Serial.begin(9600);
  while (!Serial);

  transmit("Done.");
//  logMessage("Boot Complete.");
  transmit("Boot Complete.");
}

//-----------------------------------------------------

void loop() 
{
  // pass
}


//-----------------------------------------------------
//-FUNCTIONS-//

/// Sends a message over radio
void transmit(char message)
{
  radio.println(message);
}


/// Records data to file
void recordData(char data)
{
  File f = SD.open("/data.txt");
  f.print(second);
  f.print(",");
  f.println(data);
  f.close();
}


/// Sets up initial state of files
void initializeFilesystem()
{
  //====CHECK FOR DATA FILE====//
  if (SD.exists("/data.txt"))
  {
    transmit("Previous data found..");
    // if dataDump doesn't exist, create it
    if (!SD.exists("/Archive/dataDump.txt"))
    {
      File f = SD.open("/Archive/dataDump.txt");
      if (f)
      {
        f.flush();
        f.close();
      }
    }

    // copy content of data to dataDump
    transmit("Archiving data..");
    File readFile = SD.open("/data.txt", FILE_READ);
    File writeFile = SD.open("/Archive/dataDump.txt", FILE_WRITE);
    writeFile.println(" ");
    writeFile.println("NEW DUMP");
    writeFile.println(" ");
    byte data;
    while ((data = readFile.read()) >= 0)
    {
      writeFile.write(data);
    }

    readFile.close();
    writeFile.flush();
    writeFile.close();

    // remove original data file
    if (!SD.remove("/data.txt"))
    {
      transmit("Error removing data..");
    }
  }

  if (!SD.exists("/data.txt"))
  {
    File f = SD.open("/data.txt", FILE_WRITE);
    f.flush();
    f.close();
  }
  else
  {
    transmit("ERROR: Data file already exists..");
  }
}


/// Interrupt Service Routine - Track time
/// Do not manually call - interrupt only.
void incrementSecond()
{
  ++second;
}


///// Writes an event to the log file
//void logMessage(char message)
//{
//  File f = SD.open("/log.txt");
//  f.print(second);
//  f.print(": ");
//  f.println(message);
//  f.close();
//}
