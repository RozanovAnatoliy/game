#ifndef GAME_OBJECT_MANUFACTURE_H
#define GAME_OBJECT_MANUFACTURE_H

#include "object.h"

namespace Game {
    class Object_manufacture {
    public:
        void get_object(Object_type type, Game::Object** object);
    };
}

#endif /* GAME_OBJECT_MANUFACTURE_H */
