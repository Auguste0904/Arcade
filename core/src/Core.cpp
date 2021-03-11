/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** Arcade.cpp
*/

#include "Core.hpp"

arcade::Core::Core(int ac, char **av)
{
    this->ac = ac;
    this->av = av;
}

int arcade::Core::run()
{
    try {
        this->error_handling();
        this->getLibrary();
        this->getGames();
        this->launch_core();
        for (int i = 0; i < static_cast<int>(this->lib_list.size()); i++)
            dlclose(this->lib_list[i].handle);
        for (int i = 0; i < static_cast<int>(this->game_list.size()); i++)
            dlclose(this->game_list[i].handle);
    } catch (arcade::Exception &message) {
        std::cerr << message.what() << std::endl;
        return (84);
    } catch (std::exception &message) {
        std::cerr << message.what() << std::endl;
        return (84);
    } catch (std::string &message) {
        std::cerr << message << std::endl;
        return (84);
    } catch (...) {
        std::cerr << "An unknown error occured!" << std::endl;
        return (84);
    }
    return (0);
}

bool arcade::Core::hasEnding(std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length())
        return (fullString.compare(fullString.length() - ending.length(), ending.length(), ending) == 0);
    else
        return false;
}

std::string arcade::Core::get_string_end(std::string tmp)
{
    std::string str = "";
    int i = tmp.length();

    if (i <= 0 || !tmp[0])
        return (std::string(""));
    if (hasEnding(tmp, ".so"))
        i -= 4;
    for (; i >= 0 && tmp[i] != '.' && tmp[i] != '/' && tmp[i] != '~'; i--) {
        if (i > 0 && (tmp[i - 1] == '.' || tmp[i - 1] == '/' || tmp[i - 1] == '~'))
            break;
    }
    if (i < 0)
        i = 0;
    for (; tmp[i]; i++)
        str.push_back(tmp[i]);
    return (str);
}

void arcade::Core::getGames()
{
    DIR *dir;
    struct dirent *dirent;
    struct stat filestat;
    std::string tmp = "./games/";
    void *dl = NULL;

    if ((dir = opendir("./games")) == NULL)
        throw (arcade::Exception("Can't open lib directory"));
    while ((dirent = readdir(dir)) != NULL) {
        tmp = std::string("./games/") + std::string(dirent->d_name);
        stat(tmp.c_str(), &filestat);
        if (S_ISREG(filestat.st_mode) == 1 && dirent->d_name[0] != '.' && hasEnding(tmp, ".so")) {
            dl = NULL;
            if ((dl = dlopen(tmp.c_str(), RTLD_NOW)))
                this->game_list.push_back({tmp, dl, arcade::libType::GAME});
            dlerror();
        }
//        free(dirent);
    }
    closedir(dir);
}

void arcade::Core::getLibrary()
{
    DIR *dir;
    struct dirent *dirent;
    struct stat filestat;
    std::string tmp = "./lib/";
    void *dl = NULL;

    if ((dir = opendir("./lib")) == NULL)
        throw (arcade::Exception("Can't open lib directory"));
    while ((dirent = readdir(dir)) != NULL) {
        tmp = std::string("./lib/") + std::string(dirent->d_name);
        stat(tmp.c_str(), &filestat);
        if (S_ISREG(filestat.st_mode) == 1 && dirent->d_name[0] != '.'
        && hasEnding(tmp, ".so") && (this->get_string_end(this->lib_list[0].name).compare(this->get_string_end(tmp)))) {
            dl = NULL;
            if ((dl = dlopen(tmp.c_str(), RTLD_NOW)))
                this->lib_list.push_back({tmp, dl, arcade::libType::GRAPHICAL});
            dlerror();
        }
//        free(dirent);
    }
    closedir(dir);
}

void arcade::Core::clear()
{
    static display_t display_clear = {" ", "", "", "", 0, 0, true};

    for (float i = -100; i < 100; i++) {
        for (float j = -100; j < 100; j++) {
            display_clear = {" ", "", "", "", j, i, true};
            this->graphics->print(display_clear);
        }
    }
}

void arcade::Core::switch_lib()
{
    createLib_t *initialize_graphics = NULL;

    if (this->graphics != NULL)
        (this->graphics)->destructor();
    this->which_lib += 1;
    if (this->which_lib >= static_cast<int>(this->lib_list.size()))
        this->which_lib = 0;
    initialize_graphics = (createLib_t *)dlsym(this->lib_list[this->which_lib].handle, "create");
    if (!(initialize_graphics))
        throw (arcade::Exception(std::string(dlerror())));
    this->graphics = initialize_graphics();
}

void arcade::Core::switch_lib(void *handle)
{
    createLib_t *initialize_graphics = NULL;

    if (this->graphics != NULL)
        (this->graphics)->destructor();
    for (int i = 0; i < static_cast<int>(this->lib_list.size()); i++) {
        if (handle == this->lib_list[i].handle) {
            this->which_lib = i;
            break;
        }
    }
    initialize_graphics = (createLib_t *)dlsym(this->lib_list[this->which_lib].handle, "create");
    if (!(initialize_graphics))
        throw (arcade::Exception(std::string(dlerror())));
    this->graphics = initialize_graphics();
}

void arcade::Core::manage_menu_event()
{
    if (this->event == -1)
        return;
    if (this->event == -34 || this->event == -35)
        this->switch_lib();
    if (this->event == -32
    && this->select_index + 1 <= static_cast<int>(this->select_list.size()))
        this->select_index += 1;
    if (this->event == -33
    && this->select_index - 1 >= 0)
        this->select_index -= 1;
    if (this->select_index < static_cast<int>(this->select_list.size()) && this->event == 10) {
        if (this->select_list[this->select_index].type == arcade::libType::GAME) {
            this->clear();
            launchGame(this->select_list[this->select_index].handle);
            this->clear();
        } else
            switch_lib(this->select_list[this->select_index].handle);
    } else if ((this->select_index == static_cast<int>(this->select_list.size())) && ((this->event >= 'a' && this->event <= 'z') || (this->event >= '0' && this->event <= '9'))) {
        this->nickname += this->event;
    } else if ((this->select_index == static_cast<int>(this->select_list.size())) && this->event == 10 && this->nickname.size())
        this->nickname.pop_back();
}

void arcade::Core::setScore()
{
    std::ofstream tmp_file;

    if (this->nickname.size() <= 0 || !this->nickname.compare(""))
        return;
    tmp_file.open("./assets/score.txt", std::ofstream::out | std::ofstream::trunc);
    tmp_file << std::string(std::to_string(this->score) + " " + this->nickname);
    tmp_file.close();
}

void arcade::Core::getScore()
{
    std::ofstream tmp_file;
    std::ifstream file("./assets/score.txt");
    std::string tmp("");
    std::vector<std::string> array;
    std::stringstream tmp_stream(tmp);

    if (!file.is_open()) {
        tmp_file = std::ofstream("./assets/score.txt");
        file = std::ifstream("./assets/score.txt");
        return;
    }
    getline(file, tmp, '\0');
    if (tmp.size() == 0 || !tmp.compare("")) {
        this->setScore();
        return;
    }
    tmp_file.close();
    file.close();
    this->best_score = tmp;
    tmp_stream = std::stringstream(tmp);
    while(getline(tmp_stream, tmp, ' ')) {
        array.push_back(tmp);
    }
    if (array.size() == 0)
        return;
    if (array.size() != 2)
        throw (arcade::Exception("The file isn't correct or has been corrupted"));
    if (this->score > std::stoul(array[0]) && this->nickname.size())
        this->setScore();
}

void arcade::Core::print_menu()
{
    static display_t title = {"Arcade", "red", "", "", -1, -14, true};
    static display_t display_games = {"", "yellow", "", "", -6, 0, true};
    static display_t background = {"", "", "", "assets/BackgroundArcade.jpg", 0, 0, true};
    static display_t borne = {"", "", "", "assets/BorneArcade.png", 0, 0, true};
    static display_t select = {">", "green", "", "assets/GreenArrow.png", -8, 0, true};
    static display_t select_none = {" ", "", "", "", -8, 0, true};
    static display_t nickname = {"Player name: ", "cyan", "", "", -6, 12, true};
    static display_t high_score = {"Best score: ", "cyan", "", "", -6, 14, true};

    this->graphics->print(background);
    this->graphics->print(borne);
    display_games.y = -6;
    for (int i = 0; i <= static_cast<int>(this->select_list.size()); i++) {
        if (i < static_cast<int>(this->select_list.size())) {
            display_games.y = -6 + i;
            if (this->select_list[i].type == arcade::libType::GRAPHICAL)
                display_games.y += 2;
            display_games.ascii = this->get_string_end(this->select_list[i].name);
            this->graphics->print(display_games);
            if (this->select_index == i) {
                select.y = display_games.y;
                this->graphics->print(select);
            } else {
                select_none.y = display_games.y;
                this->graphics->print(select_none);
            }
        } else {
            if (this->select_index == i) {
                select.y = 12;
                this->graphics->print(select);
            } else {
                select_none.y = 12;
                this->graphics->print(select_none);
            }
        }
    }
    nickname.ascii = "Player name: " + this->nickname;
    this->graphics->print(nickname);
    high_score.ascii = "Best score: " + this->best_score;
    this->graphics->print(high_score);
    this->graphics->print(title);
}

void arcade::Core::launch_menu()
{
    this->getScore();
    while (true) {
        this->event = this->graphics->getEvent();

        if (this->event == arcade::CLOSE || this->event == arcade::ESCAPE) {
            this->graphics->destructor();
            break;
        } else
            this->manage_menu_event();
        if (this->graphics->clockDisplay()) {
            this->print_menu();
            this->graphics->refresh();
        }
    }
}

void arcade::Core::launch_core()
{
    this->switch_lib();
    for (int i = 0; i < static_cast<int>(this->game_list.size()); i++)
        this->select_list.push_back(this->game_list[i]);
    for (int i = 0; i < static_cast<int>(this->lib_list.size()); i++)
        this->select_list.push_back(this->lib_list[i]);
    this->launch_menu();
}