#include "border_rect.h"

using namespace Game;

Border_rect::Border_rect()
{
    this->position = sf::Vector2f(0.f, 0.f);
    this->size = sf::Vector2f(0.f, 0.f);

    this->color = this->default_color;

    lines_init();
}

Border_rect::Border_rect(sf::Vector2f _position, sf::Vector2f _size)
{
    this->position = _position;
    this->size = _size;

    this->color = this->default_color;

    lines_init();
}

void Border_rect::draw(sf::RenderWindow &window)
{
    if (Border_rect::need_draw) {
        window.draw(line_up, 2, sf::Lines);
        window.draw(line_down, 2, sf::Lines);
        window.draw(line_left, 2, sf::Lines);
        window.draw(line_right, 2, sf::Lines);
    }
}

void Border_rect::lines_init()
{
    sf::Vertex point1(position);
    sf::Vertex point2(sf::Vector2f(position.x + size.x, position.y));
    sf::Vertex point3(sf::Vector2f(position.x + size.x, position.y + size.y));
    sf::Vertex point4(sf::Vector2f(position.x, position.y + size.y));

    this->line_up[0] = point1;
    this->line_up[1] = point2;

    this->line_down[0] = point3;
    this->line_down[1] = point4;

    this->line_left[0] = point1;
    this->line_left[1] = point4;

    this->line_right[0] = point2;
    this->line_right[1] = point3;

    line_up->color = this->color;
    line_down->color = this->color;
    line_left->color = this->color;
    line_right->color = this->color;
}


void Border_rect::update_position(sf::Vector2f _position)
{
    this->position = _position;
    lines_init();
}

void Border_rect::update_size(sf::Vector2f _size)
{
    this->size = _size;
    lines_init();
}


const sf::Vector2f &Border_rect::get_position() const
{
    return position;
}

const sf::Vector2f &Border_rect::get_size() const
{
    return size;
}

const sf::Color &Border_rect::get_default_color() const
{
    return default_color;
}

void Border_rect::need_to_draw(bool is_need, sf::Color _color)
{
    this->need_draw = is_need;
    this->color = _color;

    for (int i = 0; i < 2; i++) {
        line_up[i].color = this->color;
        line_down[i].color = this->color;
        line_left[i].color = this->color;
        line_right[i].color = this->color;
    }
}
