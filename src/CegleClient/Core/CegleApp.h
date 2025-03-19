#pragma once

#include "UDPClient.h"
#include "KeyboardManager.h"

class CegleApp {
public:
    CegleApp() = delete;
    CegleApp(const std::string& serverIP, int serverPort);
    
    ~CegleApp() {}

    void run();

private:
    KeyboardManager keyboardManager;
    UDPClient client;
};