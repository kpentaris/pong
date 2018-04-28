//
// @author kpentaris - 16/4/2018.
//

#pragma once

#include <SDL_thread.h>

#define MULTIPLAYER_PORT 6666
void init_network_operations();
void stop_network_operations();
SDL_Thread* start_awaiting_for_someone_to_connect();
void close_network_communication();