#include "Platform.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

Platform::Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight)
    : window(sf::VideoMode(windowWidth, windowHeight), title) // makes the window
{

    if (!soundBuffer.loadFromFile("audio.wav")){ 
        std::cout << "ERROR SOUND" << std::endl; // error message if you dont have the audio
    }
    beep.setBuffer(soundBuffer);
    beep.setLoop(true);
    window.setFramerateLimit(60); // set the refresh rate to 60
    texture.create(textureWidth, textureHeight);
    sprite.setTexture(texture); // adds the sprite to the texture
    sprite.setScale(
        static_cast<float>(windowWidth) / textureWidth, // make sure it scales with the window and texture sizes
        static_cast<float>(windowHeight) / textureHeight
    );
}

Platform::~Platform() {
    window.close();
}

void Platform::soundPlayer(bool active){
    if (active){
        if (beep.getStatus() != sf::Sound::Playing){ // if it's not already playing play the beep
            beep.play();
        }
    }
    else {
        beep.stop(); // stops it
    }
}

void Platform::update(void const* buffer, int pitch){
    texture.update(static_cast<const sf::Uint8*>(buffer)); // gets the updated textures from the buffer

    window.clear(); // clears
    window.draw(sprite); // draws the new updated sprites
    window.display();
}

bool Platform::processInput(uint8_t* keys){
    bool quit = false; // if you hit esc
    sf::Event event;

    while (window.pollEvent(event)){
        switch (event.type){
            case sf::Event::Closed: // if you close the window
                quit = true;
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code){
                    case sf::Keyboard::Escape: quit = true; break; // all the keybinds
                    case sf::Keyboard::X: keys[0] = 1; break;
                    case sf::Keyboard::Num1: keys[1] = 1; break;
                    case sf::Keyboard::Num2: keys[2] = 1; break; // I just used recommended keybinds that most people use
                    case sf::Keyboard::Num3: keys[3] = 1; break;
                    case sf::Keyboard::Q: keys[4] = 1; break; 
                    case sf::Keyboard::W: keys[5] = 1; break;   //   1 2 3 4
                    case sf::Keyboard::E: keys[6] = 1; break;   //   q w e r
                    case sf::Keyboard::A: keys[7] = 1; break;   //   a s d f
                    case sf::Keyboard::S: keys[8] = 1; break;   //   z x c v
                    case sf::Keyboard::D: keys[9] = 1; break;
                    case sf::Keyboard::Z: keys[0xA] = 1; break;
                    case sf::Keyboard::C: keys[0xB] = 1; break;
                    case sf::Keyboard::Num4: keys[0xC] = 1; break;
                    case sf::Keyboard::R: keys[0xD] = 1; break;
                    case sf::Keyboard::F: keys[0xE] = 1; break;
                    case sf::Keyboard::V: keys[0xF] = 1; break;
                    default: break;
                }
                break;  
            
            case sf::Event::KeyReleased:
                switch (event.key.code){
                    case sf::Keyboard::X: keys[0] = 0; break;
                    case sf::Keyboard::Num1: keys[1] = 0; break;
                    case sf::Keyboard::Num2: keys[2] = 0; break;
                    case sf::Keyboard::Num3: keys[3] = 0; break;
                    case sf::Keyboard::Q: keys[4] = 0; break;
                    case sf::Keyboard::W: keys[5] = 0; break;
                    case sf::Keyboard::E: keys[6] = 0; break;
                    case sf::Keyboard::A: keys[7] = 0; break;
                    case sf::Keyboard::S: keys[8] = 0; break;
                    case sf::Keyboard::D: keys[9] = 0; break;
                    case sf::Keyboard::Z: keys[0xA] = 0; break;
                    case sf::Keyboard::C: keys[0xB] = 0; break;
                    case sf::Keyboard::Num4: keys[0xC] = 0; break;
                    case sf::Keyboard::R: keys[0xD] = 0; break;
                    case sf::Keyboard::F: keys[0xE] = 0; break;
                    case sf::Keyboard::V: keys[0xF] = 0; break;
                    default: break;
                }
                break;
            default: // to avoid the warnings for not using all the keybinds
                break;
        }
    }
    return quit;
}
