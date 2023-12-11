#include "Pause.hpp"

Menu::Pause::Pause(sf::RenderWindow *w, std::function<void()>resumeFn) :
    Base(w)
{
    m_width = GameUI::Config::Menu::Pause::Width;
    m_height = GameUI::Config::Menu::Pause::Height;

    m_setup(m_width, m_height, "Game Over");
    
    // Retry button
    Utils::Button *resume = new Utils::Button("Resume", fontCollection);
    
    resume->setClickFn(resumeFn);
    resume->setHoverFn(std::bind(forwarder_setSelected, this, resume));
    
    m_clickables.push_back(resume);
    
    m_setButtonPositions();
    setSelected(resume);
}
