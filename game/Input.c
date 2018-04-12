//
// @author kpentaris - 6/4/2018.
//

#include <SDL.h>
#include "Input.h"
#include "../paddle/Paddle.h"

extern Paddle left_paddle;
extern Paddle right_paddle;

void handle_keydown(SDL_Scancode scancode) {
  switch (scancode) {
    case SDL_SCANCODE_UP:
      start_moving_paddle(&left_paddle, PADDLE_DIRECTION_UP);
      break;
    case SDL_SCANCODE_DOWN:
      start_moving_paddle(&left_paddle, PADDLE_DIRECTION_DOWN);
      break;
    default: {}
  }
}

void handle_keyup(SDL_Scancode scancode) {
  switch (scancode) {
    case SDL_SCANCODE_UP:
    case SDL_SCANCODE_DOWN:
      stop_moving_paddle(&left_paddle);
      break;
    default: {}
  }
}

void handle_no_key() {
  stop_moving_paddle(&left_paddle);
}