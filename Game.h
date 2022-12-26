#pragma once
#include "SDL2/SDL.h"
#include "snake.h"

class Game{
private:
SDL_Window *m_window = nullptr;
SDL_Renderer *m_renderer_ = nullptr;
SDL_TimerID step_timer_;
int width_;
int height;
int cell_size_ = 10;
int window_width_ = 0;
int window_height_ = 0;
bool is_paused;
bool working;

SDL_Color grid_background_ = {22,22,22,255};
SDL_Color line_color_ = {0,100,50,255};

Snake snake;
Snake snake1;

public:
    Game(int size, int width, int height);
    int HandleEvents();
    void Render();
    void RenderLoop();
    void UpdateTitle();
    void escape();

    static Uint32 sdl_timer_callback(Uint32 interval, void *payload){
        SDL_Event e;
        SDL_UserEvent ue;

        (void) payload;
        ue.type = SDL_USEREVENT;
        ue.code = 0;
        ue.data1 = nullptr;
        ue.data2 = nullptr;
        e.type = SDL_USEREVENT;
        e.user = ue;
        SDL_PushEvent(&e);
        return interval;
    }
};