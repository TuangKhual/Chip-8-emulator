#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Platform{
    public:
        Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
        ~Platform();
        void update(void const* buffer, int pitch);
        bool processInput(uint8_t* keys);

    private:
        sf::RenderWindow window;
        sf::Texture texture;
        sf::Sprite sprite;
};