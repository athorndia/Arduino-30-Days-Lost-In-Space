/* This code demonstrates how to use an OLED or Organic Light Emitting Diode Display. 
This OLED display has a length of 128 pixels and a height of 64 pixels, which means it has that many
separate LEDs that can be turned on and off in order to create a graphical image or text image. 
That's 8,192 separate LEDs! 

A communicating protocal that can be used between communicating devices help utilize gobs of LEDs.
A protocol is a set of rules and guidelines for communicating data. 
We want to design a protocol that can be used to communicate between the HERO and the OLED display. 
Remember to install OLED library (<PololuOLED.h> and <U8glib-HAL.h>). Check Day16 to manually import .zip libraries. 

I2C Communication Protocol sends data through a single wire.
It carries a message in the form of data packets that are communicated between the two devices (HERO -> OLED) 
using clock wire pulses and data wire pulses.

OLED Display has 4 pins GND (0v /negative voltage supply), VCC (5v /positive voltage supply), SCL (Serial Clock), and SDA (Serial Data).

GND will be connected to GND pin of the HERO Board, just like other components.
VCC will be connected to 5v pin of the HERO Board, just like other components as well. 
SCL will syncronize the devices. Connected to pin A5
SDA will ***. Connected to pin A4.

Pins A4 and A5 should be used for components requiring I2C communication such as the 128 x 64 OLED display. 
*/

// ********************************************************* //

// #include <U8glib.h> causes Compilation error: U8glib.h: No such file or directory (on macbook only...PC does not error)
#include <U8glib-HAL.h>
#include <PololuOLED.h>
 
// Type of graphical object | name of our object of this type
U8GLIB_SH1106_128X64  My_u8g_Panel(U8G_I2C_OPT_NONE); // I2C / TWI

// Custom function that draws things on the OLED screen. Does not return values.
// One of the things we can do is write one item of text on the screen in a particular location.  
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  My_u8g_Panel.setFont(u8g_font_unifont); // unicode font 

  // drawstring command that takes 3 different inputs.
  // x position, Y position, and the actual string data that is to be printed out on the panel.
  My_u8g_Panel.drawStr( 0, 10, "Build"); // upper left to right and down.
  My_u8g_Panel.drawStr( 0, 30, "everything!");
  My_u8g_Panel.drawStr( 0, 50, "Invent safe!!");
}
 
// ********************************************************* //

void setup(void) {
  // flip screen, if required
  // My_u8g_Panel.setRot180(); // If we mount the panel upside down we might want to flip the display 180 degrees.
 
  // assign default color value
  My_u8g_Panel.setColorIndex(1); // We have a monochrome display that can display different grey levels. Default brightness is set to intermediate grey level 1. 
 
 // pinMode(8, OUTPUT);
}

// ********************************************************* //

void loop(void) {
  // picture do-while loop will execute repeatedly until My_u8g_Panel.nextPage returns a 0, which means it's done.
  My_u8g_Panel.firstPage();
  do {
    draw(); // call draw repeatedly until do loop finishes. 
  } while( My_u8g_Panel.nextPage() );
}
