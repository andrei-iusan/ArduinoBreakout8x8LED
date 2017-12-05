#include "LedControl.h"
#include "Breakout.h"

#ifndef __CONSTANTS__
#define SCREEN_HEIGHT 8
#define SCREEN_WIDTH 8
#define MAX_BRICK_ROWS 5
#define PAD_SPEED 10
#define REFRESH_RATE 20
#endif

#define ANALOG_MAX_VALUE 1023
// PAD_SPEED: maximum speed of the pad, measured in px/sec
#define PAD_SPEED 16
// REFRESH_RATE in fps
#define REFRESH_RATE 20


LedControl lc=LedControl(12,11,10,1);
Breakout game=Breakout();

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int joystick_x = analogRead(A0);
  float pad_velocity = (joystick_x / ANALOG_MAX_VALUE * 2 - 1)
                      * PAD_SPEED * REFRESH_RATE;
  game.move_pad(pad_velocity);
  game.refresh(millis());
  byte screen[8] = game.screen();
  draw_screen(screen);
}

void draw_screen(int * screen){
  for (row=0;row<8;row++){
    lc.setRow(0,row,screen[row]);
  }
}
