#ifndef GAME_HOUSE_H
#define GAME_HOUSE_H

#include "object.h"
#include "border_rect.h"

namespace Game {

    class House : public Object
    {
    public:
        House();
        House(sf::Vector2f _position);
        void init();

        void draw(sf::RenderWindow &window) override;
    private:
        static const std::string texture_file_name;
        static const float scale;
    };
}

#endif /* GAME_HOUSE_H */
