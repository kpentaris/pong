//
// @author kpentaris - 1/4/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../main.h"
#include "Paddle.h"

extern float BALL_MINIMAL_DEGREE_OFFSET;
extern float BALL_SMALL_DEGREE_OFFSET;
extern float BALL_MEDIUM_DEGREE_OFFSET;
extern float BALL_LARGE_DEGREE_OFFSET;

extern short BALL_MAX_DECELERATION;
extern short BALL_MIN_DECELERATION;
extern short BALL_MIN_ACCELERATION;
extern short BALL_MAX_ACCELERATION;

Paddle left_paddle;
Paddle right_paddle;

static float randomize_angle(float angle);

/**
 * Initializes the global paddle values with the defaults.
 */
void init_paddles() {
  left_paddle.y_pos = 100;
  left_paddle.x_pos = 20;
  left_paddle.velocity = 0;
  left_paddle.type = LEFT_PADDLE;
  left_paddle.color_code = "FFFFFF";
  left_paddle.height = PADDLE_HEIGHT;
  left_paddle.width = PADDLE_WIDTH;

  right_paddle.velocity = 0;
  right_paddle.type = RIGHT_PADDLE;
  right_paddle.color_code = "FFFFFF";
  right_paddle.height = PADDLE_HEIGHT;
  right_paddle.width = PADDLE_WIDTH;
  right_paddle.y_pos = WINDOW_HEIGHT - 100 - right_paddle.height;
  right_paddle.x_pos = WINDOW_WIDTH - 20 - right_paddle.width;
}

short hit_ball(Paddle *paddle, Ball *ball, float paddle_offset_pct /* between 0 and 1 */) {
  if (!ball) {
    fprintf(stderr, "Provided ball reference is null");
    goto error;
  }

  float new_angle;
  short ball_acceleration;
  float abs_paddle_offset_pct = fabsf(paddle_offset_pct);
  if (abs_paddle_offset_pct < 0.11) {
    new_angle = randomize_angle(BALL_MINIMAL_DEGREE_OFFSET);
    ball_acceleration = BALL_MAX_DECELERATION;
  } else if (abs_paddle_offset_pct < 0.33) {
    new_angle = randomize_angle(BALL_SMALL_DEGREE_OFFSET);
    ball_acceleration = BALL_MIN_DECELERATION;
  } else if (abs_paddle_offset_pct < 0.66) {
    new_angle = randomize_angle(BALL_MEDIUM_DEGREE_OFFSET);
    ball_acceleration = BALL_MIN_ACCELERATION;
  } else {
    new_angle = randomize_angle(BALL_LARGE_DEGREE_OFFSET);
    ball_acceleration = BALL_MAX_ACCELERATION;
  }

  if (ball->direction > 180) { // ball comes in a downward angle
    new_angle = 360 - new_angle;
  }

  // normalize degree according to positive or negative direction
  if (paddle->type == RIGHT_PADDLE) {
    if (new_angle <= 90) {
      new_angle = 180 - new_angle;
    } else if (new_angle >= 270) {
      new_angle = 540 - new_angle; // 360 + 180 - angle
    }
    ball->x_pos = paddle->x_pos - ball->radius - 1;  // TODO MAKE BETTER
  } else {
    ball->x_pos = paddle->x_pos + paddle->width + 1; // TODO MAKE BETTER
  }

  change_ball_direction(ball, new_angle);
  increase_ball_velocity(ball, ball_acceleration);

  return EXIT_SUCCESS;

  error:
  return EXIT_FAILURE;
}

/**
 * To be called on each frame.
 * If the paddle has a velocity, then its position must change by the same amount.
 * If no velocity is present then the position will remain unchanged.
 *
 * @param paddle
 */
void update_paddle_position(Paddle *paddle) {
  paddle->y_pos += paddle->velocity;
}

/**
 * Set the velocity of the paddle to the predefined amount.
 * Since Y coordinates are reverted in SDL windows, for the sake of consistency the
 * convention is that moving upwards has negative speed and vice versa.
 *
 * Possible replacement candidate in case we want to support different paddle speeds.
 *
 * @param paddle
 * @param direction
 * @return
 */
short start_moving_paddle(Paddle *paddle, PaddleDirection direction) {
  if (!paddle) {
    fprintf(stderr, "Attempted to move null paddle");
    goto error;
  }

  paddle->velocity = direction == PADDLE_DIRECTION_UP ? -PADDLE_FRAME_SPEED : PADDLE_FRAME_SPEED;

  error:
  return EXIT_FAILURE;
}

/**
 * Sets the velocity of the paddle to 0.
 *
 * @param paddle
 * @return
 */
short stop_moving_paddle(Paddle *paddle) {
  if (!paddle) {
    fprintf(stderr, "Attempted to move null paddle");
    goto error;
  }

  paddle->velocity = 0;

  error:
  return EXIT_FAILURE;
}

static float randomize_angle(float angle) {
  angle += (rand() % 5 + 1) * (rand() % 2 == 0 ? -1 : 1);
  return angle;
}