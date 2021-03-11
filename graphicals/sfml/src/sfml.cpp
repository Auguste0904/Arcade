/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** sfml.cpp
*/

#include "sfml.hpp"

arcade::Sfml::Sfml()
{
    this->window = new sf::RenderWindow(
        sf::VideoMode(
            sf::VideoMode::getDesktopMode().width,
            sf::VideoMode::getDesktopMode().height
        ),
        "Arcade",
        sf::Style::Close | sf::Style::Resize
    );
    this->window->setFramerateLimit(30);
    this->sprite = {};
    if (!this->font.loadFromFile("./assets/arcade.ttf"))
        throw (std::string("Font not found"));
    this->shade = new sf::Shader();
    this->shade->loadFromFile("assets/scanline.frag", sf::Shader::Fragment);
    this->past_clock = std::chrono::system_clock::now();
    this->clock_time = 1000/30;
    #ifdef CENTER_ORIGIN
    this->view = std::unique_ptr<sf::View>(new sf::View);
    this->view->setSize(sf::Vector2f(1920, 1080));
    this->view->setCenter(sf::Vector2f(0, 0));
    this->window->setView(*this->view);
    #endif
}

void arcade::Sfml::destructor()
{
    this->window->close();
}

char arcade::Sfml::getEvent()
{
    sf::Event event;

    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::A)
                return (97);
            if (event.key.code == sf::Keyboard::B)
                return (98);
            if (event.key.code == sf::Keyboard::C)
                return (99);
            if (event.key.code == sf::Keyboard::D)
                return (100);
            if (event.key.code == sf::Keyboard::E)
                return (101);
            if (event.key.code == sf::Keyboard::F)
                return (102);
            if (event.key.code == sf::Keyboard::G)
                return (103);
            if (event.key.code == sf::Keyboard::H)
                return (104);
            if (event.key.code == sf::Keyboard::I)
                return (105);
            if (event.key.code == sf::Keyboard::J)
                return (106);
            if (event.key.code == sf::Keyboard::K)
                return (107);
            if (event.key.code == sf::Keyboard::L)
                return (108);
            if (event.key.code == sf::Keyboard::M)
                return (109);
            if (event.key.code == sf::Keyboard::N)
                return (110);
            if (event.key.code == sf::Keyboard::O)
                return (111);
            if (event.key.code == sf::Keyboard::P)
                return (112);
            if (event.key.code == sf::Keyboard::Q)
                return (113);
            if (event.key.code == sf::Keyboard::R)
                return (114);
            if (event.key.code == sf::Keyboard::S)
                return (115);
            if (event.key.code == sf::Keyboard::T)
                return (116);
            if (event.key.code == sf::Keyboard::U)
                return (117);
            if (event.key.code == sf::Keyboard::V)
                return (118);
            if (event.key.code == sf::Keyboard::W)
                return (119);
            if (event.key.code == sf::Keyboard::X)
                return (120);
            if (event.key.code == sf::Keyboard::Y)
                return (121);
            if (event.key.code == sf::Keyboard::Z)
                return (122);
            if (event.key.code == sf::Keyboard::Escape)
                return (27);
            if (event.key.code == sf::Keyboard::Return)
                return (10);
            if (event.key.code == sf::Keyboard::Num1)
                return (49);
            if (event.key.code == sf::Keyboard::Num2)
                return (50);
            if (event.key.code == sf::Keyboard::Num3)
                return (51);
            if (event.key.code == sf::Keyboard::Num4)
                return (52);
            if (event.key.code == sf::Keyboard::Num5)
                return (53);
            if (event.key.code == sf::Keyboard::Num6)
                return (54);
            if (event.key.code == sf::Keyboard::Num7)
                return (55);
            if (event.key.code == sf::Keyboard::Num8)
                return (56);
            if (event.key.code == sf::Keyboard::Num9)
                return (57);
            if (event.key.code == sf::Keyboard::Down)
                return (-32);
            if (event.key.code == sf::Keyboard::Up)
                return (-33);
            if (event.key.code == sf::Keyboard::Left)
                return (-34);
            if (event.key.code == sf::Keyboard::Right)
                return (-35);
        }
    }
    return (-1);
}


void arcade::Sfml::refresh(void)
{
    this->window->display();
    this->window->clear();
}

int arcade::Sfml::getWindowHeight()
{
    return (this->window->getSize().y);
}

int arcade::Sfml::getWindowWidth()
{
    return (this->window->getSize().x);
}

bool arcade::Sfml::clockDisplay()
{
    std::chrono::duration<double, std::milli> delta = std::chrono::system_clock::now() - this->past_clock;

    if (delta.count() >= this->clock_time) {
        this->past_clock = std::chrono::system_clock::now();
        return (true);
    } else {
        return (false);
    }
}

sf::Sprite *arcade::Sfml::create_sprite(const std::string &filename)
{
    sf::Texture *tmp_texture = new sf::Texture();
    sf::Sprite *tmp_sprite = new sf::Sprite();

    if (!tmp_texture->loadFromFile(filename)) {
        throw (std::string("Texture not found:" + filename));
    }
    tmp_sprite->setTexture(*tmp_texture);
    #ifdef CENTER_ORIGIN
    tmp_sprite->setOrigin(tmp_texture->getSize().x / 2, tmp_texture->getSize().y / 2);
    #endif
    return (tmp_sprite);
}

void arcade::Sfml::draw_text(display_t &display)
{
    sf::Text text;

    text.setFillColor(sf::Color::White);
    text.setString(display.ascii);
    text.setCharacterSize(20);
    text.setFont(this->font);
    #ifndef CENTER_ORIGIN
    text.setPosition(sf::Vector2f(display.x, display.y));
    #else
    text.setPosition(sf::Vector2f(display.x * 34 - 34/3, display.y * 34 - 34/3));
    #endif
    this->window->draw(text, this->shade);
}

void arcade::Sfml::print(display_t &display)
{
    sf::Sprite *sprite = NULL;

    if (!display.isPrint)
        return;
    if (display.image.length() < 1) {
        this->draw_text(display);
        return;
    }
    if (this->sprite.find(display.image) == this->sprite.end()) {
        sprite = this->create_sprite(display.image);
        this->sprite.insert(std::make_pair(display.image, sprite));
    } else
        sprite = this->sprite[display.image];
    #ifndef CENTER_ORIGIN
    sprite->setPosition(sf::Vector2f(display.x, display.y));
    #else
    sprite->setPosition(sf::Vector2f(display.x * 34, display.y * 34));
    #endif
    this->window->draw(*sprite, this->shade);
}

extern "C" arcade::IGraphics *create()
{
    return (new arcade::Sfml());
}