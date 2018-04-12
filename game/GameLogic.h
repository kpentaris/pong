//
// @author kpentaris - 12/4/2018.
//

#ifndef PONG_GAMELOGIC_H
#define PONG_GAMELOGIC_H

#include "../paddle/Paddle.h"

void check_ball_to_paddle_collision(Ball *ball, Paddle *left_paddle, Paddle *right_paddle);
void correct_ball_position(Ball *ball);
void correct_paddle_position(Paddle *paddle);
bool check_for_goal(Ball *ball);
#endif //PONG_GAMELOGIC_H
