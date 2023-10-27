#include <SFML/Graphics.hpp>
#include "../GameEntity/TetrominoContainer.hpp"

namespace GameUI
{
    class UI
    {
    private:
        GameEntity::TetrominoContainer m_container;
        sf::RenderWindow m_window;
    public:
        UI();
        void run();
    
    private:
        void handleKeyEvents();
    };
}
