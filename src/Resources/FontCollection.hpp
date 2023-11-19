#pragma once
#include <SFML/Graphics.hpp>

namespace Resources
{
    class FontCollection
    {
    private:
        static FontCollection *fc_ptr;
        FontCollection();
        
    public:
        FontCollection(FontCollection &fc) = delete;
        static FontCollection *getInstance();
        sf::Font RobotoRegular;
    };
}
