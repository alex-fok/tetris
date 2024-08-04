#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "GameUI/UI.hpp"

int main(int, char**)
{
    GameUI::UI ui;
    ui.run();
    return 0;
}
