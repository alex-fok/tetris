#include <SFML/Graphics.hpp>
#include "../GameEntity/TetrominoContainer.hpp"
#include "../Menu/GameOver.hpp"
namespace GameUI
{
    class UI
    {
    private:
        GameEntity::TetrominoContainer m_container;
        Menu::GameOver m_gameOver_menu;
        sf::RenderWindow m_window;
        
    public:
        UI();
        void run();
    };
}
