/*

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

Arduino code based on liquid crystal library + lcdproc source code
(see https://github.com/lcdproc/lcdproc/blob/master/server/drivers/hd44780-serial.h, HD44780_CT_LCDSERIALIZER)

 http://www.arduino.cc/en/Tutorial/LiquidCrystalSerialDisplay

*/


// include the library code:
#include <LiquidCrystal.h>

// UART config
const int baud = 9600;
const int escapeByte = 0xFE;

// display pinning & dimensions
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int rows = 2;
const int colums = 20;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(colums, rows);
  
  // initialize the serial communications:
  Serial.begin(baud);

  // give hint on how to send data to display
  lcd.clear();
  lcd.print("lcdproc hd44780");
  lcd.setCursor(0,1);
  lcd.print("lcdserializer");
}

// for instruction escape logic
uint8_t c = 0xFF;
bool instructionEscape = false;

// for timeout display logic
uint32_t timeoutCounter = 1;
uint32_t lastTimeReception = 0;
 
void loop()
{
    // logic to show message in case of no update
    timeoutCounter+=1;
    if((timeoutCounter>2000000) && (timeoutCounter%1000)==0)
    {
        // calculate time
        int seconds = ((millis()/1000) - lastTimeReception); // overflow might happen!
        int minutes = seconds/60;
        int hours = minutes/60;
        seconds = seconds%60;
        minutes = minutes%60;
        char timestring[20];
        snprintf(timestring,20,"%04d:%02d:%02d",hours,minutes,seconds);

        lcd.clear();
        lcd.print("no data since ");
        lcd.setCursor(0,1);        
        lcd.print(timestring);
    }

    while (Serial.available() > 0)
    {
        timeoutCounter=0;
        lastTimeReception = millis()/1000;
        // display each character to the LCD
        c = Serial.read();

        // last char was escape character
        if(instructionEscape == true)
        {
            instructionEscape = false;
            lcd.command(c);
        }
        else
        {
            if((c == escapeByte) ) // command escape character
            {
                instructionEscape = true;
            }
            else
            {
                lcd.write(c);  
            }  
        }
    }
}
