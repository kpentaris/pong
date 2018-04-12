//
// @author kpentaris - 6/4/2018.
//
#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include "GameLoop.h"
#include "Input.h"
#include "../paddle/Paddle.h"

extern Paddle left_paddle;
extern Paddle right_paddle;
extern Ball game_ball;
extern short BALL_MAX_ACCELERATION;

static void render_frame(SDL_Renderer *);

static void update_objects();

static bool round_started = false;

void start_game(SDL_Window *window, SDL_Renderer *renderer) {
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    // TODO Ask SO about use case and if using SDL events was better
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    if (keyboardState[SDL_SCANCODE_UP] && keyboardState[SDL_SCANCODE_DOWN]) {
      handle_no_key();
    } else if (keyboardState[SDL_SCANCODE_DOWN]) {
      handle_keydown(SDL_SCANCODE_DOWN);
    } else if (keyboardState[SDL_SCANCODE_UP]) {
      handle_keydown(SDL_SCANCODE_UP);
    } else {
      handle_no_key();
    }

    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_KEYDOWN:
          if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
            if (!round_started) {
              increase_ball_velocity(&game_ball, BALL_MAX_ACCELERATION);
              round_started = true;
            }
          }
          break;
        default: {
        }
      }
    }
    update_objects();
    render_frame(renderer);
  }
  SDL_DestroyWindow(window);
  SDL_Quit();
}

static void update_objects() {
  update_paddle_position(&left_paddle);
  update_paddle_position(&right_paddle);
  update_ball_position(&game_ball);
}

static void render_frame(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // white for paddles & ball

  SDL_Rect left_paddle_rect;
  left_paddle_rect.h = left_paddle.height;
  left_paddle_rect.w = left_paddle.width;
  left_paddle_rect.y = left_paddle.y_pos;
  left_paddle_rect.x = left_paddle.x_pos;

  SDL_RenderDrawRect(renderer, &left_paddle_rect);
  SDL_RenderFillRect(renderer, &left_paddle_rect);

  SDL_Rect right_paddle_rect;
  right_paddle_rect.h = right_paddle.height;
  right_paddle_rect.w = right_paddle.width;
  right_paddle_rect.y = right_paddle.y_pos;
  right_paddle_rect.x = right_paddle.x_pos;

  SDL_RenderDrawRect(renderer, &right_paddle_rect);
  SDL_RenderFillRect(renderer, &right_paddle_rect);

  SDL_Rect ball_rect;
  ball_rect.y = game_ball.y_pos;
  ball_rect.x = game_ball.x_pos;
  ball_rect.h = game_ball.radius * 2;
  ball_rect.w = game_ball.radius * 2;

  SDL_RenderDrawRect(renderer, &ball_rect);
  SDL_RenderFillRect(renderer, &ball_rect);

  SDL_RenderPresent(renderer);
}