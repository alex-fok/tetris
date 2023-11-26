#include <functional>
#include "UI.hpp"
#include "Config.hpp"
#include "../Utils/LayerControl.hpp"
#include "../Menu/GameOver.hpp"
#include <iostream>

GameUI::UI::UI():
    m_window(sf::VideoMode((unsigned int)Config::Window::Width, (unsigned int)Config::Window::Height), "Tetris"),
    m_layerControl(&m_window),
    m_gameOverMenu(Menu::GameOver(&m_window)),
    m_status(Running)
{
}
void GameUI::UI::setGameOver()
{
    Utils::Layer *l = new Utils::Layer();
    l->addDrawable(new Menu::GameOver(&m_window));
    m_layerControl.addTop(l);
}

void GameUI::UI::setPaused()
{

}

void GameUI::UI::setStatus(Status s)
{
    if (m_status == s)
        return;
    
    if (m_status == GameOver)// || m_status == Paused)
       m_layerControl.removeTop(m_layerControl.top());
    
    m_status = s;
    
    switch (m_status)
    {
        case GameOver:
            std::cout << "GAME OVER" << std::endl;
            setGameOver();
            break;
        case Paused:
            setPaused();
            break;
        case Running:

        default:
            break;
    }
}

void GameUI::UI::forwarder_setStatus(GameUI::UI *self, Status s)
{
    self->setStatus(s);
}

void GameUI::UI::run()
{
    // counter
    int loop = 0;
    // Base layer
    Utils::Layer *baseLayer = &Utils::Layer();
    std::function<void(Status)> statusSetter = std::bind(GameUI::UI::forwarder_setStatus, this, std::placeholders::_1);

    GameEntity::TetrominoContainer tetroContainer(
        &m_window,
        Config::Block::Size,
        Config::TetrominoContainer::BorderWidth,
        Config::TetrominoContainer::Window_Offset,
        statusSetter
    );
    
    baseLayer->addDrawable(&tetroContainer);
    m_layerControl.addTop(baseLayer);
    
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
        if (m_status != Paused && m_status != GameOver)
            tetroContainer.nextStep();

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
                        isPaused = !isPaused;
                    else if (!isPaused)
                        for (sf::Keyboard::Key k: inputs)
                            if (sf::Keyboard::isKeyPressed(k))
                            {
                                tetroContainer.handle(k);
                                break;
                            }
                    break;
                default:
                    break;
            };
        m_window.clear(sf::Color::Black);
        m_layerControl.render();
        
        m_window.display();
    }
}
