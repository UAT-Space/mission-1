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
#define GPIOA  14 // GPIO A / A0

float gps_time;
float latitude;
float longitude;
float altitude;
char SERIAL_ERROR = "ERR: Empty Buffer";

SoftwareSerial radio = SoftwareSerial(ssRX, ssTX);


//-----------------------------------------------------
//-FUNCTION DECLARATIONS-//
void transmit(char message);


//-----------------------------------------------------
//-SETUP-//

void setup()
{
  // start radio connection
  pinMode(ssRX, INPUT);
  pinMode(ssTX, OUTPUT);
  radio.begin(9600);

  transmit("Eagle Online..");
  transmit("==============");
  transmit("Starting GPS..");

  pinMode(gpsRX, INPUT);
  pinMode(gpsTX, OUTPUT);
  Serial.begin(9600);
  while (!Serial);
}


//-----------------------------------------------------
//-LOOP-//

void loop()
{
  delay(30000);
  if (Serial.available() > 0)
  {
    if (Serial.find("$GPGGA,"))
    {
      // parse GPGGA for data we care about
      gps_time = (Serial.parseFloat() - 70000); // hhmmss.sss
      latitude = Serial.parseFloat();           // N,  xxxx.xxxx
      longitude = Serial.parseFloat();          // W, xxxxx.xxxx
      Serial.parseInt();                        // Connection quality indicator
      Serial.parseInt();                        // # of satellites collected
      Serial.parseFloat();                      // HDOP
      altitude = Serial.parseFloat();           // Altitude, Meters

      // transmit data to ground
      radio.print(gps_time);
      radio.print(",");
      radio.print(latitude);
      radio.print(",");
      radio.print(longitude);
      radio.print(",");
      radio.println(altitude);
    }
  }
  else
  {
    transmit(SERIAL_ERROR);
  }
}


//-----------------------------------------------------
//-FUNCTIONS-//

/// Sends a message over radio
void transmit(char message)
{
  radio.println(message);
}
