#include <iostream>
#include "GameOver.hpp"

Menu::GameOver::GameOver(sf::RenderWindow *w):
    Base(w, {s_Width, s_Height}, "Game Over")
{
    m_buttons.push_back(new Utils::Button("Retry", fontCollection));
    setButtonPositions(m_buttons);
    for (Utils::Button *b : m_buttons)
        sf::Vector2f position = b->content.getPosition();
}

void Menu::GameOver::retry()
{
    std::cout << "Attempting to retry" << std::endl;
}

void Menu::GameOver::render()
{
    renderBase();
    for (Utils::Button *b: m_buttons)
    {
        m_window->draw(b->content);
    }
}
