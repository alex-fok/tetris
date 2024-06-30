#include <functional>
#include "UI.hpp"
#include "../GameEntity/PreviewList.hpp"
#include "Config.hpp"
#include <iostream>

GameUI::UI::UI():
    m_window(sf::VideoMode((unsigned int)Config::Window::Width, (unsigned int)Config::Window::Height), "Tetris"),
    m_status(Start),
    m_scoreAnimation(
        &m_window,
        std::bind(GameUI::UI::forwarder_startAnimation, this),
        std::bind(GameUI::UI::forwarder_stopAnimation, this)
    ),
    m_clearLinesAnimation(
        &m_window,
        std::bind(GameUI::UI::forwarder_startAnimation, this),
        std::bind(GameUI::UI::forwarder_stopAnimation, this)
    ),
    m_animationCount(0),
    m_setting(),
    m_scoringSystem(&m_scoreAnimation),
    m_tetroFactory(GameEntity::TetrominoFactory()),
    m_score(&m_window, &m_scoringSystem),
    m_previewList(GameEntity::PreviewList(&m_window, &m_tetroFactory, &m_setting)),
    m_hold(&m_window, &m_setting),
    m_tetroContainer(
        &m_window,
        &m_tetroFactory,
        &m_scoringSystem,
        &m_setting,
        &m_clearLinesAnimation,
        std::bind(GameEntity::Hold::forwarder_switchTetro, &m_hold, std::placeholders::_1),
        std::bind(GameUI::UI::forwarder_setStatus, this, std::placeholders::_1)
    ),
    m_startMenu(Menu::Start(
        &m_window,
        std::bind(GameUI::UI::forwarder_startGame, this),
        std::bind(GameUI::UI::forwarder_close, this)
    )),
    m_gameOverMenu(Menu::GameOver(
        &m_window,
        std::bind(GameUI::UI::forwarder_retry, this),
        std::bind(GameUI::UI::forwarder_close, this)
    )),
    m_pauseMenu(Menu::Pause(
        &m_window,
        &m_setting,
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
    m_status = GameOver;
    Utils::Layer *l = new Utils::Layer(&m_window);
    l->addDrawable(&m_gameOverMenu);
    m_layerControl.addTop(l);
}

void GameUI::UI::setPaused()
{
    m_status = Paused;
    Utils::Layer *l = new Utils::Layer(&m_window);
    l->addDrawable(&m_pauseMenu);
    m_layerControl.addTop(l);
}

void GameUI::UI::setRunning()
{
    m_status = Running;
    std::cout << "GameUI::UI >> Status is set to Running" << std::endl;
}

void GameUI::UI::setAnimationPlaying()
{
    if (m_status != AnimationPlaying)
    {
        m_status_before_animation = m_status;
        m_status = AnimationPlaying;
    }
    m_animationCount++;
}

void GameUI::UI::setStatus(Status s)
{
    std::cout << "GAMEUI::UI >> setStatus " << s << std::endl;
    if (m_status == s)
        return;

    if (m_status == GameOver || m_status == Paused)
        m_layerControl.remove(m_layerControl.top());

    switch (s)
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
        case AnimationPlaying:
            setAnimationPlaying();
        default:
            break;
    }
}

void GameUI::UI::startGame()
{
    m_layerControl.remove(m_layerControl.top());
    Utils::Layer *gameLayer = new Utils::Layer(&m_window);
    Utils::Layer *animationLayer = new Utils::Layer(&m_window);
    
    gameLayer->addDrawable(&m_tetroContainer);
    gameLayer->addDrawable(&m_score);
    gameLayer->addDrawable(&m_hold);
    gameLayer->addDrawable(&m_previewList);
    
    animationLayer->addDrawable(&m_scoreAnimation);
    animationLayer->addDrawable(&m_clearLinesAnimation);
    
    m_layerControl.addTop(gameLayer);
    m_layerControl.addTop(animationLayer);
    m_status = Running;
}

void GameUI::UI::startAnimation()
{
    setStatus(AnimationPlaying);
}

void GameUI::UI::stopAnimation()
{
    if (--m_animationCount <= 0)
        setStatus(m_status_before_animation);
}
void GameUI::UI::close()
{
    m_window.close();
}

void GameUI::UI::forwarder_setStatus(GameUI::UI *self, Status s)
{
    self->setStatus(s);
}

void GameUI::UI::forwarder_startGame(GameUI::UI *self)
{
    self->startGame();
}

void GameUI::UI::forwarder_startAnimation(GameUI::UI *self)
{
    self->startAnimation();
}

void GameUI::UI::forwarder_stopAnimation(GameUI::UI *self)
{
    self->stopAnimation();
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
    Utils::Layer *startLayer = new Utils::Layer(&m_window);
    startLayer->addDrawable(&m_startMenu);
    m_layerControl.addTop(startLayer);

    sf::Keyboard::Key start_inputs[4] = 
    {
        sf::Keyboard::Up,
        sf::Keyboard::Down,
        sf::Keyboard::Enter,
        sf::Keyboard::Q
    };

    sf::Keyboard::Key gameover_inputs[5] =
    {
        sf::Keyboard::Up,
        sf::Keyboard::Down,
        sf::Keyboard::Q,
        sf::Keyboard::R,
        sf::Keyboard::Enter
    };

    sf::Keyboard::Key paused_inputs[5] =
    {
        sf::Keyboard::Up,
        sf::Keyboard::Down,
        sf::Keyboard::R,
        sf::Keyboard::S,
        sf::Keyboard::Enter
    };

    sf::Keyboard::Key running_inputs[10] =
    {
        sf::Keyboard::Up,
        sf::Keyboard::Right,
        sf::Keyboard::Down,
        sf::Keyboard::Left,
        sf::Keyboard::Space,
        sf::Keyboard::LShift,
        sf::Keyboard::Z,
        sf::Keyboard::X,
        sf::Keyboard::C,
        sf::Keyboard::LControl
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
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_status != GameOver && m_status != AnimationPlaying)
                        setStatus(m_status == Paused ? Running : Paused);

                    switch (m_status)
                    {
                        case Start:
                            for (sf::Keyboard::Key input: start_inputs)
                                if (sf::Keyboard::isKeyPressed(input))
                                {
                                    m_startMenu.handle(input);
                                    break;
                                }
                            break;
                        case GameOver:
                            for (sf::Keyboard::Key input: gameover_inputs)
                                if (sf::Keyboard::isKeyPressed(input))
                                {
                                    m_gameOverMenu.handle(input);
                                    break;
                                }
                            break;                    
                        case Paused:
                            for (sf::Keyboard::Key input: paused_inputs)
                                if (sf::Keyboard::isKeyPressed(input))
                                {
                                    m_pauseMenu.handle(input);
                                    break;
                                }
                            break;
                        case Running: // Running
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
