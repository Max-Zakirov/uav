#include "UDPServer.h"

/* TODO: Make try : catch + exceptions inside the code, instead of returns of ints and bools */
int main() {
    UDPServer server(8080);

    server.serveForever();

    return 0;
}