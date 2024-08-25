#include <cstdlib>
#include <string>
#include "FontCollection.hpp"
#include <stdlib.h>

Resources::FontCollection::FontCollection()
{
    const char *ENVIRONMENT = std::getenv("ENVIRONMENT");
    std::string assetPath = std::string(ENVIRONMENT != NULL && std::strcmp(ENVIRONMENT, "dev") == 0 ? "../../assets/" : "../assets/");
    std::string robotoFontLocation = std::string(assetPath + "font/Roboto-Regular.ttf");
    RobotoRegular.loadFromFile(robotoFontLocation);
}

Resources::FontCollection *Resources::FontCollection::fc_ptr = nullptr;

Resources::FontCollection *Resources::FontCollection::getInstance()
{
    if (fc_ptr == nullptr)
        fc_ptr = new FontCollection();

    return fc_ptr;
}
