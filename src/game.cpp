#include "game.h"

#include <thread>
#include <interface.h>

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

bool Game::Game_state::out_of_area(sf::Vector2f &point)
{
    sf::FloatRect area(sf::Vector2f(0.0f, 0.0f),
                       sf::Vector2f((float) area_width, (float) area_height));
    return !area.contains(point);
}

bool Game::Game_state::out_of_area(sf::FloatRect &rect)
{
    sf::FloatRect intersection;
    sf::FloatRect area(sf::Vector2f(0.0f, 0.0f),
                       sf::Vector2f((float) area_width, (float) area_height));
    area.intersects(rect, intersection);
    return (intersection.width != rect.width || intersection.height != rect.height);
}

sf::Vector2f Game::Game_state::get_window_size()
{
    sf::Vector2u size_u = window->getSize();
    sf::Vector2f size_f = sf::Vector2f((float) size_u.x, (float) size_u.y);
    return size_f;
}
