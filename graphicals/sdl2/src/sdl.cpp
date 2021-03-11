/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** Sdl.cpp
*/

#include "sdl.hpp"

arcade::Sdl::Sdl()
{
    std::string error;
    SDL_DisplayMode dm;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        error = std::string(SDL_GetError());
        SDL_Quit();
        throw (std::string("SDL Initiation error: " + error));
    }
    memset(&dm, 0, sizeof(dm));
    SDL_GetCurrentDisplayMode(0, &dm);
    this->x = dm.w;
    this->y = dm.h;
    this->window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h, SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RaiseWindow(this->window);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderSetScale(this->renderer, static_cast<float>(this->x) / 1920, static_cast<float>(this->y) / 1080);
    this->past_clock = std::chrono::system_clock::now();
    this->clock_time = 1000/30;
    if (IMG_Init(IMG_INIT_PNG) == -1)
        throw (std::string("Error: bad init PNG"));
    if (IMG_Init(IMG_INIT_JPG) == -1)
        throw (std::string("Error: bad init JPG"));
    if (TTF_Init() == -1)
        throw (std::string("Error: bad init TTF"));
    this->font = TTF_OpenFont("./assets/arcade.ttf", 20);
    if (this->font == NULL)
        throw (std::string("Error: font bad opened"));
}

void arcade::Sdl::destructor()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    IMG_Quit();
    TTF_CloseFont(this->font);
    TTF_Quit();
    SDL_Quit();
}

char arcade::Sdl::keyEvent()
{
    if (this->event.key.keysym.sym == SDLK_a)
        return (97);
    if (this->event.key.keysym.sym == SDLK_b)
        return (98);
    if (this->event.key.keysym.sym == SDLK_c)
        return (99);
    if (this->event.key.keysym.sym == SDLK_d)
        return (100);
    if (this->event.key.keysym.sym == SDLK_e)
        return (101);
    if (this->event.key.keysym.sym == SDLK_f)
        return (102);
    if (this->event.key.keysym.sym == SDLK_g)
        return (103);
    if (this->event.key.keysym.sym == SDLK_h)
        return (104);
    if (this->event.key.keysym.sym == SDLK_i)
        return (105);
    if (this->event.key.keysym.sym == SDLK_j)
        return (106);
    if (this->event.key.keysym.sym == SDLK_k)
        return (107);
    if (this->event.key.keysym.sym == SDLK_l)
        return (108);
    if (this->event.key.keysym.sym == SDLK_m)
        return (109);
    if (this->event.key.keysym.sym == SDLK_n)
        return (110);
    if (this->event.key.keysym.sym == SDLK_o)
        return (111);
    if (this->event.key.keysym.sym == SDLK_p)
        return (112);
    if (this->event.key.keysym.sym == SDLK_q)
        return (113);
    if (this->event.key.keysym.sym == SDLK_r)
        return (114);
    if (this->event.key.keysym.sym == SDLK_s)
        return (115);
    if (this->event.key.keysym.sym == SDLK_t)
        return (116);
    if (this->event.key.keysym.sym == SDLK_u)
        return (117);
    if (this->event.key.keysym.sym == SDLK_v)
        return (118);
    if (this->event.key.keysym.sym == SDLK_w)
        return (119);
    if (this->event.key.keysym.sym == SDLK_x)
        return (120);
    if (this->event.key.keysym.sym == SDLK_y)
        return (121);
    if (this->event.key.keysym.sym == SDLK_z)
        return (122);
    if (this->event.key.keysym.sym == SDLK_ESCAPE)
        return (27);
    if (this->event.key.keysym.sym == SDLK_RETURN)
        return (10);
    if (this->event.key.keysym.sym == SDLK_KP_1)
        return (49);
    if (this->event.key.keysym.sym == SDLK_KP_2)
        return (50);
    if (this->event.key.keysym.sym == SDLK_KP_3)
        return (51);
    if (this->event.key.keysym.sym == SDLK_KP_4)
        return (52);
    if (this->event.key.keysym.sym == SDLK_KP_5)
        return (53);
    if (this->event.key.keysym.sym == SDLK_KP_6)
        return (54);
    if (this->event.key.keysym.sym == SDLK_KP_7)
        return (55);
    if (this->event.key.keysym.sym == SDLK_KP_8)
        return (56);
    if (this->event.key.keysym.sym == SDLK_KP_9)
        return (57);
    if (this->event.key.keysym.sym == SDLK_DOWN)
        return (-32);
    if (this->event.key.keysym.sym == SDLK_UP)
        return (-33);
    if (this->event.key.keysym.sym == SDLK_LEFT)
        return (-34);
    if (this->event.key.keysym.sym == SDLK_RIGHT)
        return (-35);
    return (-1);
}

char arcade::Sdl::getEvent()
{
    while (SDL_PollEvent(&this->event)) {
        if (this->event.type == SDL_QUIT)
            return (0);
        if (this->event.type == SDL_KEYUP)
            return (-1);
        if (this->event.type == SDL_KEYDOWN)
            return (this->keyEvent());
    }
    return (-1);
}


void arcade::Sdl::refresh(void)
{
    SDL_RenderPresent(this->renderer);
    SDL_RenderClear(this->renderer);
}

int arcade::Sdl::getWindowHeight()
{
    return (this->y);
}

int arcade::Sdl::getWindowWidth()
{
    return (this->x);
}

bool arcade::Sdl::clockDisplay()
{
    std::chrono::duration<double, std::milli> delta = std::chrono::system_clock::now() - this->past_clock;

    if (delta.count() >= this->clock_time) {
        this->past_clock = std::chrono::system_clock::now();
        return (true);
    } else {
        return (false);
    }
}

SDL_Texture *arcade::Sdl::create_texture(const std::string &filename)
{
    SDL_Texture *tmp_texture = NULL;
    SDL_Surface *image = NULL;

    image = IMG_Load(filename.c_str());
    if(!image)
        throw(std::string("Error while loading the file: ") + std::string(SDL_GetError()));
    tmp_texture = SDL_CreateTextureFromSurface(this->renderer, image);
    SDL_FreeSurface(image);
    if (!tmp_texture)
        throw(std::string("Error while loading the texture: ") + std::string(SDL_GetError()));
    return (tmp_texture);
}

void arcade::Sdl::create_text(display_t display)
{
    static SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(this->font, display.ascii.c_str(), white);
    SDL_Texture* tmp_texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect sdlRect;
    int w = 0;
    int h = 0;

    SDL_FreeSurface(surfaceMessage);
    SDL_QueryTexture(tmp_texture, NULL, NULL, &w, &h);
    #ifdef CENTER_ORIGIN
        display.x = display.x * 34 - 34/3 + 1920 / 2;
        display.y = display.y * 34 - 34/3 + 1080 / 2;
    #endif
    sdlRect.x = static_cast<int>(display.x);
    sdlRect.y = static_cast<int>(display.y);
    sdlRect.w = static_cast<int>(w);
    sdlRect.h = static_cast<int>(h);
    if (SDL_RenderCopy(this->renderer, tmp_texture, NULL, &sdlRect) != 0)
        throw std::runtime_error(SDL_GetError());
    SDL_DestroyTexture(tmp_texture);
}

void arcade::Sdl::drawTexture(SDL_Texture *texture, display_t display)
{
    SDL_Rect sdlRect;
    int w = 0;
    int h = 0;

    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    #ifdef CENTER_ORIGIN
        display.x = display.x * 34 - w / 2 + 1920 / 2;
        display.y = display.y * 34 - h / 2 + 1080 / 2;
    #endif
    sdlRect.x = static_cast<int>(display.x);
    sdlRect.y = static_cast<int>(display.y);
    sdlRect.w = static_cast<int>(w);
    sdlRect.h = static_cast<int>(h);
    if (SDL_RenderCopy(this->renderer, texture, NULL, &sdlRect) != 0)
        throw std::runtime_error(SDL_GetError());
}

void arcade::Sdl::print(display_t &display)
{
    SDL_Texture *texture = NULL;

    if (!display.isPrint)
        return;
    if (display.image.length() < 1) {
        if (display.ascii.length() > 0)
            this->create_text(display);
        return;
    }
    if (this->sprite.find(display.image) == this->sprite.end()) {
        texture = this->create_texture(display.image);
        this->sprite.insert(std::make_pair(display.image, texture));
    } else
        texture = this->sprite[display.image];
    this->drawTexture(texture, display);
}

extern "C" arcade::IGraphics *create()
{
    return (new arcade::Sdl());
}