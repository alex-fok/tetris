#include "UI.hpp"

GameUI::UI::UI():
    m_window(sf::VideoMode(800, 600), "Tetris"),
    m_container(&m_window, GameEntity::BlockSize, 10.f, 250.f, 0.f)
{
}

void GameUI::UI::handleKeyEvents()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        m_container.rotate(GameEntity::Tetromino::Rotation::Clockwise);
     else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_container.moveRight();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_container.moveLeft();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        m_container.moveDown();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        m_container.drop();
}

void GameUI::UI::run()
{
    while (m_window.isOpen())
    {
        sf::Event event;
        
        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::KeyPressed:
                    handleKeyEvents();
                    break;
                default:
                    break;
            };
        }
        m_window.clear(sf::Color::Black);
        m_container.render();
        m_window.display();
    }
}
