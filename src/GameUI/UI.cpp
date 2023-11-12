#include "UI.hpp"
#include <iostream>
GameUI::UI::UI():
    m_window(sf::VideoMode(800, 600), "Tetris"),
    m_container(&m_window, GameEntity::BlockSize, 10.f, 250.f, 0.f)
{
}

void GameUI::UI::run()
{
    bool isPaused = false;
    sf::Keyboard::Key inputs[5] =
    {
        sf::Keyboard::Up,
        sf::Keyboard::Right,
        sf::Keyboard::Down,
        sf::Keyboard::Left,
        sf::Keyboard::Space,  
    };
    int iteration = 0;
    while (m_window.isOpen())
    {
        if (!isPaused && !m_container.isGameOver)
            m_container.nextStep();

        sf::Event event;
        
        while (m_window.pollEvent(event))
            switch (event.type)
            {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (m_container.isGameOver)
                        break;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        isPaused = !isPaused;
                    else if (!isPaused)
                        for (sf::Keyboard::Key k: inputs)
                            if (sf::Keyboard::isKeyPressed(k))
                            {
                                m_container.handle(k);
                                break;
                            }
                    break;
                default:
                    break;
            };
        m_window.clear(sf::Color::Black);
        m_container.render();
        m_window.display();
    }
}
