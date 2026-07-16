#include <SPI.h>
#include "images.h"

//Arduino Parameters 
#define LED   A0
#define CS    A2
#define RS    A3
#define RESET A4

/////////////////////////////////////////////
//////screen initialization functions////////
/////////////////////////////////////////////

void Lcd_Writ_Bus(unsigned char d)
{
  SPI.transfer(d);
}

void Lcd_Write_Com(unsigned char VH)
{
  *(portOutputRegister(digitalPinToPort(RS))) &=  ~digitalPinToBitMask(RS);//LCD_RS=0;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Data(unsigned char VH)
{
  *(portOutputRegister(digitalPinToPort(RS))) |=  digitalPinToBitMask(RS); //LCD_RS=1;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Com_Data(unsigned char com, unsigned char dat)
{
  Lcd_Write_Com(com);
  Lcd_Write_Data(dat);
}

void Address_set(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
  Lcd_Write_Com(0x2a);
  Lcd_Write_Data(x1 >> 8);
  Lcd_Write_Data(x1);
  Lcd_Write_Data(x2 >> 8);
  Lcd_Write_Data(x2);
  Lcd_Write_Com(0x2b);
  Lcd_Write_Data(y1 >> 8);
  Lcd_Write_Data(y1);
  Lcd_Write_Data(y2 >> 8);
  Lcd_Write_Data(y2);
  Lcd_Write_Com(0x2c);
}


void SPI_Init(void)
{
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2); // 4 MHz (half speed)
  //SPI.setClockDivider(SPI_CLOCK_DIV128); // sloooooow
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
}

void Lcd_Init(void)
{
  digitalWrite(RESET, HIGH);
  delay(5);
  digitalWrite(RESET, LOW);
  delay(15);
  digitalWrite(RESET, HIGH);
  delay(15);

  //ST7789H2 Init
  digitalWrite(CS, LOW); //CS
  Lcd_Write_Com(0x36);
  Lcd_Write_Data(0x00);

  Lcd_Write_Com(0x3A);
  Lcd_Write_Data(0x05);

  Lcd_Write_Com(0xB2);
  Lcd_Write_Data(0x0C);
  Lcd_Write_Data(0x0C);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x33);
  Lcd_Write_Data(0x33);

  Lcd_Write_Com(0xB7);
  Lcd_Write_Data(0x35);

  Lcd_Write_Com(0xBB);
  Lcd_Write_Data(0x17);

  Lcd_Write_Com(0xC0);
  Lcd_Write_Data(0x2C);

  Lcd_Write_Com(0xC2);
  Lcd_Write_Data(0x01);

  Lcd_Write_Com(0xC3);
  Lcd_Write_Data(0x12);

  Lcd_Write_Com(0xC4);
  Lcd_Write_Data(0x20);

  Lcd_Write_Com(0xC6);
  Lcd_Write_Data(0x0F);

  Lcd_Write_Com(0xD0);
  Lcd_Write_Data(0xA4);
  Lcd_Write_Data(0xA1);

  Lcd_Write_Com(0xE0);
  Lcd_Write_Data(0xD0);
  Lcd_Write_Data(0x04);
  Lcd_Write_Data(0x0D);
  Lcd_Write_Data(0x11);
  Lcd_Write_Data(0x13);
  Lcd_Write_Data(0x2B);
  Lcd_Write_Data(0x3F);
  Lcd_Write_Data(0x54);
  Lcd_Write_Data(0x4C);
  Lcd_Write_Data(0x18);
  Lcd_Write_Data(0x0D);
  Lcd_Write_Data(0x0B);
  Lcd_Write_Data(0x1F);
  Lcd_Write_Data(0x23);

  Lcd_Write_Com(0xE1);
  Lcd_Write_Data(0xD0);
  Lcd_Write_Data(0x04);
  Lcd_Write_Data(0x0C);
  Lcd_Write_Data(0x11);
  Lcd_Write_Data(0x13);
  Lcd_Write_Data(0x2C);
  Lcd_Write_Data(0x3F);
  Lcd_Write_Data(0x44);
  Lcd_Write_Data(0x51);
  Lcd_Write_Data(0x2F);
  Lcd_Write_Data(0x1F);
  Lcd_Write_Data(0x1F);
  Lcd_Write_Data(0x20);
  Lcd_Write_Data(0x23);

  Lcd_Write_Com(0x21);

  Lcd_Write_Com(0x11);
  //Delay (120);

  Lcd_Write_Com(0x29);
  digitalWrite(CS, HIGH);
}

///////////////////////////////////
/////////drawing functions/////////
///////////////////////////////////

void draw_image(int x, int y, int width, int height, byte image_array[]) {
  // draw an image
  digitalWrite(CS, LOW);
  Address_set(x, y, x + width - 1, y + height - 1);
  for (int i = 0; i < (width * height * 2); i++) {
    //Lcd_Write_Data(gImage_shifter_digit_R_24x28px[i]);  // not PROGMEM
    Lcd_Write_Data(pgm_read_byte_near(image_array + i)); // PROGMEM

  }
  digitalWrite(CS, HIGH);
  // end draw an image
}

void Fill_Rect(unsigned int sx, unsigned int sy, unsigned int w, unsigned int h, unsigned int color)
{
  unsigned int i, m;
  unsigned int ex = w + sx - 1;
  unsigned int ey = h + sy - 1;
  digitalWrite(CS, LOW);
  Address_set(sx, sy, ex, ey);
  for (i = 0; i < w; i++)
    for (m = 0; m < h; m++)
    {
      Lcd_Write_Data(color >> 8);
      Lcd_Write_Data(color);
    }
  digitalWrite(CS, HIGH);
}

void LCD_Clear(unsigned int j)
{
  unsigned int i, m;
  digitalWrite(CS, LOW);
  Address_set(0, 0, 239, 197);
  for (i = 0; i < 198; i++)
    for (m = 0; m < 240; m++)
    {
      Lcd_Write_Data(j >> 8);
      Lcd_Write_Data(j);
    }
  digitalWrite(CS, HIGH);
}

void draw_image_tinted(int x, int y, int width, int height, byte image_array[], unsigned int tint) {
  // draw an image
  digitalWrite(CS, LOW);
  Address_set(x, y, x + width - 1, y + height - 1);
  for (int i = 0; i < (width * height); i++) {
    //Lcd_Write_Data(gImage_shifter_digit_R_24x28px[i]);  // not PROGMEM

    Lcd_Write_Data(pgm_read_byte_near(image_array + i * 2) & highByte(tint)); // PROGMEM
    Lcd_Write_Data(pgm_read_byte_near(image_array + i * 2 + 1) & lowByte(tint)); // PROGMEM

    //Lcd_Write_Data(pgm_read_byte_near(image_array + i * 2) & (B11111000)); // PROGMEM
    //Lcd_Write_Data(pgm_read_byte_near(image_array + i * 2 + 1) & (B00000000)); // PROGMEM

  }
  digitalWrite(CS, HIGH);
  // end draw an image
}

//////////////////////////////////////
///////////color definitions//////////
//////////////////////////////////////

unsigned int color_dark_gray = 0x8410; //    Red    ⏐    Green    ⏐   Blue - 1 0 0 0 0 ⏐ 1 0 0 0 0 0 ⏐ 1 0 0 0 0
unsigned int color_light_gray = 0xc618; //    Red    ⏐    Green    ⏐   Blue - 1 1 0 0 0 ⏐ 1 1 0 0 0 0 ⏐ 1 1 0 0 0
unsigned int color_red = 0xf800; // 1 1 1 1 1 ⏐ 0 0 0 0 0 0 ⏐ 0 0 0 0 0
unsigned int color_light_blue = 0x841f; // 1 0 0 0 0 ⏐ 1 0 0 0 0 0 ⏐ 1 1 1 1 1
unsigned int color_blue_gray = 0x8418; //
unsigned int color_dark_blue = 0x01f0; //

// those two colors are used to draw everything
unsigned int color_active;
unsigned int color_inactive;

byte color_theme = 5;     //sets color theme



//setup
int gear_previous = 0;
int gear_current = 1;

void setup() {
  // put your setup code here, to run once:
  SPI_Init();
 
 
  //input pin set up
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);
  
  
  //output pin setup
  pinMode(A0, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A2, OUTPUT);

  digitalWrite(A0, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A2, HIGH);
  
 
  Lcd_Init();
  Serial.begin(115200);

  //Draw defualt screen (neutral)
  LCD_Clear(0x0000); // fill fullscreen with BLACK

  color_active = color_red;
  color_inactive = color_light_gray;

  // first screen redraw
  // images logo on the back - M symbol
  draw_image( 55,  99, 123, 47, gImage_shifter_logo_M_123x47px);

  // connecting lines + DIGITS

  // R
  Fill_Rect( 40, 85, 4, 37, color_inactive);
  Fill_Rect( 44, 118, 25, 4, color_inactive);   // going over the image
  draw_image_tinted( 30,  52, 24, 28, gImage_shifter_digit_R_24x28px, color_inactive);

  // 1
  Fill_Rect( 92, 85, 4, 14, color_inactive);
  draw_image_tinted( 82,  52, 24, 28, gImage_shifter_digit_1_24x28px, color_inactive);

  // 2
  Fill_Rect( 92, 146, 4, 9, color_inactive);
  draw_image_tinted( 82, 160, 24, 28, gImage_shifter_digit_2_24x28px, color_inactive);

  // 3
  Fill_Rect( 144, 85, 4, 14, color_inactive);
  draw_image_tinted(134,  52, 24, 28, gImage_shifter_digit_3_24x28px, color_inactive);

  // 4
  Fill_Rect( 144, 146, 4, 9, color_inactive);
  draw_image_tinted(134, 160, 24, 28, gImage_shifter_digit_4_24x28px, color_inactive);

  // 5
  Fill_Rect( 196, 85, 4, 37, color_inactive);
  Fill_Rect( 178, 118, 18, 4, color_inactive);
  draw_image_tinted(186,  52, 24, 28, gImage_shifter_digit_5_24x28px, color_inactive);

}

void loop() {
  // put your main code here, to run repeatedly:

  //hall value initialization
  int hall_value_0 = analogRead(A8); 
  int hall_value_1 = analogRead(A9); 
  int hall_value_2 = analogRead(A10); 
  int hall_value_3 = analogRead(A11); 
  int hall_value_4 = analogRead(A12); 
  int hall_value_5 = analogRead(A13); 

// convert hall value to range 0-100%
  int percentage_value_8 = round(abs(hall_value_0 - 512) / 5.12);    //reverse
  int percentage_value_9 = round(abs(hall_value_1 - 512) / 5.12);    // 1st
  int percentage_value_10 = round(abs(hall_value_2 - 512) / 5.12);   // 3rd
  int percentage_value_11 = round(abs(hall_value_3 - 512) / 5.12);   // 5th 
  int percentage_value_12 = round(abs(hall_value_4 - 512) / 5.12);   // 2nd
  int percentage_value_13 = round(abs(hall_value_5 - 512) / 5.12);   // 4th

  // calculate the current gear
  // hall sensors are arranged like this
  //
  // A8    A9   A10    A11
  // R     1     3     5
  // |    │     │     │
  // ├────├─────┼─────┘
  //      │     │     
  //      2     4     
  //   A12       A13

if (percentage_value_8 > 30 && percentage_value_9 < 70){
  gear_current = -1; //reverse
}

else if ((percentage_value_9 > 25) && (percentage_value_10 < 50) && (percentage_value_8 < 70)){
  gear_current = 1; // 1st 
}

else if ((percentage_value_10 > 40) && (percentage_value_9 < 70) && (percentage_value_11 < 80)){
  gear_current = 3; // 3rd
}

else if (percentage_value_11 > 20 && percentage_value_10 < 80){
  gear_current = 5; // 5th
}

else if (percentage_value_12 > 40 && percentage_value_13 < 45){
  gear_current = 4; // 2nd
}

else if (percentage_value_13 > 35){
  gear_current = 2; // 4th
}

else {
  gear_current = 0; // Neutral
}

////////////////////////////////////////
//// gear change animation /////////////
////////////////////////////////////////

 if (gear_current != gear_previous) { // show a different gear

    // FADE THE PREVIOUS DIGIT
    if (gear_previous == -1) { // reverse
      Fill_Rect( 40, 85, 4, 37, color_inactive);
      Fill_Rect( 44, 118, 25, 4, color_inactive);   // going over the image
      draw_image_tinted( 30,  52, 24, 28, gImage_shifter_digit_R_24x28px, color_inactive);
    }
    else if (gear_previous == 0) { // neutral
      // add this                                         //did i say add this? dont think its needed
    }
    else if (gear_previous == 1) { // 1st
      Fill_Rect( 92, 85, 4, 14, color_inactive);
      draw_image_tinted( 82,  52, 24, 28, gImage_shifter_digit_1_24x28px, color_inactive);
    }
    else if (gear_previous == 2) { // 2nd
      Fill_Rect( 92, 146, 4, 9, color_inactive);
      draw_image_tinted( 82, 160, 24, 28, gImage_shifter_digit_2_24x28px, color_inactive);
    }
    else if (gear_previous == 3) { // 3rd
      Fill_Rect( 144, 85, 4, 14, color_inactive);
      draw_image_tinted(134,  52, 24, 28, gImage_shifter_digit_3_24x28px, color_inactive);
    }
    else if (gear_previous == 4) { // 4th
      Fill_Rect( 144, 146, 4, 9, color_inactive);
      draw_image_tinted(134, 160, 24, 28, gImage_shifter_digit_4_24x28px, color_inactive);
    }
    else if (gear_previous == 5) { // 5th
      Fill_Rect( 196, 85, 4, 37, color_inactive);
      Fill_Rect( 178, 118, 18, 4, color_inactive);
      draw_image_tinted(186,  52, 24, 28, gImage_shifter_digit_5_24x28px, color_inactive);
    }
    }


    // new gear
    if (gear_current == -1) { // reverse
      Fill_Rect( 40, 85, 4, 37, color_active);
      Fill_Rect( 44, 118, 25, 4, color_active);   // going over the image
      //draw_image( 30,  52, 24, 28, gImage_shifter_digit_R_24x28px);
      draw_image_tinted( 30,  52, 24, 28, gImage_shifter_digit_R_24x28px, color_active);
    }
    else if (gear_current == 0) { // neutral
    }
    else if (gear_current == 1) { // 1st
      Fill_Rect( 92, 85, 4, 14, color_active);
      //draw_image( 82,  52, 24, 28, gImage_shifter_digit_1_24x28px);
      draw_image_tinted( 82,  52, 24, 28, gImage_shifter_digit_1_24x28px, color_active);
    }
    else if (gear_current == 2) { // 2nd
      Fill_Rect( 92, 146, 4, 9, color_active);
      //draw_image( 82, 160, 24, 28, gImage_shifter_digit_2_24x28px);
      draw_image_tinted( 82, 160, 24, 28, gImage_shifter_digit_2_24x28px, color_active);
    }
    else if (gear_current == 3) { // 3rd
      Fill_Rect( 144, 85, 4, 14, color_active);
      //draw_image(134,  52, 24, 28, gImage_shifter_digit_3_24x28px);
      draw_image_tinted(134,  52, 24, 28, gImage_shifter_digit_3_24x28px, color_active);
    }
    else if (gear_current == 4) { // 4th
      Fill_Rect( 144, 146, 4, 9, color_active);
      //draw_image(134, 160, 24, 28, gImage_shifter_digit_4_24x28px);
      draw_image_tinted(134, 160, 24, 28, gImage_shifter_digit_4_24x28px, color_active);
    }
    else if (gear_current == 5) { // 5th
      Fill_Rect( 196, 85, 4, 37, color_active);
      Fill_Rect( 178, 118, 18, 4, color_active);
      //draw_image(186,  52, 24, 28, gImage_shifter_digit_5_24x28px);
      draw_image_tinted(186,  52, 24, 28, gImage_shifter_digit_5_24x28px, color_active);
    }
    
    gear_previous = gear_current;




//changes color theme
  if (color_theme == 0) { // red on gray
    color_active = color_red;
    color_inactive = color_dark_gray;
  } else if (color_theme == 1) { // white on blue
    color_active = 0xFFFF;
    color_inactive = color_dark_blue; // red on blue
  } else if (color_theme == 2) {
    color_active = color_red;
    color_inactive = color_dark_blue;
  } else if (color_theme == 3) { // white on gray
    color_active = 0xFFFF;
    color_inactive = color_dark_gray;
  } else if (color_theme == 4) { // red on blue
    color_active = color_red;
    color_inactive = color_dark_blue;
  } else if (color_theme == 5) { // red on white
    color_active = color_red;
    color_inactive = color_light_gray;
  }



/////////////////////////////
//////////debug info/////////
/////////////////////////////

  //Serial.println(gear_current);
  //Serial.println(percentage_value_8);
  //Serial.println(percentage_value_9);
  Serial.println(percentage_value_10);
  //Serial.println(percentage_value_11);
  //Serial.println(percentage_value_12);
  //Serial.println(percentage_value_13);
  //Serial.println(", 0, 512, 1023");

  delay(150);
}
