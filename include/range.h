#ifndef GAME_RANGE_H
#define GAME_RANGE_H

namespace Utils {

    template <typename T>
    class Range {
    public:
        Range(T low, T high) : low(low), high(high) {};

        T low;
        T high;
    };

    template <typename T>
    bool in_range(Range<T> &range, T number)
    {
        return range.low <= number && number <= range.high;
    }
}

#endif /* GAME_RANGE_H */
