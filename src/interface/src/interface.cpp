#include "interface.h"
#include "interface_build_object.h"

using namespace Game;

const std::string Interface::texture_file_name = "../textures/interface.jpg";
const float Interface::scale = 1.0f;

Interface::Interface(sf::Vector2f &_position, sf::Vector2f &_size) : Object(_position, texture_file_name, this->scale)
{
    object_name = "Interface";
    object_type = Object_type::INTERFACE;

    size = _size;

    sprite.setScale(_size.x / sprite.getLocalBounds().width, _size.y / sprite.getLocalBounds().height);

    border->update_size(_size);

    sf::Vector2f buildings_size(_size.x * 0.4f, _size.y);
    buildings = new Interface_buildings(_position, buildings_size, indent);
    object_interface = new Interface_object(position, size, indent);
}


void Interface::update(Game_state &game, float elapsed_time, sf::Vector2f &mouse_position)
{
    switch (type) {
        case Interface_type::BUILDINGS:
            buildings->update(game, mouse_position);
            break;
        case Interface_type::OBJECT:
            break;
    }
}

void Interface::draw(sf::RenderWindow &window)
{
    border->draw(window);
    draw_texture(window);

    switch (type) {
        case Interface_type::BUILDINGS:
            buildings->draw(window);
            break;
        case Interface_type::OBJECT:
            object_interface->draw(window);
            break;
    }
}

void Interface::click_on(Game_state &game, sf::Vector2f &mouse_pos)
{
    switch (type) {
        case Interface_type::BUILDINGS:
            buildings->click_on(game, mouse_pos);
            break;
        case Interface_type::OBJECT:
            break;
    }
}

void Interface::set_object_interface(Object *object)
{
    type = Interface_type::OBJECT;
    object_interface->set_object(object);
}

void Interface::set_buildings_interface()
{
    type = Interface_type::BUILDINGS;
}
