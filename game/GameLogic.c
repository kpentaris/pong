//
// @author kpentaris - 12/4/2018.
//

#include <stdbool.h>
#include "GameLogic.h"
#include "../paddle/Paddle.h"
#include "../main.h"
#include "../utils/MathUtils.h"

void check_ball_to_paddle_collision(Ball *ball, Paddle *left_paddle, Paddle *right_paddle) {
  const short blx = ball->x_pos; // ball left x
  const short brx = ball->x_pos + ball->radius * 2; // ball right x
  const short bty = ball->y_pos; // ball top y
  const short bby = ball->y_pos + ball->radius * 2; // ball bottom y
  const short lplx = left_paddle->x_pos;
  const short lprx = left_paddle->x_pos + left_paddle->width;
  const short lpty = left_paddle->y_pos;
  const short lpby = left_paddle->y_pos + left_paddle->height;
  const short rplx = right_paddle->x_pos;
  const short rprx = right_paddle->x_pos + right_paddle->width;
  const short rpty = right_paddle->y_pos;
  const short rpby = right_paddle->y_pos + right_paddle->height;

  if (blx <= lprx && brx >= lplx &&
      bby >= lpty && bty <= lpby) {
    hit_ball(left_paddle, ball, 0.5);
  }

  if (brx >= rplx && blx <= rprx &&
      bby <= rpty && bty >= rpby) {
    hit_ball(right_paddle, ball, 0.5);
  }
}

/**
 * Corrects the position of the ball in case it is about to go off-screen.
 *
 * @param ball
 */
void correct_ball_position(Ball *ball) {
  if (ball->y_pos - BALL_RADIUS < 0 || ball->y_pos + BALL_RADIUS > WINDOW_HEIGHT) {
    change_ball_direction(ball, find_symmetrical_angle(ball->direction, false));
    ball->y_pos = ball->y_pos - BALL_RADIUS < 0 ? BALL_RADIUS : WINDOW_HEIGHT - BALL_RADIUS;
  }
  // both cases must be evaluated in case the ball hits the corner (corner case)
}

/**
 * If the paddle's position is off bounds, reset it to exactly the maximum.
 *
 * @param paddle
 */
void correct_paddle_position(Paddle *paddle) {
  if (paddle->y_pos <= 0) {
    paddle->y_pos = 0;
  }

  if (paddle->y_pos >= WINDOW_HEIGHT - paddle->height) {
    paddle->y_pos = WINDOW_HEIGHT - paddle->height;
  }
}

bool check_for_goal(Ball *ball) {
  if (ball->x_pos - BALL_RADIUS < 0 || ball->x_pos + BALL_RADIUS > WINDOW_WIDTH) {
    init_ball(); // one of the parties has lost the round
    return true;
  }
  return false;
}