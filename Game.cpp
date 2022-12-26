#include <stdexcept>
#include "Game.h"


Game::Game(int size, int width, int height) : cell_size_(size), width_(width), height(height), snake_(size, width, height),
                                               is_paused(false), working(true), food(width, height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
        throw std::runtime_error("SDL_INIT_VIDEO error");
    }
    window_width_ = (width * cell_size_) + 1;
    window_height_ = (height * cell_size_) + 1;
    m_window = SDL_CreateWindow("Snake",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                window_width_,
                                window_height_,
                                SDL_WINDOW_OPENGL);
    if (m_window == NULL){
        throw std::runtime_error("window is null");
    }

    m_renderer_ = SDL_CreateRenderer(m_window,
                                     -1,
                                     SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer_ == NULL){
        throw std::runtime_error("window renderer is null");
    }
    step_timer_ = SDL_AddTimer(50, this->sdl_timer_callback, nullptr);
}

int Game::HandleEvents() {
    SDL_Event e;
    SDL_Event r;
    while(SDL_PollEvent(&e)){
        switch (e.type) {
            case SDL_QUIT: {
                escape();
            }
            case SDL_USEREVENT: {
                if (!is_paused) snake_.step();
                break;
            }
            case SDL_KEYDOWN: {
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE: {
                        escape();
                    }
                    case SDL_SCANCODE_P:{
                        is_paused = (!is_paused);
                        break;
                    }
                    case SDL_SCANCODE_R: {
                        snake_.initialize();
                        break;
                    }
                    case SDL_SCANCODE_RIGHT: {
                        snake_.redirection(Direction::DIR_RIGHT);
                        break;
                    }
                    case SDL_SCANCODE_LEFT: {
                        snake_.redirection(Direction::DIR_LEFT);
                        break;
                    }
                    case SDL_SCANCODE_UP: {
                        snake_.redirection(Direction::DIR_UP);
                        break;
                    }
                    case SDL_SCANCODE_DOWN: {
                        snake_.redirection(Direction::DIR_DOWN);
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }

        }
    }
    return 1;
}

void Game::RenderLoop() {
    while (working){
        HandleEvents();
        Render(snake_);
        //Render(snake1);
        UpdateTitle();
        if (!is_paused) ChangeColor();
    }
}

void Game::Render(Snake snake) {
    SDL_SetRenderDrawColor(m_renderer_, grid_background_.r, grid_background_.g, grid_background_.b, grid_background_.a);
    SDL_RenderClear(m_renderer_);
    SDL_SetRenderDrawColor(m_renderer_, line_color_.r, line_color_.g, line_color_.b, line_color_.a);
    ///setka
    for(int x = 0; x < 1 + width_ * cell_size_; x += cell_size_){
        SDL_RenderDrawLine(m_renderer_, x, 0, x, window_height_);
    }
    for(int y = 0; y < 1 + height * cell_size_; y += cell_size_){
        SDL_RenderDrawLine(m_renderer_, 0, y, window_width_, y);
    }

    ///snake_
    SDL_Rect r;
    r.w = r.h = cell_size_;
    SDL_SetRenderDrawColor(m_renderer_, 255,0,0,255);
    r.x = snake.food.x * cell_size_;
    r.y = snake.food.y * cell_size_;
    SDL_SetRenderDrawColor(m_renderer_, food_color.r,food_color.g,food_color.b
                           ,food_color.a);
    SDL_RenderFillRect(m_renderer_, &r);

    r.x = snake.body.position[HEAD_][X_] * cell_size_;
    r.y = snake.body.position[HEAD_][Y_] * cell_size_;
    SDL_SetRenderDrawColor(m_renderer_, head_color.r,head_color.g,head_color.b,head_color.a);
    SDL_RenderFillRect(m_renderer_, &r);

    SDL_SetRenderDrawColor(m_renderer_, body_color.r,body_color.g,body_color.b, body_color.a);
    for(int i = 1; i < snake.body.length; i++){
        r.x = snake.body.position[i][X_] * cell_size_;
        r.y = snake.body.position[i][Y_] * cell_size_;
        SDL_RenderFillRect(m_renderer_, &r);

    }

    SDL_RenderPresent(m_renderer_);
}

void Game::UpdateTitle() {
    std::string title = "record: " + std::to_string(snake_.body.length - 4);
    SDL_SetWindowTitle(m_window, title.c_str());
}

void Game::escape() {
    working = false;
    std::cout << "delete game" << std::endl;
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
    SDL_DestroyRenderer(m_renderer_);
    m_renderer_ = nullptr;
    SDL_Quit();
}

void Game::ChangeColor() {
    if (snake_.body.length % 5 == 0){
        const Uint8 red = rand() % 255;
        const Uint8 green = rand() % 255;
        const Uint8 blue = rand() % 255;
        const Uint8 alpha = rand() % 255;
        body_color = {red, green, blue, alpha};
        food_color = {green, red, blue, alpha};
        grid_background_ = {blue, green, red, alpha};
        line_color_ = {green, blue, red, alpha};
        head_color = {red, blue, green, alpha};
    }
}
