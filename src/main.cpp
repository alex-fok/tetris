#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(__MINGW32__)
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "GameUI/UI.hpp"

int main(int, char**)
{
    // const char *ENVIRONMENT = std::getenv("ENVIRONMENT");
    // _putenv_s("ASSET_PATH", std::strcmp("DEBUG", ENVIRONMENT) == 0 ? "../../assets/" : "../assets/");

    GameUI::UI ui;
    ui.run();
    return 0;
}
