#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <vector>
#include <mutex>

#include "SFML/Graphics.hpp"

#include "object.h"

namespace Game {
    class Object;
    class Interface;

    enum class State {
        NOT_RUNNING = 0,
        RUNNING,
        BUILDING_OBJECT,
    };

    class Game_state {
    public:
        Game_state(std::vector<Object *> &_object, sf::RenderWindow &_window);

        void add_object(Object *object);
        void lock_objects_mutex();
        void unlock_objects_mutex();

        bool intersects_with_objects(const Object *target_object);
        bool out_of_area(sf::Vector2f &point);
        bool out_of_area(sf::FloatRect &rect);

        sf::Vector2f get_window_size();

        State state;

        const unsigned int area_width = 3000;
        const unsigned int area_height = 3000;

        int max_fps = 100;
        float sec_per_frame;
    private:
        std::vector<Object *> *objects;
        std::mutex objects_mutex;

        sf::RenderWindow *window;
    };
}

#endif /* GAME_GAME_H */
