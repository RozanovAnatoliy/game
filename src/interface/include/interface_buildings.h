#ifndef GAME_INTERFACE_BUILDINGS_H
#define GAME_INTERFACE_BUILDINGS_H

#include "interface_build_object.h"
#include "object.h"
#include "game.h"

namespace Game {
    class Game_state;
    class Interface_building_object;

    class Interface_buildings {
    public:
        Interface_buildings(sf::Vector2f &_position, sf::Vector2f _size, float _indent);

        void draw(sf::RenderWindow &window);
        void update(Game_state &game, sf::Vector2f &mouse_position);

        void click_on(Game_state &game, sf::Vector2f &mouse_position);
        bool contains(sf::Vector2f &point);
    private:
        std::vector<Interface_building_object *> building_objects;
        Interface_building_object *waiting_building = nullptr;

        sf::Vector2f position;
        sf::Vector2f size;
        float indent;

        int num_icon_rows = 2;
        int num_icon_columns =3;

        sf::RectangleShape end_line;
        float end_line_width = 2.0f;

        //sf::Text buildings_text;
    };
}

#endif /* GAME_INTERFACE_BUILDINGS_H */
