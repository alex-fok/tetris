#include <cstdlib>
#include <cstring>
#include "BlockTextureCollection.hpp"

Resources::BlockTextureCollection::BlockTextureCollection()
{
    const char *ENVIRONMENT = std::getenv("ENVIRONMENT");
    std::string assetPath = std::string(ENVIRONMENT != NULL && std::strcmp(ENVIRONMENT, "dev") == 0 ? "../../assets/" : "../assets/");
    std::string woodenLocation = std::string(assetPath + "texture/wooden.jpg");
    std::string grassLocation = std::string(assetPath + "texture/grass.jpg");
    Wooden.loadFromFile(woodenLocation);
    Grass.loadFromFile(grassLocation);
}

Resources::BlockTextureCollection *Resources::BlockTextureCollection::btc_ptr = nullptr;

Resources::BlockTextureCollection *Resources::BlockTextureCollection::getInstance()
{
    if (btc_ptr == nullptr)
        btc_ptr = new BlockTextureCollection();

    return btc_ptr;
}
