#include "CegleApp.h"

/* TODO: Make try : catch + exceptions inside the code, instead of returns of ints and bools */
int main() {
    CegleApp app("127.0.0.1", 8080);

    app.run();

    return 0;
}