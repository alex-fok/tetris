#include "Pause.hpp"
#include <iostream>

#define Options_ButtonCount 2
#define Texture_ButtonCount 4

Menu::Pause::Pause(sf::RenderWindow *w, GameSetting::Setting *setting, std::function<void()> resumeFn) :
    Base(w),
    m_setting(setting),
    m_resumeFn(resumeFn)
{
    m_width = GameUI::Config::Menu::Pause::Width;
    m_height = GameUI::Config::Menu::Pause::Height;
    m_setup(m_width, m_height, "Pause");
    displayContent(options);
}

void Menu::Pause::renderOptionsContent()
{
    // Resume button
    Utils::Button *resume = new Utils::Button("Resume (R)", fontCollection);
    resume->setClickFn(m_resumeFn);
    resume->setHoverFn(std::bind(forwarder_setSelected, this, 0));
    
    // Settings button
    Utils::Button *setting = new Utils::Button("Settings (S)", fontCollection);
    setting->setClickFn(std::bind(forwarder_displayContent, this, style));
    setting->setHoverFn(std::bind(forwarder_setSelected, this, 1));
    
    Utils::Drawable **arr = new Utils::Drawable *[Options_ButtonCount]{resume, setting};
    setDrawables(arr, Options_ButtonCount);
    m_setButtonPositions();
    setSelectedIdx(0);
}

void Menu::Pause::renderStylingContent()
{
    Utils::Button *none = new Utils::Button("None", fontCollection);
    none->setClickFn(std::bind(GameSetting::Setting::forwarder_setBlockTheme, m_setting, GameSetting::BlockTheme::none));
    none->setHoverFn(std::bind(forwarder_setSelected, this, 0));

    Utils::Button *wood = new Utils::Button("Wood", fontCollection);
    wood->setClickFn(std::bind(GameSetting::Setting::forwarder_setBlockTheme, m_setting, GameSetting::BlockTheme::wood));
    wood->setHoverFn(std::bind(forwarder_setSelected, this, 1));

    Utils::Button *grass = new Utils::Button("Grass", fontCollection);
    grass->setClickFn(std::bind(GameSetting::Setting::forwarder_setBlockTheme, m_setting, GameSetting::BlockTheme::grass));
    grass->setHoverFn(std::bind(forwarder_setSelected, this, 2));

    Utils::Button *back = new Utils::Button("Back", fontCollection);
    back->setClickFn(std::bind(forwarder_displayContent, this, options));
    back->setHoverFn(std::bind(forwarder_setSelected, this, 3));
    Utils::Drawable **arr = new Utils::Drawable *[Texture_ButtonCount]{none, wood, grass, back};
    setDrawables(arr, Texture_ButtonCount);
    setListPositions(m_container.getPosition().x, m_offset.top);
    setSelectedIdx(0);
}

void Menu::Pause::displayContent(Menu::Pause::ContentType content)
{
    clearContent();
    switch(content)
    {
        case options:
            renderOptionsContent();
            break;
        case style:
            renderStylingContent();
            break;
        default:
            break;
    }
}

void Menu::Pause::handle(sf::Keyboard::Key input)
{
    switch(input)
    {
        case sf::Keyboard::R:
            m_resumeFn();
            break;
        case sf::Keyboard::S:
            displayContent(style);
            break;
        default:
            Base::handle(input);
            break;
    }
}

void Menu::Pause::forwarder_displayContent(Menu::Pause *self, Menu::Pause::ContentType content)
{
    self->displayContent(content);
}
