#include "snake.h"
////////////////////////////////////////
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
_width(width), _height(height), body(width*height){
initialize();
}


void Snake::initialize() {
    body.current_direction = body.prev_direction = Direction::DIR_RIGHT;
    this->body.length = 4;
    for (int i = 0; i < _size; i++){
        this->body.position[i][X_] = 0;
        this->body.position[i][Y_] = 0;
    }
    new_food_position();
}

void Snake::new_food_position() {
        food.x = rand() % _width;
        food.y = rand() % _height;
        if (is_food_inside()){
            return;
        }
}
//// there must be mistake
bool Snake::is_food_inside() {
    for(int i = 0; i < body.length; i++){
        if (food.y == body.position[i][Y_] && food.x == body.position[i][X_]){
            return true;
        }
    }
    return false;
}

void Snake::step() {
    for(int i = body.length; i > 0; i-- ){
        body.position[i][X_] = body.position[i - 1][X_];
        body.position[i][Y_] = body.position[i - 1][Y_];
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
    if (body.position[0][X_] == _width){
        body.position[0][X_] = 0;
    } else if (body.position[0][X_] == -1) {
        body.position[0][X_] = _width - 1;
    } else if (body.position[0][Y_] == _height){
        body.position[0][Y_] = 0;
    } else if (body.position[0][Y_] == -1){
        body.position[0][Y_] = _height - 1;
    }
    /// eating
    if(food.x == body.position[0][X_] && food.y == body.position[0][Y_]){
        new_food_position();
        body.length++;
    }

    ///eating herself
    for(int i = 1; i < body.length; i++){
        if (body.position[0][X_] == body.position[i][X_] && body.position[0][Y_] == body.position[i][Y_]){
            initialize(); /// aka death TODO
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
