#include <iostream>
#include "thread"
#include "mutex"
#include "vector"
#include "fstream"
#include <cstdlib>

enum class Direction {
    DIR_UP,
    DIR_DOWN,
    DIR_RIGHT,
    DIR_LEFT
};

#define X_ 0
#define Y_ 1

class Snake{
public:
    Snake(const size_t size, const size_t width, const size_t height);

    void initialize();

    void new_food_position();

/// there was const in 17:01 3:00 while restricting
    bool is_food_inside();

    void step();

    void redirection(Direction dir);

    size_t _size;
    size_t _width;
    size_t _height;


    class Body{
    public:
        Body(size_t snake_matrix_size);
        ~Body();
        Direction current_direction;
        Direction prev_direction;
        size_t length;
        size_t snake_matrix_size;
        /// position of every snake block
        std::vector<std::vector<int>> position;


    };

    Body body;

    class Food{
    public:
        size_t x;
        size_t y;
    };
    Food food;

private:

};
