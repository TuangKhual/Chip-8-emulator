#include "Chip8.h"
#include "Platform.h"
#include <chrono>
#include <iostream>

using namespace std;

int main(int argc, char** argv){
    int videoScale = 20;
    int cycleDelay = 2;  // when you run it Defaults to tetris
    string romName = "Tetris.ch8";
    if (argc == 4){      //                ./chip8 (videoScale) (delay) (name)
        videoScale = stoi(argv[1]); // converts the typed into a int to use 
        cycleDelay = stoi(argv[2]);
        romName = argv[3]; // collects the other rom name you want to use instead
	}



    Platform platform ("Chip 8 emulator", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

    Chip8 chip8;
    chip8.LoadRom(romName); // loads the rom

    int videoPitch = sizeof(chip8.video[0]) * VIDEO_WIDTH; // how big 1 row is

    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    bool quit = false;

    while (!quit){ // as long as you dont quit
        quit = platform.processInput(chip8.keypad); // checks if you want to quit

        auto currTime = std::chrono::high_resolution_clock::now();
         // the difference in time from now and last cycle aka the delta time interval
        float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currTime - lastCycleTime).count(); 

		if (dt > cycleDelay){ // if enough time has passed for the next cycle according to the delay set
			lastCycleTime = currTime; // updates
			chip8.Cycle(); // runs a cycle

			platform.update(chip8.video, videoPitch); // updates the video screen
		}
        if (chip8.soundTimer > 0){ 
            platform.soundPlayer(true); // plays sound/beep
        } 
        else {
            platform.soundPlayer(false);
        }
	}

    return 0;
}
