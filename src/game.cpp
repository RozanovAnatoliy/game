#include "game.h"

#include <thread>
#include <interface.h>

const unsigned int Game::Game_state::width = 800;
const unsigned int Game::Game_state::height = 600;

Game::Game_state::Game_state(std::vector<Object *> &_object, sf::RenderWindow &_window)
{
    Game_state::objects = &_object;
    Game_state::window = &_window;

    Game_state::sec_per_frame = 1.0f / (float) Game_state::max_fps;
}

void Game::Game_state::add_object(Object *object)
{
    Game_state::objects->push_back(object);
}

void Game::Game_state::lock_objects_mutex()
{
    objects_mutex.lock();
}

void Game::Game_state::unlock_objects_mutex()
{
    objects_mutex.unlock();
}

bool Game::Game_state::intersects_with_objects(const Game::Object *target_object)
{
    sf::FloatRect target_bounds = target_object->get_global_bounds();

    for (Object *object : (*Game_state::objects)) {
        if (object != target_object && object->intersects(target_bounds)) {
            return true;
        }
    }

    return false;
}

bool Game::Game_state::out_of_window()
{
    return false;
}
