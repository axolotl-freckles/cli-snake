#include <iostream>

#include <menu.h>
#include <game.h>

#ifndef RELEASE
	#define DEFAULT_UP    164
	#define DEFAULT_DOWN  'e'
	#define DEFAULT_LEFT  'o'
	#define DEFAULT_RIGHT 'u'
	/*
		I'm the dude with the weird tastes
		I'm using an spanish dvorak layout
		so this makes sense for me
		the 165 char is the 'ñ'
		hope it shows in your screen
	*/
#else
	#define DEFAULT_UP    'w'
	#define DEFAULT_DOWN  's'
	#define DEFAULT_LEFT  'a'
	#define DEFAULT_RIGHT 'd'
#endif

int main(void) {
	std::cin.tie(nullptr);
	
	int select;
	// Key direction follows LURD
	// Left, Up, Right, Down
	int keys[] = {DEFAULT_LEFT, DEFAULT_UP, DEFAULT_RIGHT, DEFAULT_DOWN};
	// Rules are: Width, height, border;
	// Might add speed later
	int rules[] = {16, 10, 1};

	do {
		select = main_menu(keys);
		switch (select) {
			case START_OPTION:
				game_screen(keys, rules);
				break;
			case GAME_SETTINGS:
				game_config(rules, keys);
				break;
			case KEY_SETTINGS:
				key_config(keys);
				break;
		}
	} while(select != EXIT_OPTION);

	system(CLEAR_COMMAND);

	return 0;
}