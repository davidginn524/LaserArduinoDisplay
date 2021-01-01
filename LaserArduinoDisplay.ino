

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
unsigned int len;
unsigned char tcheck; 
static char temp[15];
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 10, "H2o:");   
  u8g.drawStr(30, 10, temp );
  u8g.drawStr(62, 10, "C" );
  tempcheck();
  u8g.drawStr( 0, 21, "Pump:");
  u8g.drawStr(62, 21, "L/H" );
  pumpcheck();
}
void tempcheck(void){
    //u8g.drawStr(70, 10, "test" );
}
void pumpcheck(void){
  
}
void setup(void) {
  // flip screen, if required
  u8g.setRot180();
   T0 = 25 + 273.15;

  
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
  dtostrf(TX, 3, 1, temp);
  delay(500);
  tcheck = "ok";
 
  
}
