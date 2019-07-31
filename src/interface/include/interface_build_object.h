#ifndef GAME_INTERFACE_BUILD_OBJECT_H
#define GAME_INTERFACE_BUILD_OBJECT_H

#include "SFML/Graphics.hpp"
#include "border_rect.h"
#include "object.h"
#include "game.h"

namespace Game {
    class Interface_building_object {
    public:
        Interface_building_object(Object_type _object_type, sf::Vector2f &_size, sf::Vector2f &_position);

        void draw(sf::RenderWindow &window);
        void update(Game_state &game, sf::Vector2f &mouse_position);

        const sf::Vector2f& get_position();

        bool contains(sf::Vector2f &point);
        void click_on(Game_state &game, sf::Vector2f &mouse_position);
    private:
        bool clicked_on = false;
        Object_type type;
        sf::Vector2f size;

        sf::Sprite sprite;

        Border_rect *border;
        Object *object {};
    };
}

#endif /* GAME_INTERFACE_BUILD_OBJECT_H */
