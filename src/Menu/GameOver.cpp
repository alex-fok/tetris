#include <functional>
#include "GameOver.hpp"
#include "algorithm"
#include "iostream"

#define ButtonCount 2

Menu::GameOver::GameOver(sf::RenderWindow *w, std::function<void()> retryFn, std::function<void()> quitFn) :
    Base(w),
    m_retryFn(retryFn),
    m_quitFn(quitFn)
{
    m_width = GameUI::Config::Menu::GameOver::Width;
    m_height = GameUI::Config::Menu::GameOver::Height;
    
    m_setup(m_width, m_height, "Game Over");
    // Retry button
    Utils::Button *retry = new Utils::Button("Retry (R)", fontCollection);
    
    retry->setClickFn(retryFn);
    retry->setHoverFn(std::bind(forwarder_setSelected, this, 0));
    
    // Quit button
    Utils::Button *quit = new Utils::Button("Quit (Q)", fontCollection);
    quit->setClickFn(quitFn);
    quit->setHoverFn(std::bind(forwarder_setSelected, this, 1));

    Utils::Drawable **arr = new Utils::Drawable *[ButtonCount]{retry, quit};
    setDrawables(arr, ButtonCount);

    setListPositions(arr, ButtonCount, m_container.getPosition().x, m_offset.top, 5.f);
    setSelectedIdx(0);
}

void Menu::GameOver::handle(sf::Keyboard::Key input)
{
    switch(input)
    {
        case sf::Keyboard::R:
            m_retryFn();
            break;
        case sf::Keyboard::Q:
            m_quitFn();
            break;
        default:
            Base::handle(input);
            break;
    }
}

void Menu::GameOver::onClose()
{
}
