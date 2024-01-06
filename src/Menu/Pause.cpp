#include "Pause.hpp"

Menu::Pause::Pause(sf::RenderWindow *w, std::function<void()>resumeFn) :
    Base(w),
    m_resumeFn(resumeFn)
{
    m_width = GameUI::Config::Menu::Pause::Width;
    m_height = GameUI::Config::Menu::Pause::Height;

    m_setup(m_width, m_height, "Pause");
    
    // Retry button
    Utils::Button *resume = new Utils::Button("Resume (R)", fontCollection);
    
    resume->setClickFn(resumeFn);
    resume->setHoverFn(std::bind(forwarder_setSelected, this, resume));
    
    m_clickables.push_back(resume);
    
    m_setButtonPositions();
    setSelected(resume);
}

void Menu::Pause::handle(sf::Keyboard::Key input)
{
    switch(input)
    {
        case sf::Keyboard::Up:
            break;
        case sf::Keyboard::Down:
            break;
        case sf::Keyboard::R:
            m_resumeFn();
            break;
        default:
            break;
    }
}
