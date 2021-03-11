/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** pacman.cpp
*/

#include "pacman.hpp"


arcade::Pacman::Pacman()
{
    srand(time(NULL));
    this->past_clock = std::chrono::system_clock::now();
    this->time_finish = 180 * 1000;
    this->clock_time = 1000 / 22;
    this->time_animate = 1000 / 5;
    this->animation_clock = std::chrono::system_clock::now();
    this->animation_status = 0;
}

void arcade::Pacman::moveGhost()
{
    std::chrono::duration<double, std::milli> delta_tmp = std::chrono::system_clock::now() - this->ghost_clock;
    int tmp_x = 0;
    int tmp_y = 0;
    float tempo_x = 0;
    float tempo_y = 0;
    std::vector<arcade::DIR> possibility;
    bool found = false;
    float speed = 0.2;

    if (this->ghosted && delta_tmp.count() >= 10000)
        this->ghosted = false;
    if (ghosted)
        speed = 0.1;
    this->x = round(this->x * 10) / 10;
    this->y = round(this->y * 10) / 10;
    for (int i = 0; i < static_cast<int>(this->ghost.size()); i++) {
        // if (delta.count() < this->ghost[i].time_spawn)
        //     continue;
        tempo_x = round(this->ghost[i].x * 10) / 10;
        tempo_y = round(this->ghost[i].y * 10) / 10;
        tmp_x = tempo_x;
        tmp_y = tempo_y;
        possibility = {};
        found = false;
        this->ghost[i].x = tempo_x;
        this->ghost[i].y = tempo_y;
        if (this->ghost[i].x == this->x && this->ghost[i].y == this->y) {
            if (this->ghosted == false)
                this->status = arcade::statusGame::LOSE;
        }
        if (static_cast<float>(tmp_x) == tempo_x && static_cast<float>(tmp_y) == tempo_y) {
            if (this->ghost[i].y && this->compute_map[this->ghost[i].y - 1][this->ghost[i].x] != -1)
                possibility.push_back(arcade::DIR::UP);
            if (this->ghost[i].x < static_cast<int>(this->compute_map[this->ghost[i].y].size()) - 1 && this->compute_map[this->ghost[i].y][this->ghost[i].x + 1] != -1)
                possibility.push_back(arcade::DIR::RIGHT);
            if (this->ghost[i].y < static_cast<int>(this->compute_map.size()) - 1  && this->compute_map[this->ghost[i].y + 1][this->ghost[i].x] != -1)
                possibility.push_back(arcade::DIR::DOWN);
            if (this->ghost[i].x && this->compute_map[this->ghost[i].y][this->ghost[i].x - 1] != -1)
                possibility.push_back(arcade::DIR::LEFT);
            for (int j = 0; j < static_cast<int>(possibility.size()); j++) {
                if (this->ghost[i].orientation == possibility[j])
                    found = true;
            }
            if (possibility.size()) {
                if (found != true)
                    this->ghost[i].orientation = possibility[rand() % possibility.size()];
                if (this->ghost[i].orientation == arcade::DIR::LEFT)
                    this->ghost[i].x -= speed;
                else if (this->ghost[i].orientation == arcade::DIR::RIGHT)
                    this->ghost[i].x += speed;
                else if (this->ghost[i].orientation == arcade::DIR::UP)
                    this->ghost[i].y -= speed;
                else if (this->ghost[i].orientation == arcade::DIR::DOWN)
                    this->ghost[i].y += speed;
            }
        } else {
            if (this->ghost[i].orientation == arcade::DIR::LEFT)
                this->ghost[i].x -= speed;
            else if (this->ghost[i].orientation == arcade::DIR::RIGHT)
                this->ghost[i].x += speed;
            else if (this->ghost[i].orientation == arcade::DIR::UP)
                this->ghost[i].y -= speed;
            else if (this->ghost[i].orientation == arcade::DIR::DOWN)
                this->ghost[i].y += speed;
        }
        tempo_x = round(this->ghost[i].x * 10) / 10;
        tempo_y = round(this->ghost[i].y * 10) / 10;
        tmp_x = tempo_x;
        tmp_y = tempo_y;
        possibility = {};
        found = false;
        this->ghost[i].x = tempo_x;
        this->ghost[i].y = tempo_y;
        if (this->ghost[i].x == this->x && this->ghost[i].y == this->y) {
            if (this->ghosted == false)
                this->status = arcade::statusGame::LOSE;
            else {
                this->score += 13;
                this->ghost[i].x = this->spawn_x;
                this->ghost[i].y = this->spawn_y;
                this->ghost[i].orientation = arcade::DIR::UP;
            }
        }
    }
}

void arcade::Pacman::createComputeMap()
{
    int i = 0;
    int j = 0;

    for (; i < static_cast<int>(this->map.size()); i++) {
        this->compute_map.push_back({});
        for (j = 0; j < static_cast<int>(this->map[i].size()); j++) {
            if (this->map[i][j] != ' ' && this->map[i][j] != 'X' && this->map[i][j] != 'O' && this->map[i][j] != '.' && this->map[i][j] != '-')
                this->compute_map[i].push_back(-1);
            else
                this->compute_map[i].push_back(0);
            if (this->map[i][j] == 'X') {
                this->x = static_cast<float>(j);
                this->y = static_cast<float>(i);
            } else if (this->map[i][j] == ',') {
                this->spawn_x = static_cast<float>(j);
                this->spawn_y = static_cast<float>(i);
            }
        }
        if (i && this->compute_map[i].size() != this->compute_map[i - 1].size())
            throw (std::string("The map isn't correct"));
    }
    if (i <= 7 || j <= 7)
        throw (std::string("The map is too small"));
    this->ghost.push_back({this->spawn_x, this->spawn_y, "yellow", 2, arcade::DIR::UP});
    this->ghost.push_back({this->spawn_x, this->spawn_y, "red", 5, arcade::DIR::UP});
    this->ghost.push_back({this->spawn_x, this->spawn_y, "pink", 10, arcade::DIR::UP});
    this->ghost.push_back({this->spawn_x, this->spawn_y, "cyan", 17, arcade::DIR::UP});
}

void arcade::Pacman::createMap()
{
    std::ifstream file("./assets/map_pacman.txt");
    std::string tmp("");
    std::string allowed("ABabcdefghijklX-O .,");
    std::vector<std::string> tmp_map = {};
    int present = 0;

    this->ghost_clock = std::chrono::system_clock::now();
    if (!file.is_open())
        throw (std::string("Can't open file: ./assets/map_pacman.txt"));
    while (getline(file, tmp, '\n')) {
        // if (tmp.size() != 19)
        //     throw (std::string("The map width must be a size of 19: ./assets/map_pacman.txt"));
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
    // if (tmp_map.size() != 19)
    //     throw (std::string("The map height must be a size of 19: ./assets/map_pacman.txt"));
    this->map = tmp_map;
    file.close();
    this->createComputeMap();
}

std::vector<display_t> &arcade::Pacman::getInitState()
{
    return (this->getState());
}

arcade::statusGame &arcade::Pacman::getStatus()
{
    return (this->status);
}

void arcade::Pacman::displayMap(std::vector<display_t> &tmp)
{
    display_t tmp_display = {"", "", "", "", 0, 0, true};
    float offset_x = -10;
    float offset_y = -11;

    for (int y = 0; y < static_cast<int>(this->map.size()); y++) {
        for (int x = 0; x < static_cast<int>(this->map[y].size()); x++) {
            // tmp_display = {"", "", "", "assets/debug.png", x + offset_x, y + offset_y, true};
            // tmp.push_back(tmp_display);
            if (this->map[y][x] == '#')
                tmp_display = {"#", "blue", "", "assets/empty.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'A')
                tmp_display = {"#", "blue", "", "assets/map_pacman_horizontal.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'B')
                tmp_display = {"#", "blue", "", "assets/map_pacman_vertical.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'e')
                tmp_display = {"#", "blue", "", "assets/map_pacman_horizontal_right.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'f')
                tmp_display = {"#", "blue", "", "assets/map_pacman_horizontal_left.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'g')
                tmp_display = {"#", "blue", "", "assets/map_pacman_vertical_up.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'h')
                tmp_display = {"#", "blue", "", "assets/map_pacman_vertical_down.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == '.')
                tmp_display = {".", "yellow", "", "assets/food_pacman.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'O')
                tmp_display = {"o", "yellow", "", "assets/super_food_pacman.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == '-')
                tmp_display = {"-", "red", "", "assets/red_fence.png", x + offset_x, y + offset_y, true};
            else if (this->map[y][x] == 'a') {
                tmp_display = {"#", "blue", "", "assets/map_pacman_horizontal_right.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "blue", "", "assets/map_pacman_vertical_up.png", x + offset_x, y + offset_y, true};
            } else if (this->map[y][x] == 'b') {
                tmp_display = {"#", "blue", "", "assets/map_pacman_horizontal_left.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "blue", "", "assets/map_pacman_vertical_up.png", x + offset_x, y + offset_y, true};
            } else if (this->map[y][x] == 'c') {
                tmp_display = {"#", "blue", "", "assets/map_pacman_horizontal_left.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "blue", "", "assets/map_pacman_vertical_down.png", x + offset_x, y + offset_y, true};
            } else if (this->map[y][x] == 'd') {
                tmp_display = {"#", "blue", "", "assets/map_pacman_horizontal_right.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "blue", "", "assets/map_pacman_vertical_down.png", x + offset_x, y + offset_y, true};
            } else if (this->map[y][x] == 'i') {
                tmp_display = {"#", "blue", "", "assets/map_pacman_vertical.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "blue", "", "assets/map_pacman_horizontal_right.png", x + offset_x, y + offset_y, true};
            } else if (this->map[y][x] == 'j') {
                tmp_display = {"#", "blue", "", "assets/map_pacman_vertical.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "blue", "", "assets/map_pacman_horizontal_left.png", x + offset_x, y + offset_y, true};
            } else if (this->map[y][x] == 'k') {
                tmp_display = {"#", "blue", "", "assets/map_pacman_horizontal.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "blue", "", "assets/map_pacman_vertical_up.png", x + offset_x, y + offset_y, true};
            } else if (this->map[y][x] == 'l') {
                tmp_display = {"#", "blue", "", "assets/map_pacman_horizontal.png", x + offset_x, y + offset_y, true};
                tmp.push_back(tmp_display);
                tmp_display = {"#", "blue", "", "assets/map_pacman_vertical_down.png", x + offset_x, y + offset_y, true};
            }
            tmp.push_back(tmp_display);
        }
    }
}

void arcade::Pacman::displayGhosts(std::vector<display_t> &tmp)
{
    float offset_x = -10;
    float offset_y = -11;

    for (int i = 0; i < static_cast<int>(this->ghost.size()); i++) {
        if (this->ghosted)
            tmp.push_back({"M", "blue", "", "assets/blue_ghost.png", this->ghost[i].x + offset_x, this->ghost[i].y + offset_y, true});
        else
            tmp.push_back({"M", this->ghost[i].color, "", "assets/" + this->ghost[i].color + "_ghost.png", this->ghost[i].x + offset_x, this->ghost[i].y + offset_y, true});
    }
}

void arcade::Pacman::displaySnake(std::vector<display_t> &tmp)
{
    float offset_x = -10;
    float offset_y = -11;
    std::chrono::duration<double, std::milli> delta = std::chrono::system_clock::now() - this->animation_clock;

    if (delta.count() >= this->time_animate) {
        this->animation_status = (this->animation_status + 1 >= 3) ? 0 : this->animation_status + 1;
        this->animation_clock = std::chrono::system_clock::now();
    }
    this->displayGhosts(tmp);
    if (this->animation_status == 0) {
        if (this->direction == arcade::DIR::UP || this->direction == arcade::DIR::DOWN)
            tmp.push_back({"|", "yellow", "", "assets/closed_pacman.png", static_cast<float>(this->x + offset_x), static_cast<float>(this->y + offset_y), true});
        else
            tmp.push_back({"-", "yellow", "", "assets/closed_pacman.png", static_cast<float>(this->x + offset_x), static_cast<float>(this->y + offset_y), true});
    } else if (this->animation_status == 1) {
        if (this->direction == arcade::DIR::LEFT)
            tmp.push_back({">", "yellow", "", "assets/normal_pacman_left.png", static_cast<float>(this->x + offset_x), static_cast<float>(this->y + offset_y), true});
        else if (this->direction == arcade::DIR::RIGHT)
            tmp.push_back({"<", "yellow", "", "assets/normal_pacman_right.png", static_cast<float>(this->x + offset_x), static_cast<float>(this->y + offset_y), true});
        else if (this->direction == arcade::DIR::UP)
            tmp.push_back({"v", "yellow", "", "assets/normal_pacman_up.png", static_cast<float>(this->x + offset_x), static_cast<float>(this->y + offset_y), true});
        else
            tmp.push_back({"^", "yellow", "", "assets/normal_pacman_down.png", static_cast<float>(this->x + offset_x), static_cast<float>(this->y + offset_y), true});
    } else {
        if (this->direction == arcade::DIR::LEFT)
            tmp.push_back({"}", "yellow", "", "assets/opened_pacman_left.png", static_cast<float>(this->x + offset_x), static_cast<float>(this->y + offset_y), true});
        else if (this->direction == arcade::DIR::RIGHT)
            tmp.push_back({"{", "yellow", "", "assets/opened_pacman_right.png", static_cast<float>(this->x + offset_x), static_cast<float>(this->y + offset_y), true});
        else if (this->direction == arcade::DIR::UP)
            tmp.push_back({"V", "yellow", "", "assets/opened_pacman_up.png", static_cast<float>(this->x + offset_x), static_cast<float>(this->y + offset_y), true});
        else
            tmp.push_back({"^", "yellow", "", "assets/opened_pacman_down.png", static_cast<float>(this->x + offset_x), static_cast<float>(this->y + offset_y), true});
    }
}

std::vector<display_t> &arcade::Pacman::displayGame()
{
    display_t score = {"Score : " + std::to_string(this->score), "magenta", "", "", -8, -12, true};
    display_t tmp_time = {"Time left : " + std::to_string(static_cast<int>(round(this->time_finish / 1000 - this->delta.count() / 1000))), "", "", "", -8, -13, true};
    std::vector<display_t> tmp = {score, tmp_time};

    this->displayMap(tmp);
    this->displaySnake(tmp);
    this->state = tmp;
    return (this->state);
}

std::vector<display_t> &arcade::Pacman::displayMenu()
{
    static display_t title = {"Pacman", "yellow", "", "assets/pacman_logo.png", 0, -10, true};
    static display_t play = {"Play", "", "", "", 0, 2, true};
    static display_t quit = {"Quit", "", "", "", 0, 5, true};
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

void arcade::Pacman::clearScreen()
{
    display_t display_clear = {" ", "", "", "", 0, 0, true};

    for (float i = -100; i < 100; i++) {
        for (float j = -100; j < 100; j++) {
            display_clear = {" ", "", "", "", j, i, true};
            this->clear.push_back(display_clear);
        }
    }
}

std::vector<display_t> &arcade::Pacman::getState()
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

bool arcade::Pacman::speedGame()
{
    std::chrono::duration<double, std::milli> delta = std::chrono::system_clock::now() - this->past_clock;

    if (delta.count() >= this->clock_time) {
        this->past_clock = std::chrono::system_clock::now();
        return (true);
    } else {
        return (false);
    }
}

uint64_t arcade::Pacman::getScore()
{
    return (static_cast<uint64_t>(this->score));
}

void arcade::Pacman::restart()
{
    this->status = arcade::statusGame::INGAME;
}

void arcade::Pacman::moveMenu(char input)
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

bool arcade::Pacman::canSwitchDirection()
{
    int tmp_x = 0;
    int tmp_y = 0;

    this->x = round(this->x * 10) / 10;
    this->y = round(this->y * 10) / 10;
    tmp_x = this->x;
    tmp_y = this->y;
    if (static_cast<float>(tmp_x) == this->x && static_cast<float>(tmp_y) == this->y) {
        this->direction = this->coming_direction;
        return (true);
    } else
        return (false);
}

void arcade::Pacman::incrementScore()
{
    if (this->map[this->y][this->x] == '.') {
        this->map[this->y][this->x] = ' ';
        this->score += 2;
    } else if (this->map[this->y][this->x] == 'O') {
        this->map[this->y][this->x] = ' ';
        this->score += 15;
        this->ghosted = true;
        this->ghost_clock = std::chrono::system_clock::now();
    }
}

void arcade::Pacman::movePacman()
{
    if (this->canSwitchDirection()) {
        this->incrementScore();
        if (this->direction == arcade::DIR::RIGHT && this->x >= static_cast<int>(this->map[this->y].size()) - 1)
            this->x = 0;
        if (this->direction == arcade::DIR::LEFT && this->x <= 0)
            this->x = static_cast<int>(this->map[this->y].size()) - 1;
        if (this->direction == arcade::DIR::UP && this->y && this->compute_map[this->y - 1][this->x] != -1) {
            this->y -= 0.2;
        } else if (this->direction == arcade::DIR::RIGHT && this->x + 1 < static_cast<int>(this->compute_map[this->y].size()) && this->compute_map[this->y][this->x + 1] != -1) {
            this->x += 0.2;
        } else if (this->direction == arcade::DIR::DOWN && this->y + 1 < static_cast<int>(this->compute_map.size()) && this->compute_map[this->y + 1][this->x] != -1) {
            this->y += 0.2;
        } else if (this->direction == arcade::DIR::LEFT && this->x && this->compute_map[this->y][this->x - 1] != -1) {
            this->x -= 0.2;
        }
        this->incrementScore();
    } else {
        if (this->direction == arcade::DIR::UP) {
            this->y -= 0.2;
        } else if (this->direction == arcade::DIR::RIGHT) {
            this->x += 0.2;
        } else if (this->direction == arcade::DIR::DOWN) {
            this->y += 0.2;
        } else if (this->direction == arcade::DIR::LEFT) {
            this->x -= 0.2;
        }
    }
}

void arcade::Pacman::moveGame(char input)
{
    if (input == 27)
        this->isGame = false;
    if (this->started == false && input == -1)
        return;
    else if (input != -1 && this->started == false) {
        started = true;
        this->start_clock = std::chrono::system_clock::now();
    }
    if (input == 'z')
        this->coming_direction = arcade::DIR::UP;
    else if (input == 'd')
        this->coming_direction = arcade::DIR::RIGHT;
    else if (input == 's')
        this->coming_direction = arcade::DIR::DOWN;
    else if (input == 'q')
        this->coming_direction = arcade::DIR::LEFT;
    this->current_clock = std::chrono::system_clock::now();
    this->delta = this->current_clock - this->start_clock;
    if (this->time_finish - this->delta.count() <= 0)
        this->status = arcade::statusGame::LOSE;
    this->moveGhost();
    this->movePacman();
}

void arcade::Pacman::move(char input)
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
    return (new arcade::Pacman());
}