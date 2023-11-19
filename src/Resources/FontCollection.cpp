#include "FontCollection.hpp"

Resources::FontCollection::FontCollection()
{
    RobotoRegular.loadFromFile("../../assets/font/Roboto-Regular.ttf");
}

Resources::FontCollection *Resources::FontCollection::fc_ptr = nullptr;

Resources::FontCollection *Resources::FontCollection::getInstance()
{
    if (fc_ptr == nullptr)
        fc_ptr = new FontCollection();

    return fc_ptr;
}
