#include <iostream>
#include <functional>
#include "GameOver.hpp"

Menu::GameOver::GameOver(sf::RenderWindow *w, std::function<void()> retryFn) :
    Base(w),
    m_resetFn(retryFn)
{
    width = GameUI::Config::Menu::GameOver::Width;
    height = GameUI::Config::Menu::GameOver::Height;
    
    setup(width, height, "Game Over");
    // Retry button
    Utils::Button *retry = new Utils::Button("Retry", fontCollection);
    retry->setFn(retryFn);

    m_clickables.push_back(retry);

    setButtonPositions();
}

void Menu::GameOver::render()
{
    renderBase();
    for (Utils::Clickable *c: m_clickables)
    {
        draw(c->getClickable());
    }
}
