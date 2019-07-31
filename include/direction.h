#ifndef GAME_DIRECTION_H
#define GAME_DIRECTION_H

namespace Utils {
    class Direction {
    public:
        enum {
            DOWN = 0,
            LEFT,
            RIGHT,
            UP,
            END
        };

        Direction() : value(Direction::DOWN) {};

        void invert();

        void set_direction(int direction);
        void rand(int except = -1);

        int value;
    };
}

#endif /* GAME_DIRECTION_H */
