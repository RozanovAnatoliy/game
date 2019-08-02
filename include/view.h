#ifndef OBJECTS_VIEW_H
#define OBJECTS_VIEW_H

#include "game.h"
#include "SFML/Graphics.hpp"

namespace Game {
    class View {
    public:
        View(Game_state &game, sf::Vector2f &_size);

        void default_view();
        void zoom(float factor);
        void move(float offset_x, float offset_y);

        const sf::View &get_view() const;
    private:
        sf::View view;
        sf::Vector2f size;
        sf::Vector2f move_velocity = sf::Vector2f(500.0f, 500.0f);

        Game_state *game;

        void check_out_of_game_area(sf::Vector2f prev_size = sf::Vector2f(0.0f, 0.0f));
    };
}

#endif /* OBJECTS_VIEW_H */
