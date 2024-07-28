#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "../GameUI/Config.hpp"
#include "../GameSetting/Setting.hpp"
#include "Base.hpp"

namespace Menu
{
    class Pause : public Base
    {
    private:
        GameSetting::Setting *m_setting;
        std::function<void()> m_resumeFn;
        std::function<void()> m_settingFn;
    public:
        Pause(sf::RenderWindow *w, GameSetting::Setting *setting, std::function<void()> resumeFn);
        enum ContentType {
            options, style
        };
        void renderOptionsContent();
        void renderStylingContent();
        void displayContent(ContentType);
        void handle(sf::Keyboard::Key input);
        void onClose();
        static void forwarder_displayContent(Pause *, ContentType);
    };
}
