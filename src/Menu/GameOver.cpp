#include <iostream>
#include "GameOver.hpp"

Menu::GameOver::GameOver(sf::RenderWindow *w):
    Base(w, {s_Width, s_Height}, "Game Over")
{
}

void Menu::GameOver::render()
{
    renderBase();
}
