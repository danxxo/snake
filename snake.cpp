#include "snake.h"

Snake::Body::Body(size_t snake_matrix_size) : length(4), snake_matrix_size(snake_matrix_size){
    position = std::vector<std::vector<int>>(snake_matrix_size);
    for(int i = 0; i < snake_matrix_size; i++){
        position[i] = std::vector<int>(2);
    }
}

Snake::Body::~Body() {
std::vector<std::vector<int>> a;
position = a;
}

Snake::Snake(const size_t size, const size_t width, const size_t height) : _size(size),
_width(width), _height(height), body(width*height), food(width, height){
initialize();
}


void Snake::initialize() {
    body.current_direction = body.prev_direction = Direction::DIR_RIGHT;
    this->body.length = 4;
    for (int i = 0; i < _size; i++){
        set_position(i, X_, 0);
        set_position(i, Y_, 0);
    }
    new_food_position();
}

void Snake::new_food_position() {
        food.new_food_position();
        if (is_food_inside()){
            return;
        }
}
//// there must be mistake
bool Snake::is_food_inside() {
    for(int i = 0; i < body.length; i++){
        if (food.y == get_position(i, Y_) && food.x == get_position(i, X_)){
            return true;
        }
    }
    return false;
}

void Snake::step() {
    for(int i = body.length; i > 0; i-- ){
        set_position(i, X_, get_position(i-1, X_));
        set_position(i, Y_, get_position(i-1, Y_));
    }

    switch (body.current_direction) {

        case Direction::DIR_UP:
            body.position[0][Y_]--;
            break;
        case Direction::DIR_DOWN:
            body.position[0][Y_]++;
            break;
        case Direction::DIR_RIGHT:
            body.position[0][X_]++;
            break;
        case Direction::DIR_LEFT:
            body.position[0][X_]--;
            break;
    }

    body.prev_direction = body.current_direction;
/// сделать геттер на голову чтобы не писать что-то вроде body.position[___0____][Y_]++;
/// оьбработка телепортации на краях
    if (get_position(HEAD_, X_) == _width){
        set_position(HEAD_, X_, 0);
    } else if (get_position(HEAD_, X_) == -1) {
        set_position(HEAD_, X_, _width - 1);
    } else if (get_position(HEAD_, Y_) == _height){
        set_position(HEAD_, Y_, 0);
    } else if (get_position(HEAD_, Y_) == -1){
        set_position(HEAD_, Y_, _height - 1);
    }
    /// eating
    if(food.x == get_position(HEAD_, X_) && food.y == get_position(HEAD_, Y_)){
        new_food_position();
        body.length++;
    }

    ///eating herself
    for(int i = 1; i < body.length; i++){
        if (get_position(HEAD_, X_) == get_position(i, X_) && get_position(HEAD_, Y_) == get_position(i, Y_)){
            initialize();
        }
    }

}

void Snake::redirection(Direction dir) {
    if (dir == Direction::DIR_RIGHT && body.prev_direction != Direction::DIR_LEFT){
        body.current_direction = Direction::DIR_RIGHT;
    } else if(dir == Direction::DIR_UP && body.prev_direction != Direction::DIR_DOWN){
        body.current_direction = Direction::DIR_UP;
    } else if(dir == Direction::DIR_DOWN && body.prev_direction != Direction::DIR_UP){
        body.current_direction = Direction::DIR_DOWN;
    } else if(dir == Direction::DIR_LEFT && body.prev_direction != Direction::DIR_RIGHT){
        body.current_direction = Direction::DIR_LEFT;
    }
}

int Snake::get_position(int part, int coordinate) {
    return this->body.position[part][coordinate];
}

void Snake::set_position(int part, int coordinate, int value) {
    this->body.position[part][coordinate] = value;
}

///////////////////////////////////////

void Food::new_food_position() {
    this->x = rand() % _width;
    this->y = rand() % _height;
}

Food::Food(const size_t width, const size_t height) : _width(width), _height(height) {

}


