#pragma once
#include <vector>
#include "../Utils/Drawable.hpp"
#include "../Utils/Clickable.hpp"

namespace Utils 
{
    enum LayoutType
    {
        list, grid
    };
    class Layout : public Drawable
    {
    public:
        float margin_top;
        float margin_left;
        float margin_inner_x;
        float margin_inner_y;
        std::vector<Utils::Layout *> inner_layouts;
        Layout(float mt, float ml, float margin_inner_x, float margin_inner_y);
        void addLayout(Layout *);
    };
}
