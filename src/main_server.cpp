#include "UDPServer.h"

int main() {
    UDPServer server(8080);
    server.start();
    return 0;
}
