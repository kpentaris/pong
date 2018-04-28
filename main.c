#include <SDL.h>
#include <time.h>
#include <stdlib.h>
#include "game/GameLoop.h"
#include "main.h"
#include "paddle/Paddle.h"
#include "network/NetworkClient.h"
#include <stdio.h>
#include <stdbool.h>

static void seed_randomizer();

int main(int argc, char *argv[]) {
  seed_randomizer();
  init_paddles();
  init_ball();



  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Window *window = SDL_CreateWindow("Pong", 100, 100,
                                        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "Create window error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // adding presentvsync synchronizes the rendering function with the machine framerate to avoid stutter
  // essentially automatically caps the frames to 60/sec
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
    SDL_DestroyWindow(window);
    fprintf(stderr, "Rendering error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  init_network_operations();
  SDL_Thread *thread = start_awaiting_for_someone_to_connect();
  int thread_result;
  for (int i = 0 ; i != 10 ; i++) {
    printf("\nAnimating for awaiting");
    SDL_Delay(1000);
  }
  SDL_WaitThread(thread, &thread_result);
  printf("\nThread result was %d", thread_result);
  stop_network_operations();
//  start_game(window, renderer, true);
  return EXIT_SUCCESS;
}

static void seed_randomizer() {
  srand(time(NULL));
}