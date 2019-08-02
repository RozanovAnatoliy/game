#include "view.h"

using namespace Game;

View::View(Game_state &_game, sf::Vector2f &_size)
{
    View::game = &_game;
    View::size = _size;
    view.reset(sf::FloatRect(sf::Vector2f(0.0f, 0.0f), _size));
}

void View::default_view()
{
    view.reset(sf::FloatRect(sf::Vector2f(0.0f, 0.0f), size));
}

void View::zoom(float factor)
{
    sf::Vector2f prev_size = view.getSize();
    view.zoom(factor);
    check_out_of_game_area(prev_size);
}

void View::move(float offset_x, float offset_y)
{
    sf::Vector2f offset = sf::Vector2f(offset_x * move_velocity.x, offset_y * move_velocity.y);
    view.move(offset);
    check_out_of_game_area();
}


const sf::View &View::get_view() const
{
    return view;
}

void View::check_out_of_game_area(sf::Vector2f prev_size)
{
    if (view.getSize().x > (float) game->area_width) {
        view.setSize(prev_size);
    }

    sf::Vector2f center = view.getCenter();
    sf::Vector2f half_size = view.getSize() * 0.5f;
    if (center.x - half_size.x < 0) {
        center.x = half_size.x;
    } else if (center.x + half_size.x > (float) game->area_width) {
        std::cout << center.x << " " << half_size.x << std::endl;
        center.x = (float) game->area_width - half_size.x;
    }

    if (center.y - half_size.y < 0) {
        center.y = half_size.y;
    } else if (center.y + half_size.y > (float) game->area_height) {
        center.y = (float) game->area_height - half_size.y;
    }

    view.setCenter(center);
}
