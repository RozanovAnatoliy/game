#ifndef OBJECTS_VIEW_H
#define OBJECTS_VIEW_H

#include "SFML/Graphics.hpp"

namespace Game {
    class View {
    public:
        View(sf::Vector2f &_size);

        void default_view();
        void zoom(float factor);
        const sf::View &get_view() const;

    private:
        sf::View view;
        sf::Vector2f size;
    };
}

#endif /* OBJECTS_VIEW_H */
