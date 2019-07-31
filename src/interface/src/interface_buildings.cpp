#include <iostream>

#include "interface_buildings.h"

/* Constructors */
Game::Interface_buildings::Interface_buildings(sf::Vector2f &_position, sf::Vector2f _size, float _indent)
{
    sf::Vector2f icon_position = sf::Vector2f(_position.x + _indent, _position.y);

    float _icon_size = (_size.y * 0.5f) - 3 * _indent;
    sf::Vector2f icon_size = sf::Vector2f(_icon_size, _icon_size);

    for (int row = 0; row < num_icon_rows; row++) {
        for (int column = 0; column < num_icon_columns; column++) {
            building_objects.push_back(new Interface_building_object(Object_type::HOUSE, icon_size, icon_position));
            icon_position.x += _indent + icon_size.x;
        }
        icon_position.y += _indent + icon_size.y;
        icon_position.x = _position.x;
    }

    //buildings_text.setString(std::string("Buildings"));
    //buildings_text.setPosition(_position);
    //buildings_text.setFillColor(sf::Color::Black);
    //buildings_text.setCharacterSize(20);

    end_line.setPosition(_position.x + _size.x, _position.y);
    end_line.setSize(sf::Vector2f(end_line_width, _size.y));
    end_line.setFillColor(sf::Color(180, 160, 20));

    this->position = _position;
    this->indent = _indent;
    this->size = _size;
}


void Game::Interface_buildings::draw(sf::RenderWindow &window)
{
    for (Interface_building_object *object : building_objects) {
        object->draw(window);
    }

    //window->draw(buildings_text);
    window.draw(end_line);
}

void Game::Interface_buildings::update(Game_state &game, sf::Vector2f &mouse_position)
{
    for (Interface_building_object *object : building_objects) {
        object->update(game, mouse_position);
    }
}

void Game::Interface_buildings::click_on(Game_state &game, sf::Vector2f &mouse_position)
{
    if (game.state != State::BUILDING_OBJECT) {
        for (Interface_building_object *object : building_objects) {
            if (object->contains(mouse_position)) {
                std::cout << "Mouse pressed on interface building object" << std::endl;
                object->click_on(game, mouse_position);

                waiting_building = object;
            }
        }
    } else {
        waiting_building->click_on(game, mouse_position);
    }
}

bool Game::Interface_buildings::contains(sf::Vector2f &point)
{
    return sf::FloatRect(position, size).contains(point);
}
