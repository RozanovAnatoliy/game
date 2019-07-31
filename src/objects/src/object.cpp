#include "object.h"

using namespace Game;

/* Constructors */
void Object::init(sf::Vector2f &_position, const std::string &texture_file_name, float scale)
{
    Object::object_type = Object_type::OBJECT;
    Object::position = _position;

    if (!texture_file_name.empty()) {
        texture.loadFromFile(texture_file_name);

        Object::sprite.setTexture(texture);
        Object::sprite.setScale(scale, scale);
        Object::sprite.setPosition(_position);

        sf::Vector2u _size = texture.getSize();
        Object::size = sf::Vector2f((float) _size.x * scale, (float) _size.y * scale);

        Object::border = new Game::Border_rect(_position, Object::size);
    }
}

Object::Object(sf::Vector2f &_position, const std::string &texture_file_name, float scale)
{
    init(_position, texture_file_name, scale);
}

Object::Object(sf::Vector2f _position)
{
    init(_position, std::string(""), 1.0f);
}

Object::Object()
{
    sf::Vector2f _position(0.0f, 0.0f);
    init(_position, std::string(""), 1.0f);
}


void Object::draw_texture(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}

void Object::draw(sf::RenderWindow &window)
{
    draw_texture(window);
}

void Object::update(Game_state &game, float elapsed_time, sf::Vector2f &mouse_position)
{
    base_update(game, elapsed_time, mouse_position);
}

/* 1. Draw bounds */
void Object::base_update(Game_state &game, float elapsed_time, sf::Vector2f &mouse_position)
{
    bool is_need_to_draw = contains(mouse_position) && game.state != State::BUILDING_OBJECT;
    border->need_to_draw(is_need_to_draw);
}

void Object::draw_bounds(bool need_to_draw, sf::Color color)
{
    Object::border->need_to_draw(need_to_draw, color);
}


/* Bounds */
bool Object::contains(sf::Vector2f point)
{
    return Object::get_global_bounds().contains(point);
}

bool Object::intersects(const sf::FloatRect& rectangle)
{
    return Object::get_global_bounds().intersects(rectangle);
}


/* Setters */
void Object::set_position(const sf::Vector2f &_position)
{
    Object::position = _position;
    Object::sprite.setPosition(_position);
    Object::border->update_position(_position);
}

void Object::set_size(const sf::Vector2f &_size)
{
    Object::size = _size;
    sf::FloatRect local_bounds = Object::sprite.getLocalBounds();

    Object::sprite.setScale(_size.x / local_bounds.width, _size.y / local_bounds.height);
}

/* Getters */
sf::Vector2f Object::get_border_position()
{
    return border->get_position();
}

sf::Vector2f Object::get_border_size()
{
    return border->get_size();
}

const sf::Vector2f &Object::get_position() const
{
    return sprite.getPosition();
}

const sf::Sprite &Object::get_sprite() const
{
    return sprite;
}

const sf::Vector2f &Object::get_size() const
{
    return size;
}

sf::FloatRect Object::get_global_bounds() const
{
    return sprite.getGlobalBounds();
}
