#include "animation.h"

const int Animation::texture_size = 16;
const int Animation::max_frames = 3;

void Animation::set_position(sf::Vector2f &position) {
    this->sprite.setPosition(position);
}

void Animation::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Animation::set_animation_id(int animation_id) {
    this->animation_id = animation_id;
}

void Animation::update_current_frame(float elapsed_time, sf::Vector2i velocity)
{
    if (velocity.x == 0.0f && velocity.y == 0.0f) {
        current_frame = 1;
    }

    current_frame += elapsed_time * 2.0f;
    if (current_frame > (float) Animation::max_frames) {
        current_frame = 0.0f;
    }
}

void Animation::update_texture() {
    int x = texture_size * (person_id * Animation::max_frames + (int) current_frame);
    int y = texture_size * animation_id;
    sprite.setTextureRect(sf::IntRect(x, y, texture_size, texture_size));
}

sf::Vector2f Animation::get_texture_size()
{
    return sf::Vector2f((float) texture_size * scale, (float) texture_size * scale);
}

const sf::Sprite &Animation::get_sprite() const
{
    return sprite;
}
