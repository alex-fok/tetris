#include <SFML/Graphics.hpp>
#include "GameEntity/Block.hpp"
#include "GameEntity/Tetromino.hpp"
#include "GameEntity/TetrominoContainer.hpp"

void handleKeyEvents(GameEntity::TetrominoContainer *container)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        container->rotate(GameEntity::Tetromino::Rotation::Clockwise);
     else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        container->moveRight();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        container->moveLeft();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        container->moveDown();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        container->drop();
}

int main(int, char**)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");
    GameEntity::TetrominoContainer container(&window, GameEntity::BlockSize, 10.f, 250.f, 0.f);

    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    handleKeyEvents(&container);
                    break;
                default:
                    break;
            };
        }
        window.clear(sf::Color::Black);
        container.render();
        window.display();
    }
    return 0;
}
