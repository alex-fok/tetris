#include "Start.hpp"

#define ButtonCount 1

Menu::Start::Start(sf::RenderWindow *w, std::function<void()>startGameFn) :
    Base(w),
    m_startGameFn(startGameFn)
{
    m_width = GameUI::Config::Menu::Start::Width;
    m_height = GameUI::Config::Menu::Start::Height;

    m_setup(m_width, m_height, "Tetris");

    // Start button
    Utils::Button *start = new Utils::Button("Sart (S)", fontCollection);

    start->setClickFn(m_startGameFn);
    start->setHoverFn(std::bind(forwarder_setSelected, this, 0));

    Utils::Clickable ** arr = new Utils::Clickable *[ButtonCount]{start};
    setClickables(arr, ButtonCount);

    m_setButtonPositions();
    setSelectedIdx(0);
}

void Menu::Start::handle(sf::Keyboard::Key input)
{
    switch(input)
    {
        case sf::Keyboard::S:
            m_startGameFn();
            break;
        default:
            Base::handle(input);
            break;
    }
}
