//
// @author kpentaris - 6/4/2018.
//

#ifndef PONG_INPUT_H
#define PONG_INPUT_H

#include "../paddle/Paddle.h"

void handle_keydown(Paddle *paddle, PaddleDirection direction);
void handle_keyup(Paddle *paddle);
void handle_no_key(Paddle *paddle);

#endif //PONG_INPUT_H
