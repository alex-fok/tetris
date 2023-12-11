#include <iostream>
#include <functional>
#include "GameOver.hpp"

Menu::GameOver::GameOver(sf::RenderWindow *w, std::function<void()>retryFn, std::function<void()>quitFn) :
    Base(w),
    m_resetFn(retryFn)
{
    m_width = GameUI::Config::Menu::GameOver::Width;
    m_height = GameUI::Config::Menu::GameOver::Height;
    
    m_setup(m_width, m_height, "Game Over");
    // Retry button
    Utils::Button *retry = new Utils::Button("Retry", fontCollection);
    
    retry->setClickFn(retryFn);
    retry->setHoverFn(std::bind(forwarder_setSelected, this, retry));
    
    // Quit button
    Utils::Button *quit = new Utils::Button("Quit", fontCollection);
    quit->setClickFn(quitFn);
    quit->setHoverFn(std::bind(forwarder_setSelected, this, quit));

    m_clickables.push_back(retry);
    m_clickables.push_back(quit);

    m_setButtonPositions();
    setSelected(retry);
}
