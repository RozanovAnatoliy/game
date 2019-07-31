#include "interface_object.h"

Game::Interface_object::Interface_object(sf::Vector2f &_position, sf::Vector2f &_size, float _indent)
{
    Interface_object::object = nullptr;
    Interface_object::position = _position;
    Interface_object::size = _size;
    Interface_object::indent = _indent;

    float picture_size = _size.y - 2.0f * bounds_thickness;
    sf::Vector2f picture_position = _position + sf::Vector2f(bounds_thickness, bounds_thickness);
    picture.init(picture_position, picture_size, bounds_thickness);

    sf::Vector2f information_position(picture_position.x + bounds_thickness + picture_size, picture_position.y);
    sf::Vector2f information_size((_size.x - picture_size - bounds_thickness) * 0.5f, picture_size);
    information.init(information_position, information_size, bounds_thickness);
}


void Game::Interface_object::draw(sf::RenderWindow &window)
{
    picture.draw(window);
    information.draw(window);
}


void Game::Interface_object::set_object(Game::Object *_object)
{
    Interface_object::object = _object;

    picture.set_sprite(object->get_sprite());
    information.set_object_name(object->object_name);
}


/* Cell */
void Game::Interface_object_cell::cell_init(sf::Vector2f &_position, sf::Vector2f &_size, float _bounds_thickness)
{
    Interface_object_cell::position = _position;
    Interface_object_cell::size = _size;
    Interface_object_cell::bounds_thickness = _bounds_thickness;

    bounds.setPosition(position);
    bounds.setSize(size);
    bounds.setOutlineColor(bounds_color);
    bounds.setFillColor(sf::Color(0, 0, 0, 0));
    bounds.setOutlineThickness(bounds_thickness);
}

void Game::Interface_object_cell::cell_draw(sf::RenderWindow &window)
{
    window.draw(bounds);
}

const sf::Vector2f &Game::Interface_object_cell::get_position() const
{
    return position;
}

const sf::Vector2f &Game::Interface_object_cell::get_size() const
{
    return size;
}


/* Picture */
void Game::Interface_object_picture::init(sf::Vector2f &_position, float _size, float _bounds_thickness)
{
    sf::Vector2f cell_size = sf::Vector2f(_size, _size);
    cell_init(_position, cell_size, _bounds_thickness);
}

void Game::Interface_object_picture::set_sprite(const sf::Sprite &_sprite)
{
    Interface_object_picture::sprite = _sprite;

    sf::FloatRect local_bounds = sprite.getLocalBounds();
    sf::Vector2f position = get_position();
    sf::Vector2f size = get_size();

    sprite.setPosition(position);
    sprite.setScale(size.x / local_bounds.width, size.y / local_bounds.height);
}

void Game::Interface_object_picture::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
    cell_draw(window);
}


/* Text information */
void Game::Interface_object_information::init(sf::Vector2f &_position, sf::Vector2f &_size, float _bounds_thickness)
{
    cell_init(_position, _size, _bounds_thickness);

    font.loadFromFile("../fonts/fonts_online.otf");

    title.setString("Object Information");
    title.setFont(font);
    title.setFillColor(color);
    title.setCharacterSize(title_character_size);

    sf::Vector2f position = sf::Vector2f(_position.x + (_size.x - title.getLocalBounds().width) * 0.5f, _position.y);
    title.setPosition(position);

    next_text_position = sf::Vector2f(_position.x + indent,
                                   _position.y + title.getLocalBounds().height + 5.0f * indent);
}

void Game::Interface_object_information::draw(sf::RenderWindow &window)
{
    window.draw(title);
    window.draw(object_name);
    cell_draw(window);
}

void Game::Interface_object_information::set_object_name(const std::string &_object_name)
{
    object_name.setString(std::string("Object name: ") + _object_name);
    object_name.setFont(font);
    object_name.setCharacterSize(character_size);
    object_name.setFillColor(color);
    object_name.setPosition(next_text_position);
}
