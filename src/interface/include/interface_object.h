#ifndef OBJECTS_INTERFACE_OBJECT_H
#define OBJECTS_INTERFACE_OBJECT_H

#include "object.h"

#include "SFML/Graphics.hpp"

namespace Game {
    class Interface_object_cell {
    public:
        void cell_init(sf::Vector2f &_position, sf::Vector2f &_size, float bounds_thickness);
        void cell_draw(sf::RenderWindow &window);

        const sf::Vector2f &get_position() const;
        const sf::Vector2f &get_size() const;
    private:
        sf::Vector2f size;
        sf::Vector2f position;

        sf::RectangleShape bounds;
        float bounds_thickness;
        sf::Color bounds_color = sf::Color(240, 240, 170);
    };

    class Interface_object_picture : public Interface_object_cell {
    public:
        void init(sf::Vector2f &_position, float _size, float bounds_thickness);
        void draw(sf::RenderWindow &window);
        void set_sprite(const sf::Sprite &sprite);
    private:
        sf::Sprite sprite;
    };

    class Interface_object_information : public Interface_object_cell {
    public:
        void init(sf::Vector2f &_position, sf::Vector2f &_size, float bounds_thickness);
        void draw(sf::RenderWindow &window);
        void set_object_name(const std::string &_object_name);
    private:
        sf::Text title;
        sf::Text object_name;

        sf::Vector2f next_text_position;
        float indent = 2.0f;

        sf::Font font;
        sf::Color color = sf::Color::Black;
        const unsigned int character_size = 20;
        const unsigned int title_character_size = 25;
    };

    class Interface_object {
    public:
        Interface_object(sf::Vector2f &_position, sf::Vector2f &_size, float _indent);

        void draw(sf::RenderWindow &window);

        void set_object(Object *object);
    private:
        Object *object;

        sf::Vector2f position;
        sf::Vector2f size;

        float indent;
        float bounds_thickness = 4.0f;

        Interface_object_picture picture;
        Interface_object_information information;
    };
}

#endif /* OBJECTS_INTERFACE_OBJECT_H */
