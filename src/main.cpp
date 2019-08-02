#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

#include "SFML/Graphics.hpp"

#include "game.h"
#include "object.h"
#include "person.h"
#include "game.h"
#include "house.h"
#include "interface.h"
#include "view.h"

#include "range.h"

void update(Game::Game_state &game, std::vector<Game::Object *> &objects, Game::Interface &interface,
            float elapsed_time, sf::RenderWindow &window)
{
    sf::Vector2i mouse_pixel_pos = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_position = window.mapPixelToCoords(mouse_pixel_pos);

    for (Game::Object *object : objects) {
        object->update(game, elapsed_time, mouse_position);
    }
}

void render(Game::Game_state &game, sf::RenderWindow &window, Game::View &view, std::vector<Game::Object *> &objects,
            Game::Interface &interface)
{
    window.setView(view.get_view());
    window.clear(sf::Color::Black);

    for (Game::Object *object : objects) {
        object->draw(window);
    }

    /* Game area */
    sf::RectangleShape area;
    float thickness = 2.0f;
    area.setSize(sf::Vector2f((float) game.area_width - 2.0f * thickness,
                                (float) game.area_height - 2.0f * thickness));
    area.setPosition(sf::Vector2f(thickness, thickness));
    area.setFillColor(sf::Color(0, 0, 0, 0));
    area.setOutlineThickness(2.0f);
    window.draw(area);

    window.display();
}

void check_click_on_object(std::vector<Game::Object *> &objects, Game::Interface &interface,
                           sf::Vector2f &mouse_position)
{
    for (Game::Object *object : objects) {
        if (object->contains(mouse_position)) {
            if (object->object_type != Game::Object_type::INTERFACE) {
                interface.set_object_interface(object);
            }
            return;
        }
    }

    interface.set_buildings_interface();
}

void check_pressed_key(Game::View &view, sf::RenderWindow &window, float elapsed_time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        view.move(0.0f, 1.0f * elapsed_time);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        view.move(0.0f, -1.0f * elapsed_time);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        view.move(1.0f * elapsed_time, 0.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        view.move(-1.0f * elapsed_time, 0.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        view.zoom(0.99f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        view.zoom(1.01f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        view.default_view();
    }
}

void handle_events(Game::Game_state &game, std::vector<Game::Object *> &objects, Game::Interface &interface,
                   Game::View &view, sf::RenderWindow &window, float elapsed_time)
{
    sf::Event event;
    while(window.pollEvent(event)) {
        switch (event.type){
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse_pixel_pos = sf::Mouse::getPosition(window);
                    sf::Vector2f mouse_position = window.mapPixelToCoords(mouse_pixel_pos);

                    if (game.state != Game::State::BUILDING_OBJECT) {
                        check_click_on_object(objects, interface, mouse_position);
                    }

                    interface.click_on(game, mouse_position);
                }
                break;
            default:
                break;
        }
    }

    check_pressed_key(view, window, elapsed_time);
}

void game_launch(Game::Game_state &game, std::vector<Game::Object *> &objects, Game::Interface &interface,
                      Game::View &view, sf::RenderWindow &window)
{
    window.setActive(true);
    sf::Clock clock;

    while(window.isOpen()) {
        sf::Time time1 = clock.restart();

        handle_events(game, objects,interface, view, window, time1.asSeconds());
        update(game, objects, interface, time1.asSeconds(), window);
        render(game, window, view, objects, interface);

        float elapsed_time = clock.getElapsedTime().asSeconds();
        if (elapsed_time < game.sec_per_frame) {
            auto sleep_time = (long long) ((game.sec_per_frame - elapsed_time) * 1000000000.0f);
            std::this_thread::sleep_for(std::chrono::nanoseconds(sleep_time));
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "My Windows", sf::Style::Fullscreen);
    window.setActive(false);

    std::vector<Game::Object *> objects;
    Game::Game_state game(objects, window);

    sf::Vector2f windows_size = game.get_window_size();

    Game::Person person;
    Game::House house(sf::Vector2f(100., 100.));
    Game::Interface interface(sf::Vector2f(0.0f, windows_size.y * 0.7f),
                              sf::Vector2f(windows_size.x, windows_size.y * 0.3f));

    Game::View view(game, windows_size);
    window.setView(view.get_view());

    objects.push_back(&house);
    objects.push_back(&person);
    objects.push_back(&interface);

    game_launch(game, objects, interface,view, window);
    return 0;
}
