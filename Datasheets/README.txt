Flight Computer Module [By Kenneth Vorseth]
>>For UAT SPACE Program

FlightComputer.brd : Eagle Circuit Board File
FlightComputer.sch : Eagle Schematic (VERY USEFUL!)

Temperature Rating: -40C to 85C (CPU: -40C to 105C)

Microcontroller Pinout Connections
---------------------------------------------
AVR	|    Arduino	|	Usage       |
---------------------------------------------
PD0	|	0	| UART RX   (GPS/PC)|
PD1	|	1	| UART TX   (GPS/PC)|
PD2	|	2	| 1Hz Interrupt     |
PD3	|	3	| Servo A	    |
PD5	|	5	| Servo B	    |
PD6	|	6	| Servo C	    |
PD7	|	7	| SOFT RX (RADIO RX)|
PB0	|	8	| SOFT TX (RADIO TX)|
PB2	|	10	| SS   (ISP/SD CARD)|
PB3	|	11	| MOSI (ISP/SD CARD)|
PB4	|	12	| MISO (ISP/SD CARD)|
PB5	|	13	| SCK  (ISP/SD CARD)|
PC0	|	14/A0	| GPIO A	    |
PC1	|	15/A1	| GPIO B            |
PC2	|	16/A2	| GPIO C  	    |
PC4	|	18	| SDA       (BNO055)| 
PC5	|	19	| SCL	    (BNO055)|
---------------------------------------------

Usage Notes:
- Arduino Bootloader needs to be programmed via provided ISP header.
- When programming the device, use an FTDI cable attached to the designated pinout.
	-> Note that external power (VIN) must be supplied, and the PC must share GND.
	-> This means that you CANNNOT USE A LAPTOP BATTERY, PLUG IN LAPTOP.
- Power Supply (VIN) needs to be greater than 9 Volts.
- Do NOT power manually the 5V or 3.3V rails.
- The uBlox MAX8 GPS should interrupt the MCU once every second (1Hz).
	-> This can be used as an internal timekeeping method.
- The Micro SD Card is hooked up via SPI.
- The Inertial Measurement Unit (BNO055) is hooked up via I2C.
	-> The default address for the BNO055 is in the datasheet.
- Using the two jumpers, you can swap between using the UART with...
	-> Left Position:  UART TO GPS (For use in Field)
	-> Right Position: UART TO PC (FTDI for Programming/Serial Monitor)
- The RS-232 serial port is 12V tolerant, do NOT try to use 5V on this!
