#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <random>
using namespace std;

const unsigned int KEY_COUNT = 16;
const unsigned int MEMORY_SIZE = 4096;
const unsigned int REGISTER_COUNT = 16;
const unsigned int STACK_LEVELS = 16;
const unsigned int VIDEO_HEIGHT = 32;
const unsigned int VIDEO_WIDTH = 64;

class Chip8 {
    public:
	Chip8();

    void LoadRom(string filename);
	void Cycle();

	uint8_t keypad[16]{};
	uint32_t video[64 * 32]{};
	uint8_t soundTimer{};

	private:
	void Table0();
	void Table8();
	void TableE();
	void TableF();
	void OP_NULL();
	
	uint8_t registers[16]{};
	uint8_t memory[4096]{};
	uint16_t index{};
	uint16_t pc{};
	uint16_t stack[16]{};
	uint8_t sp{};
	uint8_t delayTimer{};
	uint16_t opcode;

	default_random_engine randGen;
	uniform_int_distribution<uint8_t> randByte; // 8 bits 0 to 255

		//instructions
	void OP_00E0(); // sets video buffer to 0s
	void OP_00EE(); // returns from a subroutine
	void OP_1nnn(); // jumps to location nnn and sets the pc to the location
	void OP_2nnn(); // calls the subroutine at nnn
	void OP_3xkk(); // skips next intruction if Vx = kk
    void OP_4xkk(); // skips if next intruction is Vx != kk
    void OP_5xy0(); // skips if Vx = Vy
    void OP_6xkk(); // sets Vx = kk 
    void OP_7xkk(); // adds Vx + kk/the byte
	void OP_8xy0(); // makes Vx = Vy
	void OP_8xy1(); // make Vx = Vx or Vy
	void OP_8xy2(); // sets Vx = Vx and Vy
	void OP_8xy3(); // makes Vx = Vx XOR Vy
	void OP_8xy4(); // makes Vx = Vx + Vy checks for overflow
	void OP_8xy5(); // makes Vx = Vx - Vy also sets VF to 1 or 0
	void OP_8xy6(); // divides by 2/ shifts right by 1
	void OP_8xy7(); // same as xy5 but Vy - Vx
	void OP_8xyE(); // multiples by 2/ shifts left by 1
	void OP_9xy0(); // skip if Vx != Vy
	void OP_Annn(); // sets I = nnn
	void OP_Bnnn(); // justs to location nnn + V[0]
	void OP_Cxkk(); // sets Vx to a random byte nad kk
	void OP_Dxyn(); // drawing the screen
	void OP_Ex9E(); // skips if key with the value of Vx is pressed
	void OP_ExA1(); // skips if key with the value of Vx is not pressed
	void OP_Fx07(); // set Vx = delay timer value
	void OP_Fx0A(); // stores value of key press = Vx
	void OP_Fx15(); // setting delay timer  = Vx
	void OP_Fx18(); // sound timmer = Vx
	void OP_Fx1E(); // Add Vx to index
	void OP_Fx29(); // set index to location of sprite
	void OP_Fx33(); // Stores the number in memory and splits it up
	void OP_Fx55(); // stores from 0 to Vx registers in memory
	void OP_Fx65();

	typedef void (Chip8::*Chip8Func)();
	Chip8Func table[0xF + 1];
	Chip8Func table0[0xE + 1];
	Chip8Func table8[0xE + 1];
	Chip8Func tableE[0xE + 1];
	Chip8Func tableF[0x65 + 1];
};

#endif 
