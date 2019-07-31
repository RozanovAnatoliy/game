#ifndef GAME_ANIMATION_H
#define GAME_ANIMATION_H

#include <string>

#include "SFML/Graphics.hpp"

class Animation {
public:
    static const int texture_size;
    static const int max_frames;

    Animation() {
        texture.loadFromFile(texture_file_name);
        sprite.setTexture(texture);
        sprite.setScale(scale, scale);

        current_frame = 0.0f;
        person_id = 0;
        animation_id = 0;
    }

    Animation(int person_id) : Animation() {
        this->person_id = person_id;
    }

    void draw(sf::RenderWindow &window);

    void update_current_frame(float elapsed_time, sf::Vector2i velocity);
    void update_texture();

    void set_position(sf::Vector2f &position);
    void set_animation_id(int animation_id);

    sf::Vector2f get_texture_size();
    const sf::Sprite &get_sprite() const;
private:
    std::string texture_file_name = "../textures/characters.png";

    float current_frame;
    int person_id;
    int animation_id;

    float scale = 3.0f;

    sf::Texture texture;
    sf::Sprite sprite;
};

#endif //GAME_ANIMATION_H
