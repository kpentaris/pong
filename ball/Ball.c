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
short BALL_MIN_VELOCITY = 2;
short BALL_MAX_VELOCITY = 10;

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
  if (ball->velocity <= BALL_MIN_VELOCITY) {
    ball->velocity = BALL_MIN_VELOCITY;
  } else if (ball->velocity > BALL_MAX_VELOCITY) {
    ball->velocity = BALL_MAX_VELOCITY;
  }
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

void update_ball_position(Ball *ball) {
  // PI * 2 / 360 = 0.01745. sin(radians)
  ball->y_pos += sin(ball->direction * 0.01745) * ball->velocity;
  ball->x_pos += cos(ball->direction * 0.01745) * ball->velocity;
}

// TODO Maybe implement ball wall bounce