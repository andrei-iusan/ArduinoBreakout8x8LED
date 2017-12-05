#ifndef __CONSTANTS__
#define SCREEN_HEIGHT 8
#define SCREEN_WIDTH 8
#define MAX_BRICK_ROWS 5
#define PAD_SPEED 10
#define REFRESH_RATE 20
#endif
#include <stdint.h>
#include <math.h>

class Breakout{
public:
  Breakout();
  uint8_t* get_screen(); // Return an 8x8 binary matrix of the screen
  int get_score();      // Return the score of the game
  void move_pad(int v); // Sets the pad_velocity to the given velocity v
  void start();
  bool is_over();
  int lives_left();
  void refresh(unsigned long int);
private:
  unsigned long prev_time;
  struct Ball{
    float x,y,vx,vy; // x and y position and velocity
    bool glued; // if glued==true, the position of the ball will be set to
                // the pad position, and the velocity to 0.
  };
  Ball ball;
  struct Pad{
    const int y=7; // y position fixed to the last row.
    int size;
    float x,v; // dimension, x-coordinate and velocity
  };
  Pad pad;
  int lives;
  int score;
  int width, height;
  uint8_t screen[SCREEN_HEIGHT];
  uint8_t bricks[MAX_BRICK_ROWS];
  int number_of_bricks;
  void generate_screen();
  void reset_position(); // set pad and ball to start-of-game position
  int round(float x);
  void update_pad(unsigned int);
  void update_ball(unsigned int);

};

Breakout::Breakout(){
  score = 0;
  lives = 3;
  bricks[0] = 0x00;
  number_of_bricks = 24;
  bricks[MAX_BRICK_ROWS-1] = 0x00;
  for(int i=1;i<MAX_BRICK_ROWS;i++){
    bricks[i] = 0xFF;
  }

  pad.size=3;
  reset_position(); // set pad and ball to start-of-game position
}

uint8_t* Breakout::get_screen() // Return an 8x8 binary matrix of the screen
{
  uint8_t screen[8];

  // clear the screen
  for(int i=0;i<8;i++){
    screen[i] = 0;
  }

  // draw bricks
  for(int row=0;row<MAX_BRICK_ROWS;row++){
    screen[row] = bricks[row];
  }

  //draw ball
  screen[round(ball.y)] |= 1 << SCREEN_WIDTH-round(ball.x);
   // ball.y is a float, I round it to int, and update the screen's column:
   // screen[ball_y], then I update the x coord by shifting a bit to x coord and using an "or"

   //draw pad
   for (int i=0;i<pad.size;i++)
   {
     screen[pad.y] |= 1 << SCREEN_WIDTH-round(pad.x)-i;
   }

   return screen;
}

int Breakout::get_score()     // Return the score of the game
{
  return score;
}

void Breakout::move_pad(int v) // Sets the pad_velocity to the given velocity v
{
  pad.v=v;
}

void Breakout::start()
{
  ball.glued=false;
  ball.vx=1;
  ball.vy=-2; // TODO: change to random
}

bool Breakout::is_over()
{
  return ( !number_of_bricks || !lives);
}

int Breakout::lives_left()
{
  return lives;
}

void Breakout::refresh(unsigned long tm){
  unsigned int dt = tm - prev_time;
  update_pad(dt);
  update_ball(dt);

}

void Breakout::update_pad(unsigned int dt){
  //update position
  pad.x += 0.001 * dt * pad.v;
  if ( pad.x < 0 ) pad.x = 0;
  if ( pad.x > SCREEN_WIDTH - pad.size) pad.x = SCREEN_WIDTH - pad.size;
  if ( ball.glued ){
    ball.x=pad.x;
    ball.y=pad.y+1;
    ball.vx=0;
    ball.vy=0;
  }
}

void Breakout::update_ball(unsigned int dt){
  //update position
  ball.x += 0.001 * dt * ball.vx;
  if ( ball.x < 0 ) ball.x *= -1;
  if ( ball.y < 0 ) ball.y *= -1;
  if ( ball.x > SCREEN_WIDTH -1) ball.x = 2*SCREEN_WIDTH - ball.x;
  if ( ball.y > SCREEN_WIDTH -1) { // lost the ball
    lives-=1;
    if (!lives){
      //TODO: print game over, score, bla bla
    }
    else{
      reset_position();
    }
  }
  //TODO: check for colision

}

void Breakout::reset_position(){
  pad.x = (width-pad.size)/2;
  pad.v = 0;
  ball.glued = true;
  ball.x = pad.x + pad.size/2;
  ball.y = pad.y - 1;
}

int Breakout::round(float x){
  return floor(x + 0.5);
}
