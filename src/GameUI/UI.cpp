#include <functional>
#include "UI.hpp"
#include "../GameEntity/PreviewList.hpp"
#include "Config.hpp"
#include <iostream>

GameUI::UI::UI():
    m_window(sf::VideoMode((unsigned int)Config::Window::Width, (unsigned int)Config::Window::Height), "Tetris"),
    m_status(Running),
    m_tetroFactory(GameEntity::TetrominoFactory()),
    m_score(&m_window, &m_scoringSystem),
    m_previewList(GameEntity::PreviewList(&m_window, &m_tetroFactory)),
    m_hold(&m_window),
    m_tetroContainer(
        &m_window,
        &m_tetroFactory,
        std::bind(GameUI::UI::forwarder_updateScore, this, std::placeholders::_1),
        std::bind(GameEntity::Hold::forwarder_switchTetro, &m_hold, std::placeholders::_1),
        std::bind(GameUI::UI::forwarder_setStatus, this, std::placeholders::_1)
    ),
    m_gameOverMenu(Menu::GameOver(
        &m_window,
        std::bind(GameUI::UI::forwarder_retry, this),
        std::bind(GameUI::UI::forwarder_close, this)
    )),
    m_pauseMenu(Menu::Pause(
        &m_window,
        std::bind(GameUI::UI::forwarder_setStatus, this, Status::Running)
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
    Utils::Layer *l = new Utils::Layer(&m_window);
    l->addDrawable(&m_gameOverMenu);
    m_layerControl.addTop(l);
}

void GameUI::UI::setPaused()
{
    Utils::Layer *l = new Utils::Layer(&m_window);
    l->addDrawable(&m_pauseMenu);
    m_layerControl.addTop(l);
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
    
    if (m_status == GameOver || m_status == Paused)
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

void GameUI::UI::updateScore(int linesCleared)
{
    m_scoringSystem.updateScore(linesCleared);
}

void GameUI::UI::close()
{
    m_window.close();
}

void GameUI::UI::forwarder_updateScore(GameUI::UI *self, int linesCleared)
{
    self->updateScore(linesCleared);
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
    Utils::Layer *baseLayer = &Utils::Layer(&m_window);
    
    baseLayer->addDrawable(&m_tetroContainer);
    baseLayer->addDrawable(&m_score);
    baseLayer->addDrawable(&m_hold);
    baseLayer->addDrawable(&m_previewList);
    m_layerControl.addTop(baseLayer);
    
    sf::Keyboard::Key gameover_input[5] =
    {
        sf::Keyboard::Up,
        sf::Keyboard::Down,
        sf::Keyboard::Q,
        sf::Keyboard::R,
        sf::Keyboard::Enter
    };

    sf::Keyboard::Key paused_input[4] =
    {
        sf::Keyboard::Up,
        sf::Keyboard::Down,
        sf::Keyboard::R,
        sf::Keyboard::Enter
    };

    sf::Keyboard::Key running_inputs[6] =
    {
        sf::Keyboard::Up,
        sf::Keyboard::Right,
        sf::Keyboard::Down,
        sf::Keyboard::Left,
        sf::Keyboard::Space,
        sf::Keyboard::LShift
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
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_status != GameOver)
                        setStatus(m_status == Paused ? Running : Paused);

                    switch (m_status)
                    {
                        case GameOver:
                            for (sf::Keyboard::Key input: gameover_input)
                                if (sf::Keyboard::isKeyPressed(input))
                                {
                                    m_gameOverMenu.handle(input);
                                    break;
                                }
                            break;                    
                        case Paused:
                            for (sf::Keyboard::Key input: paused_input)
                                if (sf::Keyboard::isKeyPressed(input))
                                {
                                    m_pauseMenu.handle(input);
                                    break;
                                }
                            break;
                        default: // Running
                            for (sf::Keyboard::Key input: running_inputs)
                                if (sf::Keyboard::isKeyPressed(input))
                                {
                                    m_tetroContainer.handle(input);
                                    break;
                                }
                            break;
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left)
                        m_layerControl.handleClick({event.mouseButton.x, event.mouseButton.y});
                    break;
                case sf::Event::MouseMoved:
                    m_layerControl.handleMouseMove({event.mouseMove.x, event.mouseMove.y});
                default:
                    break;
            };
        m_window.clear(sf::Color::Black);
        m_layerControl.render();
        
        m_window.display();
    }
}
