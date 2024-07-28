#include "Start.hpp"
#include <iostream>
#define ButtonCount 2

Menu::Start::Start(sf::RenderWindow *w, std::function<void()> startGameFn, std::function<void()> quitFn) :
    Base(w),
    m_startGameFn(startGameFn),
    m_quitFn(quitFn)
{
    m_width = GameUI::Config::Menu::Start::Width;
    m_height = GameUI::Config::Menu::Start::Height;

    m_setup(m_width, m_height, "Tetris");
    // Start button
    Utils::Button *start = new Utils::Button("Start (Enter)", fontCollection);

    start->setClickFn(m_startGameFn);
    start->setHoverFn(std::bind(forwarder_setSelected, this, 0));

    // Quit button
    Utils::Button *quit = new Utils::Button("Quit (Q)", fontCollection);

    quit->setClickFn(m_quitFn);
    quit->setHoverFn(std::bind(forwarder_setSelected, this, 1));

    Utils::Drawable ** arr = new Utils::Drawable *[ButtonCount]{start, quit};
    setDrawables(arr, ButtonCount);

    setListPositions(arr, ButtonCount, m_container.getPosition().x, m_offset.top, 5.f);
    setSelectedIdx(0);
}

void Menu::Start::handle(sf::Keyboard::Key input)
{
    switch(input)
    {
        case sf::Keyboard::Enter:
            m_startGameFn();
            break;
        case sf::Keyboard::Q:
            m_quitFn();
            break;
        default:
            Base::handle(input);
            break;
    }
}
