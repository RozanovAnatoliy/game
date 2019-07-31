#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include "interface_buildings.h"
#include "interface_object.h"

namespace Game {
    class Game_state;

    enum class Interface_type {
        BUILDINGS = 0,
        OBJECT
    };

    class Interface : public Object {
    public:
        Interface(sf::Vector2f &_position, sf::Vector2f &_size);

        void draw(sf::RenderWindow &window) override;
        void update(Game_state &game, float elapsed_time, sf::Vector2f &mouse_position) override;

        void click_on(Game_state &game, sf::Vector2f &mouse_pos);
        void set_object_interface(Object *object);
        void set_buildings_interface();
    private:
        Interface_type type = Interface_type::BUILDINGS;

        static const std::string texture_file_name;
        static const float scale;

        const float indent = 2.0f;

        Interface_buildings *buildings;
        Interface_object *object_interface;
    };
}

#endif /* GAME_INTERFACE_H */