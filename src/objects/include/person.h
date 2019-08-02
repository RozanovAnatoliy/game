#ifndef GAME_PERSON_H
#define GAME_PERSON_H

#include <iostream>

#include "game.h"
#include "object.h"
#include "animation.h"
#include "border_rect.h"
#include "direction.h"

namespace Game {
    class Person : public Object {
    public:
        static const int person_id;
        static const int min_velocity;

        Person();

        /* Virtual functions */
        void update(Game_state &game, float elapsed_time, sf::Vector2f &mouse_position) override;
        void draw(sf::RenderWindow &window) override;
        void go_back();

        bool contains(sf::Vector2f point) override;
        bool intersects(const sf::FloatRect& rectangle) override;

        /* Getters */
        sf::FloatRect get_global_bounds() const override;
        const sf::Sprite &get_sprite() const override;

        sf::Vector2i velocity;
    private:
        void update_velocity(Utils::Direction direction, sf::Vector2i &velocity);
        void update_position(Game_state &game, float elapsed_time, sf::Vector2i &velocity, sf::Vector2f &position);
        void update_direction(float elapsed_time, sf::Vector2i &velocity, float &direction_time);

        void change_direction(float &direction_time, int except_direction = -1);

        Animation *animation;

        Utils::Direction direction;
        float direction_time;
        const float max_direction_time = 4.0f;

        sf::Vector2f prev_position;
    };
}

#endif //GAME_PERSON_H
