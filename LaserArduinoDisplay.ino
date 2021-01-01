

#include "U8glib.h"

U8GLIB_ST7920_128X64_1X u8g(13,11,10);	// SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
//These values are in the datasheet
#define RT0 10000   // Ω
#define B 3977      // K
//--------------------------------------


#define VCC 5    //Supply voltage
#define R 10000  //R=10KΩ

//Variables
float RT, VR, ln, TX, T0, VRT;
String mystring;
unsigned int len;
char buf;
static char temp[15];
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 10, "H2o:");   
  u8g.drawStr(30, 10, temp );
  u8g.drawStr(62, 10, "C" );
  u8g.drawStr( 0, 21, "Pump:");
   u8g.drawStr(62, 21, "L/H" );
}

void setup(void) {
  // flip screen, if required
  u8g.setRot180();
   T0 = 25 + 273.15;
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  
  pinMode(8, OUTPUT);
}

void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  //delay(50);
    VRT = analogRead(A0);              //Acquisition analog value of VRT
  VRT = (5.00 / 1023.00) * VRT;      //Conversion to voltage
  VR = VCC - VRT;
  RT = VRT / (VR / R);               //Resistance of RT

  ln = log(RT / RT0);
  TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor

  TX = TX - 273.15;                 //Conversion to Celsius
 
  Serial.print("Temperature:");
  Serial.print("\t");
  Serial.print(TX);
  Serial.print("C\t\t");
  Serial.print(TX + 273.15);        //Conversion to Kelvin
  Serial.print("K\t\t");
  Serial.print((TX * 1.8) + 32);    //Conversion to Fahrenheit
  Serial.println("F");
  dtostrf(TX, 3, 1, temp);
  delay(500);
}
