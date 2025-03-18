#include "UDPServer.h"

int main() {
    UDPServer server(8080);
    server.run();
    return 0;
}
