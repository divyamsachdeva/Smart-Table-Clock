#include <DS3231.h>   //Library for RTC

#include <Wire.h>   //Allows comunication with TWI (Two Wire Interface)

#include <LiquidCrystal.h>  //Used for DS3231 and thermister


DS3231  rtc(SDA, SCL);

Time  t;

#define buz 11

int tempPin = 0;

int Hor;

int Min;

int Sec;

int tempC;
int tempF;

int tempCDS3231;
int tempFDS3231;


//-------------------------------------------------------------------------
// Used to fix Date, Time, Day of Week

// Uncomment to adjust. Be sure to // back once fixed.

//rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY

//rtc.setTime(01, 33, 00);     // Set the time to 12:00:00 (24hr format)

//rtc.setDate(23, 8, 2018);   // Set the date to August 8th, 2018

//--------------------------------------------------------------------------


void setup()

{

  Wire.begin();

  rtc.begin();

  Serial.begin(9600);

  pinMode(buz, OUTPUT);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);

  t = rtc.getTime();

  Hor = t.hour;

  Min = t.min;

  Sec = t.sec;



}


//---------------------------------------------------------------------


void loop()

{
  int tempReading = analogRead(tempPin);
  // This is OK
  double  tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  int tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  int tempF = (tempC * 9.0) / 5.0 + 32.0; // Convert Celcius to Fahrenheit

  //-------------------------------------------------------------------------------------------
  //Can change the ABOVE tempC and tempF "int" to "float" this can give you temperatures with two decimal points.
  //Can also use "lcd.print(tempF, 1);" BELOW to print with one decimal place or "lcd.print(tempF, 0);" // print without decimal place
  //-------------------------------------------------------------------------------------------

  lcd.setCursor(0, 0); //Top line of the LCD
  lcd.print("    ");
  lcd.print(rtc.getTimeStr());
  lcd.print("    ");
  lcd.setCursor(0, 1);
  lcd.print("      ");
  lcd.print(rtc.getDateStr());


  //----------------------------------------------------------

  lcd.setCursor(0, 1); //Second line of the LCD

  tempFDS3231 = (tempCDS3231 * 1.8) + 32.0; // Convert C to F
  tempCDS3231 = (rtc.getTemp());

  lcd.setCursor(0, 1);
  lcd.print(tempF);
  lcd.print((char)223); //This creates a Degree symbol
  lcd.print("F  ");
  lcd.print(rtc.getDateStr());


  //--------------------------------------------------------------------------

  t = rtc.getTime();

  Hor = t.hour;

  Min = t.min;

  Sec = t.sec;


  //-------------------------------------------------------------------------------------------
  //Use the BELOW "if" statement to set your desired alarm time
  if ( Hor == 10 &&  (Min == 00 || Min == 00)) //Comparing the current time with the Alarm time
    //-------------------------------------------------------------------------------------------

  {
    Buzzer();

    Buzzer();

    lcd.clear();

    lcd.print("Alarm ON");

    lcd.setCursor(0, 1);

    lcd.print("Wake Up!!");

    Buzzer();

    Buzzer();


  }
  delay(1000);

}




void Buzzer()

{

  digitalWrite(buz, HIGH);

  delay(500);

  digitalWrite(buz, LOW);

  delay(500);


}
