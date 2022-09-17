#pragma once
#include <queue>

extern "C" {
	#include <clirender.h>
}

#define MIN_HGAME_SIZE 10
#define MIN_VGAME_SIZE 10

struct coordinate {
	unsigned long xpos;
	unsigned long ypos;
};

int physics(
	buff_container const &buffer_cont,
	int const *keys,
	int const *rules,
	int const *pressed_key,
	std::queue<coordinate> &snake,
	coordinate &apple,
	coordinate &head
);

bool operator == (coordinate const &, coordinate const &);

int game_screen(int const * const keys, int const * const rules);
