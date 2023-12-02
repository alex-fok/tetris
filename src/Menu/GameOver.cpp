#include <iostream>
#include "GameOver.hpp"

Menu::GameOver::GameOver(sf::RenderWindow *w) :
    Base(w)
{
    width = GameUI::Config::Menu::GameOver::Width;
    height = GameUI::Config::Menu::GameOver::Height;
    setup(width, height, "Game Over");
    buttonsVector.push_back(new Utils::Button("Retry", fontCollection));
    setButtonPositions(buttonsVector);
}

void Menu::GameOver::retry()
{
    std::cout << "Attempting to retry" << std::endl;
}

void Menu::GameOver::render()
{
    renderBase();
    for (Utils::Button *b: buttonsVector)
    {
        draw(b->content);
    }
}
