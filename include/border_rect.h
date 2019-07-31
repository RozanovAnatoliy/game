#ifndef GAME_BORDER_RECT_H
#define GAME_BORDER_RECT_H

#include "SFML/Graphics.hpp"

namespace Game {
    class Border_rect
    {
    public:
        Border_rect();
        Border_rect(sf::Vector2f _position, sf::Vector2f _size);

        void update_position(sf::Vector2f _position);
        void update_size(sf::Vector2f _size);
        void need_to_draw(bool is_need, sf::Color _color = sf::Color::White);

        void draw(sf::RenderWindow &window);

        const sf::Vector2f &get_position() const;
        const sf::Vector2f &get_size() const;
        const sf::Color &get_default_color() const;

        sf::Color color;
    private:
        sf::Vector2f position;
        sf::Vector2f size;

        sf::Vertex line_up[2];
        sf::Vertex line_down[2];
        sf::Vertex line_left[2];
        sf::Vertex line_right[2];

        bool need_draw = false;
        sf::Color default_color = sf::Color::White;

        void lines_init();
    };
}

#endif /* GAME_BORDER_RECT_H */
