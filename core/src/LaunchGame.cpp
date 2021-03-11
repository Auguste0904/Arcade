/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** LaunchGame.cpp
*/

#include "Core.hpp"

void arcade::Core::launchGame(void *handle)
{
    createGame_t *initialize_game = NULL;
    display_t tmp_display;

    initialize_game = (createGame_t *)dlsym(handle, "create");
    if (!(initialize_game))
        throw (arcade::Exception(std::string(dlerror())));
    this->game = initialize_game();
    std::vector<display_t> tmp = {};
    char tmp_event = 0;
    this->event = INPUT_NOTHING;

    while (true) {
        tmp_event = this->graphics->getEvent();
        if (tmp_event != INPUT_NOTHING)
            this->event = tmp_event;
        if (this->event == arcade::CLOSE)
            return;
        if (this->event == -34 || this->event == -35) {
            this->event = INPUT_NOTHING;
            this->switch_lib();
        }
        if (this->event == 'r') {
            this->event = -1;
            this->game->restart();
        }
        if (this->game->speedGame()) {
            this->game->move(this->event);
            this->event = INPUT_NOTHING;
            this->score = this->game->getScore();
            this->getScore();
        }
        if (this->graphics->clockDisplay()) {
            tmp = this->game->getState();
            for (int i = 0; i < static_cast<int>(tmp.size()); i++) {
                tmp_display = tmp[i];
                #ifdef DISPLAY_PERCENT
                tmp_display.x = this->graphics->getWindowWidth() * tmp_display.x;
                tmp_display.y = this->graphics->getWindowHeight() * tmp_display.y;
                #endif
                this->graphics->print(tmp_display);
            }
            this->graphics->refresh();
        }
        if (this->game->getStatus() != arcade::statusGame::INGAME)
            break;
    }
}