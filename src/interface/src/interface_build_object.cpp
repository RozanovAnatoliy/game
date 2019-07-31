#include <iostream>

#include "interface_build_object.h"
#include "object_manufacture.h"

using namespace Game;

/* Constructors */
Interface_building_object::Interface_building_object(Object_type _object_type, sf::Vector2f &_size,
                                                     sf::Vector2f &_position)
{
    Object_manufacture manufacture;
    manufacture.get_object(_object_type, &(Interface_building_object::object));

    Interface_building_object::type = _object_type;

    Interface_building_object::border = new Border_rect(_position, _size);
    Interface_building_object::size = _size;

    Interface_building_object::sprite = Interface_building_object::object->get_sprite();
    Interface_building_object::sprite.setPosition(_position);

    sf::FloatRect local_bounds = Interface_building_object::sprite.getLocalBounds();
    Interface_building_object::sprite.setScale(_size.x / local_bounds.width,
                                       _size.y / local_bounds.height);
}


void Interface_building_object::draw(sf::RenderWindow &window)
{
    border->draw(window);
    window.draw(Interface_building_object::sprite);

    if (Interface_building_object::clicked_on) {
        Interface_building_object::object->draw(window);
    }
}

void Interface_building_object::update(Game_state &game, sf::Vector2f &mouse_position)
{
    bool is_contain = Interface_building_object::contains(mouse_position);
    Interface_building_object::border->need_to_draw(is_contain);

    if (Interface_building_object::clicked_on) {
        sf::Vector2f new_position = mouse_position - Interface_building_object::object->get_size() * 0.5f;
        Interface_building_object::object->set_position(new_position);

        if (game.intersects_with_objects(Interface_building_object::object)) {
            Interface_building_object::object->draw_bounds(true, sf::Color::Red);
        } else {
            Interface_building_object::object->draw_bounds(true);
        }
    }
}

bool Interface_building_object::contains(sf::Vector2f &point)
{
    return Interface_building_object::sprite.getGlobalBounds().contains(point);
}

void Interface_building_object::click_on(Game_state &game, sf::Vector2f &mouse_position)
{
    if (!Interface_building_object::clicked_on) {
        Interface_building_object::clicked_on = true;
        game.state = State::BUILDING_OBJECT;
    } else {
        if (!game.intersects_with_objects(Interface_building_object::object)) {
            Interface_building_object::clicked_on = false;

            game.lock_objects_mutex();
            game.add_object(Interface_building_object::object);
            game.unlock_objects_mutex();

            Object_manufacture manufacture;
            manufacture.get_object(Interface_building_object::type, &(Interface_building_object::object));

            game.state = State::RUNNING;
        }
    }
}


/* Getters */
const sf::Vector2f &Interface_building_object::get_position()
{
    return Interface_building_object::object->get_position();
}
