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

void render(sf::RenderWindow &window, Game::View &view, std::vector<Game::Object *> &objects,
            Game::Interface &interface)
{
    window.setView(view.get_view());
    window.clear(sf::Color::Black);

    for (Game::Object *object : objects) {
        object->draw(window);
    }

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

void rendering_thread(Game::Game_state &game, std::vector<Game::Object *> &objects, Game::Interface &interface,
                      Game::View &view, sf::RenderWindow &window)
{
    window.setActive(true);
    sf::Clock clock;

    while(window.isOpen()) {
        sf::Time time1 = clock.getElapsedTime();

        game.lock_objects_mutex();
        update(game, objects, interface, game.sec_per_frame, window);
        render(window, view, objects, interface);
        game.unlock_objects_mutex();

        sf::Time time2 = clock.restart();
        float elapsed_time = time2.asSeconds() - time1.asSeconds();
        if (elapsed_time < game.sec_per_frame) {
            auto sleep_time = (long long) ((game.sec_per_frame - elapsed_time) * 1000000000.0f);
            std::this_thread::sleep_for(std::chrono::nanoseconds(sleep_time));
        }
    }
}

void handle_events(Game::Game_state &game, std::vector<Game::Object *> &objects, Game::Interface &interface,
                   Game::View &view, sf::RenderWindow &window)
{
    while(window.isOpen()) {
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
    }
}

int main()
{
    std::vector<Game::Object *> objects;

    sf::RenderWindow window(sf::VideoMode(Game::Game_state::width, Game::Game_state::height), "My Windows");
    window.setActive(false);

    std::vector<Game::Object *> objects;
    Game::Game_state game(objects, window);

    sf::Vector2f windows_size = game.get_window_size();

    Game::Person person;
    Game::House house(sf::Vector2f(100., 100.));
    Game::Interface interface(sf::Vector2f(0.0f, Game::Game_state::height * 0.7f),
                              sf::Vector2f((float) Game::Game_state::width, (float) Game::Game_state::height * 0.3f));

    Game::View view(windows_size);
    window.setView(view.get_view());

    objects.push_back(&house);
    objects.push_back(&person);
    objects.push_back(&interface);

    std::thread thread_game(rendering_thread, std::ref(game), std::ref(objects), std::ref(interface),
                            std::ref(view), std::ref(window));
    thread_game.detach();

    handle_events(game, objects, interface, view, window);

    return 0;
}
