#include "Chip8.h"
#include "Platform.h"
#include <chrono>
#include <iostream>

using namespace std;

int main(int argc, char** argv){
    if (argc != 4){
		cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n"; // to run youd use ./chip8 (scale) (delay) (rom name))
		exit(EXIT_FAILURE);
	}

    int videoScale = stoi(argv[1]); // converts the typed into a int to use 
    int cycleDelay = stoi(argv[2]);
    char const* romName = argv[3]; // collects the name

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
	}

    return 0;
}
