#include <functional>
#include "UI.hpp"
#include "Config.hpp"
#include "../Utils/LayerControl.hpp"
#include "../Menu/GameOver.hpp"
#include <iostream>

GameUI::UI::UI():
    m_window(sf::VideoMode((unsigned int)Config::Window::Width, (unsigned int)Config::Window::Height), "Tetris"),
    m_layerControl(&m_window),
    m_status(Running),
    m_tetroContainer(
        &m_window,
        Config::Block::Size,
        Config::TetrominoContainer::BorderWidth,
        Config::TetrominoContainer::Window_Offset,
        std::bind(GameUI::UI::forwarder_setStatus, this, std::placeholders::_1)
    ),
    m_gameOverMenu(Menu::GameOver(
        &m_window,
        std::bind(GameUI::UI::forwarder_retry, this),
        std::bind(GameUI::UI::forwarder_close, this)
    ))
{
}

void GameUI::UI::retry()
{
    m_tetroContainer.reset();
    setStatus(GameUI::Status::Running);
}

void GameUI::UI::setGameOver()
{
    Utils::Layer *l = new Utils::Layer();
    l->addDrawable(&m_gameOverMenu);
    m_layerControl.addTop(l);
}

void GameUI::UI::setPaused()
{
    std::cout << "GameUI::UI >> Status is set to Paused" << std::endl;
}

void GameUI::UI::setRunning()
{
    std::cout << "GameUI::UI >> Status is set to Running" << std::endl;
}

void GameUI::UI::setStatus(Status s)
{
    std::cout << "GAMEUI::UI >> setStatus " << s << std::endl;
    if (m_status == s)
        return;
    
    if (m_status == GameOver)// || m_status == Paused)
       m_layerControl.remove(m_layerControl.top());
    
    m_status = s;
    
    switch (m_status)
    {
        case GameOver:
            setGameOver();
            break;
        case Paused:
            setPaused();
            break;
        case Running:
            setRunning();
            break;
        default:
            break;
    }
}

void GameUI::UI::close()
{
    m_window.close();
}

void GameUI::UI::forwarder_setStatus(GameUI::UI *self, Status s)
{
    self->setStatus(s);
}

void GameUI::UI::forwarder_retry(GameUI::UI *self)
{
    self->retry();
}

void GameUI::UI::forwarder_close(GameUI::UI *self)
{
    self->close();
}

void GameUI::UI::run()
{
    // Base layer
    Utils::Layer *baseLayer = &Utils::Layer();
    
    baseLayer->addDrawable(&m_tetroContainer);
    m_layerControl.addTop(baseLayer);
    
    sf::Keyboard::Key inputs[5] =
    {
        sf::Keyboard::Up,
        sf::Keyboard::Right,
        sf::Keyboard::Down,
        sf::Keyboard::Left,
        sf::Keyboard::Space,
    };
    
    while (m_window.isOpen())
    {
        if (m_status == Running)
            m_tetroContainer.nextStep();

        sf::Event event;
        
        while (m_window.pollEvent(event))
            switch (event.type)
            {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (m_status == GameOver)
                        break;
                    
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        setStatus(m_status == Paused ? Running : Paused);
                        
                    else if (m_status != Paused)
                        for (sf::Keyboard::Key k: inputs)
                            if (sf::Keyboard::isKeyPressed(k))
                            {
                                m_tetroContainer.handle(k);
                                break;
                            }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left)
                        m_layerControl.handleClick({event.mouseButton.x, event.mouseButton.y});
                    break;
                default:
                    break;
            };
        m_window.clear(sf::Color::Black);
        m_layerControl.render();
        
        m_window.display();
    }
}
