//
// @author kpentaris - 1/4/2018.
//

#include "../ball/Ball.h"

#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

#define PADDLE_FRAME_SPEED (short) 10
#define PADDLE_HEIGHT (short) 100
#define PADDLE_WIDTH (short) 10

typedef enum {LEFT_PADDLE, RIGHT_PADDLE} PaddleType;
typedef enum {PADDLE_DIRECTION_UP, PADDLE_DIRECTION_DOWN} PaddleDirection;

typedef struct Paddle {
  short height;
  short width; // thickness
  short y_pos;
  short x_pos;
  PaddleType type;
  char *color_code; // e.g. FFFFFF - unused
  short velocity; // pixels per second?
} Paddle;

void init_paddles();
short hit_ball(Paddle *paddle, Ball *ball, float paddle_offset_pct);
short start_moving_paddle(Paddle *, PaddleDirection);
short stop_moving_paddle(Paddle *);
void correct_paddle_position(Paddle*);
void update_paddle_position(Paddle *paddle);

#endif //PONG_PADDLE_H