#include <stdlib.h>

#include "person.h"
#include "game.h"

using namespace Game;

const int Person::person_id = 1;
const int Person::min_velocity = Animation::texture_size;

Person::Person() : direction(), Object(sf::Vector2f(0.f, 0.f))
{
    object_name = "Person";

    animation = new Animation(person_id);

    direction_time = 0.0f;

    position = sf::Vector2f(0.f, 0.f);
    velocity = sf::Vector2i(Animation::texture_size, 0);

    sf::Vector2f size = animation->get_texture_size();
    border = new Border_rect(position, size);

    /*for (int i = (int) position.x; i < (int) (position.x + size.x); i++) {
        for (int j = (int) position.y; j < (int) (position.y + size.y); j++) {
            global_map.set_value(i, j, (Object *) this);
        }
    }*/
}

void Person::draw(sf::RenderWindow &window) {
    animation->draw(window);
    border->draw(window);
}

void Person::update_velocity(Utils::Direction direction, sf::Vector2i &velocity)
{
    switch(direction.value) {
        case Utils::Direction::DOWN:
            velocity.x = 0;
            velocity.y = Person::min_velocity;
            break;
        case Utils::Direction::LEFT:
            velocity.x = -Person::min_velocity;
            velocity.y = 0;
            break;
        case Utils::Direction::RIGHT:
            velocity.x = Person::min_velocity;
            velocity.y = 0;
            break;
        case Utils::Direction::UP:
            velocity.x = 0;
            velocity.y = -Person::min_velocity;
            break;
    }
}

void Person::update_direction(float elapsed_time, sf::Vector2i &velocity, float &direction_time) {
    direction_time -= elapsed_time;
    int need_to_change_direction = direction_time < 0 || (velocity.x == 0 && velocity.y == 0);
    if (!need_to_change_direction) {
        return;
    }

    change_direction(this->direction_time);
}

void Person::update_position(float elapsed_time, sf::Vector2i &velocity, sf::Vector2f &position) {
    this->prev_position = this->position;
    position.x += (float) velocity.x * elapsed_time;
    if (position.x < 0) {
        position.x = 0.0f;
        velocity.x = 0;
    } else if (position.x > (float) Game_state::width) {
        position.x = (float) Game_state::Game_state::width;
        velocity.x = 0;
    }

    position.y += (float) velocity.y * elapsed_time;
    if (position.y < 0) {
        position.y = 0.0f;
        velocity.y = 0;
    } else if (position.y > (float) Game_state::height) {
        position.y = (float) Game_state::height;
        velocity.y = 0;
    }
}

void Person::update(Game_state &game, float elapsed_time, sf::Vector2f &mouse_position)
{
    update_direction(elapsed_time, this->velocity, this->direction_time);

    animation->set_animation_id(this->direction.value);
    animation->update_current_frame(elapsed_time, this->velocity);
    animation->update_texture();

    update_position(elapsed_time, this->velocity, this->position);
    border->update_position(position);
    animation->set_position(this->position);

    if (game.intersects_with_objects(this)) {
        go_back();
        animation->set_position(this->position);
    }

    base_update(game, elapsed_time, mouse_position);
}

void Person::go_back()
{
    this->position = this->prev_position;
    change_direction(direction_time, direction.value);
}

void Person::change_direction(float &direction_time, int except_direction)
{
    direction.rand(except_direction);
    direction_time = ((float) std::rand() / (float) RAND_MAX) * max_direction_time;
    update_velocity(direction, velocity);
}


/* Bounds */
bool Person::contains(sf::Vector2f point)
{
    return Person::get_global_bounds().contains(point);
}

bool Person::intersects(const sf::FloatRect& rectangle)
{
    return Person::get_global_bounds().intersects(rectangle);
}


/* Getters */
sf::FloatRect Person::get_global_bounds() const
{
    sf::Sprite sprite = animation->get_sprite();
    return sprite.getGlobalBounds();
}

const sf::Sprite &Person::get_sprite() const
{
    return animation->get_sprite();
}
