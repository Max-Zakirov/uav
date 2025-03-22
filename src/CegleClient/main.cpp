#include "CegleApp.h"

/* TODO: Make try : catch + exceptions inside the code, instead of returns of ints and bools */
int main() {
    CegleApp app("192.168.3.1", 8080);

    app.run();

    return 0;
}