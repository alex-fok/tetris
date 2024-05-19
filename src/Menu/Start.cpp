#include "Start.hpp"

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

    Utils::Clickable ** arr = new Utils::Clickable *[ButtonCount]{start, quit};
    setClickables(arr, ButtonCount);

    m_setButtonPositions();
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
