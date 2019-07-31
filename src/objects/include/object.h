#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>

#include "game.h"
#include "SFML/Graphics.hpp"
#include "border_rect.h"

namespace Game {
    class Game_state;

    enum class Object_type {
        OBJECT = 0,
        INTERFACE,
        HOUSE,
        PERSON
    };

    class Object
    {
    public:
        /* Constructors */
        Object();
        Object(sf::Vector2f _position);
        Object(sf::Vector2f &_position, const std::string &texture_file_name, float scale);
        void init(sf::Vector2f &_position, const std::string &texture_file_name, float scale);

        /* Virtual functions */
        virtual void update(Game_state &game, float elapsed_time, sf::Vector2f &mouse_position);
        virtual void draw(sf::RenderWindow &window);

        void base_update(Game_state &game, float elapsed_time, sf::Vector2f &mouse_position);
        void draw_bounds(bool need_to_draw, sf::Color color = sf::Color::White);

        /* Bounds */
        virtual bool contains(sf::Vector2f point);
        virtual bool intersects(const sf::FloatRect& rectangle);

        /* Getters */
        virtual sf::FloatRect get_global_bounds() const;
        virtual const sf::Sprite &get_sprite() const;

        sf::Vector2f get_border_position();
        sf::Vector2f get_border_size();
        const sf::Vector2f &get_size() const;
        const sf::Vector2f &get_position() const;

        /* Setters */
        void set_position(const sf::Vector2f &position);
        void set_size(const sf::Vector2f &size);

        std::string object_name = "Object";
        Object_type object_type = Object_type::OBJECT;
    protected:
        sf::Vector2f size;
        sf::Vector2f position;
        Game::Border_rect *border;
        sf::Sprite sprite;

        void draw_texture(sf::RenderWindow &window);
    private:
        sf::Texture texture;
    };
}

#endif /* GAME_OBJECT_H */
