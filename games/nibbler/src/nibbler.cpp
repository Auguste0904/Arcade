/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** nibbler.cpp
*/

#include "nibbler.hpp"


arcade::Nibbler::Nibbler()
{
    srand(time(NULL));
    this->past_clock = std::chrono::system_clock::now();
    this->time_finish = 90 * 1000;
    this->clock_time = 1000 / 3;
}

void arcade::Nibbler::createComputeMap()
{
    for (int i = 0; i < 19; i++) {
        this->compute_map.push_back({});
        for (int j = 0; j < 19; j++) {
            if (this->map[i][j] != ' ' && this->map[i][j] != 'X')
                this->compute_map[i].push_back(-1);
            else if (this->map[i][j] == ' ')
                this->compute_map[i].push_back(0);
        }
    }
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (this->map[i][j] == 'X') {
                if (i > 19 - 4)
                    throw (std::string("The nibbler is to close to the edge"));
                this->nibbler_node.push_back({arcade::DIR::UP, j, i});
                this->nibbler_node.push_back({arcade::DIR::UP, j, i + 1});
                this->nibbler_node.push_back({arcade::DIR::UP, j, i + 2});
                this->nibbler_node.push_back({arcade::DIR::UP, j, i + 3});
                break;
            }
        }
    }
    this->createApple();
    this->createApple();
}

void arcade::Nibbler::createMap()
{
    std::ifstream file("./assets/map_nibbler.txt");
    std::string tmp("");
    std::string allowed("ABabcdefghijX .");
    std::vector<std::string> tmp_map = {};
    int present = 0;

    if (!file.is_open())
        throw (std::string("Can't open file: ./assets/map_nibbler.txt"));
    while (getline(file, tmp, '\n')) {
        if (tmp.size() != 19)
            throw (std::string("The map width must be a size of 19: ./assets/map_nibbler.txt"));
        for (int i = 0; i < static_cast<int>(tmp.size()); i++) {
            for (present = 0; present < static_cast<int>(allowed.size()); present++) {
                if (tmp[i] == allowed[present])
                    break;
            }
            if (present >= static_cast<int>(allowed.size()))
                throw (std::string("The map contains non-allowed characters"));
        }
        tmp_map.push_back(tmp);
    }
    if (tmp_map.size() != 19)
        throw (std::string("The map height must be a size of 19: ./assets/map_nibbler.txt"));
    this->map = tmp_map;
    file.close();
    this->createComputeMap();
}

std::vector<display_t> &arcade::Nibbler::getInitState()
{
    return (this->getState());
}

arcade::statusGame &arcade::Nibbler::getStatus()
{
    return (this->status);
}

void arcade::Nibbler::displayMap(std::vector<display_t> &tmp)
{
    display_t tmp_display = {"", "", "", "", 0, 0, true};
    float offset_x = -9;
    float offset_y = -9;

    for (int y = 0; y < 19; y++) {
        for (int x = 0; x < 19; x++) {
            // tmp_display = {"", "", "", "assets/debug.png", x + offset_x, y + offset_y, true};
            // tmp.push_back(tmp_display);
            if (this->map[y][x] == '#')
                tmp_display = {"#", "magenta", "", "assets/empty.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'A')
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_horizontal.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'B')
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_vertical.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'e')
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_horizontal_right.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'f')
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_horizontal_left.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'g')
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_vertical_up.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'h')
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_vertical_down.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'a') {
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_horizontal_right.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_vertical_up.png", x + offset_x, y + offset_y, true};
            } else if (this->map[y][x] == 'b') {
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_horizontal_left.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_vertical_up.png", x + offset_x, y + offset_y, true};
            } else if (this->map[y][x] == 'c') {
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_horizontal_left.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_vertical_down.png", x + offset_x, y + offset_y, true};
            } else if (this->map[y][x] == 'd') {
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_horizontal_right.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_vertical_down.png", x + offset_x, y + offset_y, true};
            } else if (this->map[y][x] == 'i') {
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_vertical.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_horizontal_right.png", x + offset_x, y + offset_y, true};
            } else if (this->map[y][x] == 'j') {
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_vertical.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "magenta", "", "assets/map_nibbler_horizontal_left.png", x + offset_x, y + offset_y, true};
            }
            tmp.push_back(tmp_display);
        }
    }
}

void arcade::Nibbler::displaySnake(std::vector<display_t> &tmp)
{
    float offset_x = -9;
    float offset_y = -9;

    for (int i = 0; i < static_cast<int>(this->nibbler_node.size()); i++) {
        if (i == 0) {
            if (this->nibbler_node[i].direction == arcade::DIR::UP)
                tmp.push_back({"^", "red", "", "assets/head_nibbler_up.png", static_cast<float>(this->nibbler_node[i].x + offset_x), static_cast<float>(this->nibbler_node[i].y + offset_y), true});
            else if (this->nibbler_node[i].direction == arcade::DIR::RIGHT)
                tmp.push_back({">", "red", "", "assets/head_nibbler_right.png", static_cast<float>(this->nibbler_node[i].x + offset_x), static_cast<float>(this->nibbler_node[i].y + offset_y), true});
            else if (this->nibbler_node[i].direction == arcade::DIR::DOWN)
                tmp.push_back({"v", "red", "", "assets/head_nibbler_down.png", static_cast<float>(this->nibbler_node[i].x + offset_x), static_cast<float>(this->nibbler_node[i].y + offset_y), true});
            else if (this->nibbler_node[i].direction == arcade::DIR::LEFT)
                tmp.push_back({"<", "red", "", "assets/head_nibbler_left.png", static_cast<float>(this->nibbler_node[i].x + offset_x), static_cast<float>(this->nibbler_node[i].y + offset_y), true});
        } else if (i < static_cast<int>(this->nibbler_node.size() - 1)) {
            tmp.push_back({"O", "red", "", "assets/body_nibbler.png", static_cast<float>(this->nibbler_node[i].x + offset_x), static_cast<float>(this->nibbler_node[i].y + offset_y), true});
        } else {
            if (this->nibbler_node[i].direction == arcade::DIR::UP)
                tmp.push_back({"^", "red", "", "assets/tail_nibbler_up.png", static_cast<float>(this->nibbler_node[i].x + offset_x), static_cast<float>(this->nibbler_node[i].y + offset_y), true});
            else if (this->nibbler_node[i].direction == arcade::DIR::RIGHT)
                tmp.push_back({">", "red", "", "assets/tail_nibbler_right.png", static_cast<float>(this->nibbler_node[i].x + offset_x), static_cast<float>(this->nibbler_node[i].y + offset_y), true});
            else if (this->nibbler_node[i].direction == arcade::DIR::DOWN)
                tmp.push_back({"v", "red", "", "assets/tail_nibbler_down.png", static_cast<float>(this->nibbler_node[i].x + offset_x), static_cast<float>(this->nibbler_node[i].y + offset_y), true});
            else if (this->nibbler_node[i].direction == arcade::DIR::LEFT)
                tmp.push_back({"<", "red", "", "assets/tail_nibbler_left.png", static_cast<float>(this->nibbler_node[i].x + offset_x), static_cast<float>(this->nibbler_node[i].y + offset_y), true});
        }
    }
}

void arcade::Nibbler::createApple()
{
    int x = 0;
    int y = 0;

    while (true) {
        x = rand() % 19;
        y = rand() % 19;
        if (this->compute_map[y][x] == -1)
            continue;
        for (int i = 0; i < static_cast<int>(this->nibbler_node.size()); i++) {
            if (x == this->nibbler_node[i].x && y == this->nibbler_node[i].y)
                continue;
        }
        break;
    }
    this->apple_node.push_back({x, y});
}

std::vector<display_t> &arcade::Nibbler::displayGame()
{
    float offset_x = -9;
    float offset_y = -9;
    display_t score = {"Score : " + std::to_string(this->score), "", "", "", -8, -10, true};
    display_t tmp_time = {"Time left : " + std::to_string(static_cast<int>(round(this->time_finish / 1000 - this->delta.count() / 1000))), "", "", "", -8, -11, true};
    std::vector<display_t> tmp = {score, tmp_time};

    this->displayMap(tmp);
    this->displaySnake(tmp);
    for (int i = 0; i < static_cast<int>(this->apple_node.size()); i++)
        tmp.push_back({"*", "green", "", "assets/apple.png", this->apple_node[i].x + offset_x, this->apple_node[i].y + offset_y, true});
    this->state = tmp;
    return (this->state);
}

std::vector<display_t> &arcade::Nibbler::displayMenu()
{
    static display_t title = {"NIBBLER", "magenta", "", "assets/nibbler_logo.png", 0, -10, true};
    static display_t play = {"Play", "yellow", "", "", 0, 2, true};
    static display_t quit = {"Quit", "yellow", "", "", 0, 5, true};
    static display_t select_display = {">", "green", "", "assets/GreenArrow.png", -2, 0, true};
    static display_t no_select_display = {" ", "", "", "", -2, 0, true};
    std::vector<display_t> tmp = {title, play, quit};

    for (uint8_t i = 0; i <= 1; i++) {
        select_display.y = 2 + i * 3;
        no_select_display.y = 2 + i * 3;
        tmp.push_back((i == this->select) ? select_display : no_select_display);
    }
    this->state = tmp;
    return (this->state);
}

void arcade::Nibbler::clearScreen()
{
    display_t display_clear = {" ", "", "", "", 0, 0, true};

    for (float i = -100; i < 100; i++) {
        for (float j = -100; j < 100; j++) {
            display_clear = {" ", "", "", "", j, i, true};
            this->clear.push_back(display_clear);
        }
    }
}

std::vector<display_t> &arcade::Nibbler::getState()
{
    if (this->clear.size() > 0) {
        this->state = this->clear;
        this->clear = {};
        return (this->state);
    }
    if (this->isGame)
        return (this->displayGame());
    else
        return (this->displayMenu());
}

bool arcade::Nibbler::speedGame()
{
    std::chrono::duration<double, std::milli> delta = std::chrono::system_clock::now() - this->past_clock;

    if (delta.count() >= this->clock_time) {
        this->past_clock = std::chrono::system_clock::now();
        return (true);
    } else {
        return (false);
    }
}

uint64_t arcade::Nibbler::getScore()
{
    return (static_cast<uint64_t>(this->score));
}

void arcade::Nibbler::restart()
{
    this->status = arcade::statusGame::INGAME;
}

void arcade::Nibbler::moveMenu(char input)
{
    if (input == -32 && this->select <= 0)
        this->select += 1;
    if (input == -33 && this->select > 0)
        this->select -= 1;
    if (input == 10 && this->select == 1)
        this->status = arcade::statusGame::WIN;
    if (input == 10 && this->select == 0) {
        this->clearScreen();
        this->isGame = true;
        this->createMap();
    }
}

void arcade::Nibbler::moveSnake()
{
    if (this->direction == arcade::DIR::UP && this->nibbler_node[0].y) {
        this->nibbler_node[0].direction = this->direction;
        this->nibbler_node.insert(this->nibbler_node.begin(), {this->direction, this->nibbler_node[0].x, this->nibbler_node[0].y - 1});
        if (this->grow)
            this->grow = false;
        else
            this->nibbler_node.pop_back();
    } else if (this->direction == arcade::DIR::RIGHT && this->nibbler_node[0].x < 19 - 1) {
        this->nibbler_node[0].direction = this->direction;
        this->nibbler_node.insert(this->nibbler_node.begin(), {this->direction, this->nibbler_node[0].x + 1, this->nibbler_node[0].y});
        if (this->grow)
            this->grow = false;
        else
            this->nibbler_node.pop_back();
    } else if (this->direction == arcade::DIR::DOWN && this->nibbler_node[0].y < 19 - 1) {
        this->nibbler_node[0].direction = this->direction;
        this->nibbler_node.insert(this->nibbler_node.begin(), {this->direction, this->nibbler_node[0].x, this->nibbler_node[0].y + 1});
        if (this->grow)
            this->grow = false;
        else
            this->nibbler_node.pop_back();
    } else if (this->direction == arcade::DIR::LEFT && this->nibbler_node[0].x) {
        this->nibbler_node[0].direction = this->direction;
        this->nibbler_node.insert(this->nibbler_node.begin(), {this->direction, this->nibbler_node[0].x - 1, this->nibbler_node[0].y});
        if (this->grow)
            this->grow = false;
        else
            this->nibbler_node.pop_back();
    }
    if (this->compute_map[this->nibbler_node[0].y][this->nibbler_node[0].x] == -1)
        this->status = arcade::statusGame::LOSE;
    for (int i = 1; i < static_cast<int>(this->nibbler_node.size()); i++) {
        if (this->nibbler_node[0].x == this->nibbler_node[i].x && this->nibbler_node[0].y == this->nibbler_node[i].y)
            this->status = arcade::statusGame::LOSE;
    }
    for (int i = 0; i < static_cast<int>(this->apple_node.size()); i++) {
        if (this->nibbler_node[0].x == this->apple_node[i].x && this->nibbler_node[0].y == this->apple_node[i].y) {
            this->grow = true;
            this->apple_node.erase(this->apple_node.begin() + i);
            this->createApple();
            this->score += 10;
        }
    }
}

void arcade::Nibbler::moveGame(char input)
{
    if (input == 27)
        this->isGame = false;
    if (this->started == false && input == -1)
        return;
    else if (input != -1 && this->started == false) {
        started = true;
        this->start_clock = std::chrono::system_clock::now();
    }
    if (input == 'z' && this->direction != arcade::DIR::DOWN)
        this->direction = arcade::DIR::UP;
    else if (input == 'd' && this->direction != arcade::DIR::LEFT)
        this->direction = arcade::DIR::RIGHT;
    else if (input == 's' && this->direction != arcade::DIR::UP)
        this->direction = arcade::DIR::DOWN;
    else if (input == 'q' && this->direction != arcade::DIR::RIGHT)
        this->direction = arcade::DIR::LEFT;
    this->current_clock = std::chrono::system_clock::now();
    this->delta = this->current_clock - this->start_clock;
    if (this->time_finish - this->delta.count() <= 0)
        this->status = arcade::statusGame::LOSE;
    this->moveSnake();
}

void arcade::Nibbler::move(char input)
{
    static char buffer_input = -1;

    if (buffer_input == input)
        input = -1;
    if (input == 27 && !this->isGame)
        this->status = arcade::statusGame::WIN;
    if (this->isGame)
        this->moveGame(input);
    else
        this->moveMenu(input);
    buffer_input = input;
}

extern "C" arcade::IGames *create()
{
    return (new arcade::Nibbler());
}