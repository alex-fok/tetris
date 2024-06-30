#include "BlockTextureCollection.hpp"

Resources::BlockTextureCollection::BlockTextureCollection()
{
    Wooden.loadFromFile("../../assets/texture/wooden.jpg");
    Grass.loadFromFile("../../assets/texture/grass.jpg");
}

Resources::BlockTextureCollection *Resources::BlockTextureCollection::btc_ptr = nullptr;

Resources::BlockTextureCollection *Resources::BlockTextureCollection::getInstance()
{
    if (btc_ptr == nullptr)
        btc_ptr = new BlockTextureCollection();

    return btc_ptr;
}
