//
// @author kpentaris - 6/4/2018.
//

#include <SDL.h>
#include "Input.h"
#include "../paddle/Paddle.h"

extern Paddle left_paddle;
extern Paddle right_paddle;

void handle_keydown(Paddle *paddle, PaddleDirection direction) {
  start_moving_paddle(paddle, direction);
}

void handle_keyup(Paddle *paddle) {
  stop_moving_paddle(paddle);
}

void handle_no_key(Paddle *paddle) {
  stop_moving_paddle(paddle);
}