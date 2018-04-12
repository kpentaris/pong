//
// @author kpentaris - 1/4/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../main.h"
#include "Ball.h"

float BALL_MINIMAL_DEGREE_OFFSET = 10;
float BALL_SMALL_DEGREE_OFFSET = 30;
float BALL_MEDIUM_DEGREE_OFFSET = 45;
float BALL_LARGE_DEGREE_OFFSET = 60;

short BALL_MAX_DECELERATION = -4; // arbitrary
short BALL_MIN_DECELERATION = -2; // arbitrary
short BALL_MIN_ACCELERATION = 2; // arbitrary
short BALL_MAX_ACCELERATION = 4; // arbitrary

/**
 * Global ball instance. This represents the ball used in the game.
 * Must be accessible from other modules.
 *
 * Note that many of the methods
 * actually take a ball reference as an argument which almost always will
 * be this instance.
 *
 * Possible refactoring where there is no global instance and all methods
 * simple require references.
 */
Ball game_ball;

void init_ball() {
  game_ball.velocity = 0;
  game_ball.direction = rand() % 61;
  if (rand() % 2 == 0) {
    game_ball.direction *= -1;
  }
  if (game_ball.direction % 2 == 0) {
    game_ball.direction += 180;
  }
  if (game_ball.direction < 0) {
    game_ball.direction += 360;
  }
  game_ball.radius = BALL_RADIUS;
  game_ball.y_pos = WINDOW_HEIGHT / 2;
  game_ball.x_pos = WINDOW_WIDTH / 2;
}

short increase_ball_velocity(Ball *ball, short acceleration /*can be negative*/) {
  if (!ball) {
    printf("Provided ball reference is null");
    goto error;
  }

  ball->velocity += acceleration;
  return EXIT_SUCCESS;

  error:
  return EXIT_FAILURE;
}

short change_ball_direction(Ball *ball, float new_direction) {
  if (!ball) {
    printf("Provided ball reference is null");
    goto error;
  }

  ball->direction = new_direction;
  return EXIT_SUCCESS;

  error:
  return EXIT_FAILURE;
}

// TODO Move to utils functions
short find_symmetrical_angle(short angle, bool y_axis_symmetry) {
  short new_angle;
  if (y_axis_symmetry) {
    if (angle < 180) {
      new_angle = (short) (2 * 90 - angle);
    } else {
      new_angle = (short) (2 * 270 - angle);
    }
  } else {
    if (angle < 90 || angle > 270) {
      new_angle = (short) (2 * 360 - angle);
    } else {
      new_angle = (short) (2 * 180 - angle);
    }
  }
  if (new_angle > 360) {
    new_angle -= 360;
  } else if (new_angle < 0) {
    new_angle += 360;
  }
  return new_angle;
}

/**
 * Corrects the position of the ball in case it is about to go off-screen.
 *
 * @param ball
 */
void correct_ball_position(Ball *ball) {
  // Case A: ball is about to go off on the X Axis
  if (ball->x_pos - BALL_RADIUS < 0 || ball->x_pos + BALL_RADIUS > WINDOW_WIDTH) {
    change_ball_direction(ball, find_symmetrical_angle(ball->direction, true));
    ball->x_pos = ball->x_pos - BALL_RADIUS < 0 ? BALL_RADIUS : WINDOW_WIDTH - BALL_RADIUS;
  }
  // Case B: ball is about to go off the Y Axis
  if (ball->y_pos - BALL_RADIUS < 0 || ball->y_pos + BALL_RADIUS > WINDOW_HEIGHT) {
    change_ball_direction(ball, find_symmetrical_angle(ball->direction, false));
    ball->y_pos = ball->y_pos - BALL_RADIUS < 0 ? BALL_RADIUS : WINDOW_HEIGHT - BALL_RADIUS;
  }
  // both cases must be evaluated in case the ball hits the corner (corner case)
}

void update_ball_position(Ball *ball) {
  // PI * 2 / 360 = 0.01745. sin(radians)
  ball->y_pos += sin(ball->direction * 0.01745) * ball->velocity;
  ball->x_pos += cos(ball->direction * 0.01745) * ball->velocity;
  correct_ball_position(ball);
}

// TODO Maybe implement ball wall bounce