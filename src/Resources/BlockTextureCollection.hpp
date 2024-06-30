#pragma once

#include <SFML/Graphics.hpp>

namespace Resources {
    class BlockTextureCollection
    {
    private:
        static BlockTextureCollection *btc_ptr;
        BlockTextureCollection();
    public:
        BlockTextureCollection(BlockTextureCollection &btc) = delete;
        static BlockTextureCollection *getInstance();
        sf::Texture Wooden;
        sf::Texture Grass;
    };
}
