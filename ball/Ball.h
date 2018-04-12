//
// @author kpentaris - 1/4/2018.
//

#ifndef PONG_BALL_H
#define PONG_BALL_H

#define BALL_RADIUS 5

typedef struct Ball {
  // view related information
  short radius;
  short x_pos;
  short y_pos;

  // usability related information
  short velocity;
  short direction; // in degrees?
} Ball;

void init_ball();

short increase_ball_velocity(Ball *, short);

short change_ball_direction(Ball *, float new_direction);

void update_ball_position(Ball *);

#endif //PONG_BALL_H
