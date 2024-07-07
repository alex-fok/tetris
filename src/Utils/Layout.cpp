#include "Layout.hpp"

Utils::Layout::Layout(float mt, float ml, float m_inner_x, float m_inner_y):
margin_top(mt),
margin_left(ml),
margin_inner_x(m_inner_x),
margin_inner_y(m_inner_y)
{
};

void Utils::Layout::addLayout(Utils::Layout *layout)
{
    inner_layouts.push_back(layout);
}
