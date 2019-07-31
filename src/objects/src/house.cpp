#include <game.h>
#include "house.h"

using namespace Game;

const std::string House::texture_file_name = "../textures/house.png";
const float House::scale = 0.25;

void House::init()
{
    House::object_name = "House";
    House::object_type = Object_type::HOUSE;
}

House::House() : Object(sf::Vector2f(0.f, 0.f), House::texture_file_name, House::scale)
{
    init();
}

House::House(sf::Vector2f _position) : Object(_position, House::texture_file_name, House::scale)
{
    init();
}

void House::draw(sf::RenderWindow &window)
{
    border->draw(window);
    draw_texture(window);
}
