#ifndef __CONSTANTS__
#define SCREEN_HEIGHT 8
#define SCREEN_WIDTH 8
#define MAX_BRICK_ROWS 5
#define PAD_SPEED 10
#define REFRESH_RATE 20
#endif
class Breakout{
  // this is an implementation of the Breakout game on an 8x8 led screen
public:
  Breakout();
  uint8_t* get_screen(); // Return an 8x8 binary matrix of the screen
  int get_score();      // Return the score of the game
  void move_pad(int v); // Sets the pad_velocity to the given velocity v
  void start();
  bool is_over();
  int lives_left();
  void refresh(unsigned long int);
};
