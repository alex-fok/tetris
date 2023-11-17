#include "UI.hpp"
#include "Config.hpp"
#include "../Menu/GameOver.hpp"

GameUI::UI::UI():
    m_window(sf::VideoMode((unsigned int)Config::Window::Width, (unsigned int)Config::Window::Height), "Tetris"),
    m_tetrominoContainer(&m_window, Config::Block::Size, Config::TetrominoContainer::BorderWidth, Config::TetrominoContainer::Window_Offset),
    m_gameOverMenu(Menu::GameOver(&m_window))
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
        if (!isPaused && !m_tetrominoContainer.isGameOver)
            m_tetrominoContainer.nextStep();

        sf::Event event;
        
        while (m_window.pollEvent(event))
            switch (event.type)
            {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (m_tetrominoContainer.isGameOver)
                        break;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        isPaused = !isPaused;
                    else if (!isPaused)
                        for (sf::Keyboard::Key k: inputs)
                            if (sf::Keyboard::isKeyPressed(k))
                            {
                                m_tetrominoContainer.handle(k);
                                break;
                            }
                    break;
                default:
                    break;
            };
        m_window.clear(sf::Color::Black);
        m_tetrominoContainer.render();
        if (m_tetrominoContainer.isGameOver)
            m_gameOverMenu.render();
        m_window.display();
    }
}
