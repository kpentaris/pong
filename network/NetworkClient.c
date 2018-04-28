//
// @author kpentaris - 16/4/2018.
//

#include <stdbool.h>
#include <stdio.h>
#include "NetworkClient.h"
#include "SDL_net.h"

static bool keep_waiting = false;
static TCPsocket host;
static TCPsocket client;
static SDL_Thread *network_thread;

void close_network_communication() ;

void init_network_operations() {
  SDLNet_Init();
}

// must run in a different thread...
int await_for_incoming_connection(void *data) {
  printf("Waiting for player to join game...");
  IPaddress ip;
  SDLNet_ResolveHost(&ip, NULL, MULTIPLAYER_PORT);
  host = SDLNet_TCP_Open(&ip);
  client;
  keep_waiting = true;
  while (keep_waiting) {
    printf("\nAwaiting for client to connect...");
    client = SDLNet_TCP_Accept(host);
    if (client) {
      // TODO send confirmation message
      SDLNet_TCP_Send(client, "CONNECTED", 9);
      break;
    }
    SDL_Delay(2000);
  }
  close_network_communication();
  return 111;
}

SDL_Thread* start_awaiting_for_someone_to_connect() {
  network_thread = SDL_CreateThread(await_for_incoming_connection, "Multiplayer Host Thread", NULL);
  if (network_thread == NULL) {
    fprintf(stderr, "Failed to create SDL network thread with error: %s\n", SDL_GetError());
  }
  return network_thread;
}

void stop_awaiting() {
  keep_waiting = false;
}

void close_network_communication() {
  printf("Closing network communication");
  SDLNet_TCP_Close(host);
  SDLNet_TCP_Close(client);
  SDL_DetachThread(network_thread);
}

void stop_network_operations() {
  SDLNet_Quit();
}