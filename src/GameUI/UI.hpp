#include <SFML/Graphics.hpp>
#include "../GameEntity/TetrominoContainer.hpp"
#include "../Menu/GameOver.hpp"

namespace GameUI
{
    class UI
    {
    private:
        GameEntity::TetrominoContainer m_tetrominoContainer;
        Menu::GameOver m_gameOverMenu;
        sf::RenderWindow m_window;
        
    public:
        UI();
        void run();
    };
}
