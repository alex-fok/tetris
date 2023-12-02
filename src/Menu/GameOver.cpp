#include <iostream>
#include <functional>
#include "GameOver.hpp"

Menu::GameOver::GameOver(sf::RenderWindow *w) :
    Base(w)
{
    width = GameUI::Config::Menu::GameOver::Width;
    height = GameUI::Config::Menu::GameOver::Height;
    
    setup(width, height, "Game Over");
    // Retry button
    Utils::Button *retry = new Utils::Button("Retry", fontCollection);
    retry->setFn(std::bind(this->forwarder_retry, this));

    m_clickables.push_back(retry);
    
    setButtonPositions();
}

void Menu::GameOver::retry()
{
    std::cout << "Attempting to retry" << std::endl;
}

void Menu::GameOver::forwarder_retry(Menu::GameOver *self)
{
    self->retry();
}

void Menu::GameOver::render()
{
    renderBase();
    for (Utils::Clickable *c: m_clickables)
    {
        draw(c->getClickable());
    }
}
