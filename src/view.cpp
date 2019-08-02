#include "view.h"

using namespace Game;

View::View(sf::Vector2f &_size)
{
    View::size = _size;
    view.reset(sf::FloatRect(sf::Vector2f(0.0f, 0.0f), _size));
}

void View::default_view()
{
    view.reset(sf::FloatRect(sf::Vector2f(0.0f, 0.0f), size));
}


void View::zoom(float factor)
{
    view.zoom(factor);
}

const sf::View &View::get_view() const
{
    return view;
}
