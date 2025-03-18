#pragma once

#include "UDPClient.h"
#include "KeyboardManager.h"

class CegleApp {
public:
    CegleApp();
    ~CegleApp();

    void run();

private:
    KeyboardManager keyboardManager;
    UDPClient client;
};