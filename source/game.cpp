#include <algorithm>
#include <random>
#include <thread>
//#include <iostream>
#include <stdio.h>

#include <game.h>

#include <conio.h>
#include <Windows.h>

extern "C" {
	#include <shittykeyboardlistener.h>
}

bool operator == (coordinate const &_a, coordinate const &_b) {
	bool is_x = _a.xpos == _b.xpos;
	bool is_y = _a.ypos == _b.ypos;
	return is_x && is_y;
}

void generate_new_apple(
	coordinate &apple,
	coordinate const &head,
	buff_container const &buffer_cont,
	int const GAME_WIDTH,
	int const GAME_HEIGHT
)
{
	std::random_device rng;
	bool is_valid;
	coordinate next_apple;

	// Makes sure that the apple doesn't appear on a wall or in the snake
	do {
		is_valid = true;
		next_apple.xpos = rng() % GAME_WIDTH;
		next_apple.ypos = rng() % GAME_HEIGHT;

		if(next_apple == head) is_valid = false;
		char const * apple_tile =
			get_tile(
				buffer_cont.buffer,
				next_apple.xpos,
				next_apple.ypos,
				buffer_cont.buffer_width,
				buffer_cont.buffer_height
			);
		if(*apple_tile == '#') is_valid = false;
	} while(!is_valid);

	apple = next_apple;
}

int game_screen(int const * const keys, int const * const rules) {
	// Constant initialization and desambiguation
	long const GAME_WIDTH  = rules[0];
	long const GAME_HEIGHT = rules[1];
	bool const BORDER      = (bool)rules[2];
	unsigned long const hres = std::max<long>(GAME_WIDTH, MIN_HGAME_SIZE);
	unsigned long const vres = std::max<long>(GAME_HEIGHT, MIN_VGAME_SIZE) + 2;

	buff_container buff_cont = create_buffer(hres, vres);

	char const border_char = BORDER? '#' : '+';

	// Paints the border acording to the bordertype rule
	// Puts a '#' if the border is solid
	// Puts a '+' if the game is borderless, meaning the snake teleports ala pacman
	for (unsigned long int i=0; i<(unsigned long)GAME_WIDTH; i++) {
		*get_tile(buff_cont.buffer, i, 0, hres, vres)          = border_char;
		*get_tile(buff_cont.buffer, i, GAME_HEIGHT-1, hres, vres) = border_char;
	}

	for (unsigned long int i=1; i<(unsigned long)(GAME_HEIGHT-1); i++) {
		*get_tile(buff_cont.buffer, 0, i, hres, vres)          = border_char;
		*get_tile(buff_cont.buffer, GAME_WIDTH-1, i, hres, vres) = border_char;
	}

	// Initializes the snake head and start direction to up
	char stop = false;
	int pressed_key = keys[1];

	coordinate head;
	head.xpos = GAME_WIDTH / 2;
	head.ypos = GAME_HEIGHT/ 2;
	*get_tile(buff_cont.buffer, head.xpos, head.ypos, buff_cont.buffer_width, buff_cont.buffer_height)
		= '#';

	// Generates the first apple
	coordinate apple = head;
	generate_new_apple(apple, head, buff_cont, GAME_WIDTH, GAME_HEIGHT);
	*get_tile(buff_cont.buffer, apple.xpos, apple.ypos, buff_cont.buffer_width, buff_cont.buffer_height)
		= '#';

	std::queue<coordinate> snake;
	snake.push(head);

	// Starts the keyboard listener
	std::thread key_listener(keyboard_listener, &pressed_key, ESCAPE, &stop);

	int phys_return = 0;

	//std::cin.tie(nullptr);
	while(true) {
		system("cls");
		if(phys_return || pressed_key == ESCAPE) {
			stop = true;
			printf("Game over, press any key to exit\n");
			break;
		}
		phys_return = physics(buff_cont, keys, rules, &pressed_key, snake, apple, head);
		printf("%s\n", buff_cont.buffer);
		Sleep(SECOND);
	}

	// The keyboard listener usually has to wait for a key before it stops fully
	key_listener.join();
	delete_buffer(buff_cont.buffer);

	return 0;
}

// Utility to find out if a determinate cordinate is in a border
bool in_border(int const &WIDTH, int const &HEIGHT, int const &xpos, int const &ypos) {
	bool in_right_left = (xpos == WIDTH - 1) || (xpos == 0);
	bool in_top_bottom = (ypos == HEIGHT - 1) || (ypos == 0);
	return in_right_left || in_top_bottom;
}

// Updates the snake, cheks for collisions and generates new apples
int physics(
	buff_container const &buffer_cont,
	int const *keys,
	int const *rules,
	int const *pressed_key,
	std::queue<coordinate> &snake,
	coordinate &apple,
	coordinate &head
)
{
	coordinate next_head = head;
	int const dir = *pressed_key;

	int const GAME_WIDTH  = rules[0];
	int const GAME_HEIGHT = rules[1];

	// Gets the direction based 
	int dir_idx = 0;
	for(; dir_idx<4; dir_idx++)
		if(dir == keys[dir_idx]) break;
	// LURD
	// Grid:
	// 0,0 1,0
	// 1,0 1,1

	// Makes sure that it travels in an apropiate direction
	// It also makes sure that the snake doesn't travel backwards, killing itself
	static int prev_dir_idx = dir_idx % 4;
	int next_dir_idx;
	if(dir_idx >= 4)
		next_dir_idx = prev_dir_idx;
	else
		next_dir_idx = dir_idx == (prev_dir_idx+2)%4? prev_dir_idx : dir_idx;

	// Updates the head based on the desired direction
	//  and makes sure that it stays within bounds
	switch(next_dir_idx) {
		case 0:
			next_head.xpos = head.xpos == 0?
				GAME_WIDTH - 1 : head.xpos - 1;
			break;
		case 1:
			next_head.ypos = head.ypos == 0?
				GAME_HEIGHT - 1 : head.ypos - 1;
			break;
		case 2:
			next_head.xpos = (head.xpos + 1) % GAME_WIDTH;
			break;
		case 3:
			next_head.ypos = (head.ypos + 1) % GAME_HEIGHT;
			break;
	}
	// Saves the chosen direction to avoid backtraking
	// Remember, prev_dir_idx is a static value,
	//  meaning it's value is preserved across callings
	prev_dir_idx = next_dir_idx;

	unsigned long const next_abs_pos =
		get_tile_pos(
			next_head.xpos,
			next_head.ypos,
			buffer_cont.buffer_width,
			buffer_cont.buffer_height
		);
	
	// Checks for collisions, either with apples, walls or itself
	// Conviniently, snakes are made of walls
	bool pop_tail = true;
	if(next_head == apple) {
		pop_tail = false;
		generate_new_apple(apple, next_head, buffer_cont, GAME_WIDTH, GAME_HEIGHT);
		*get_tile(
			buffer_cont.buffer,
			apple.xpos, apple.ypos,
			buffer_cont.buffer_width,
			buffer_cont.buffer_height
		)
			= '#';
	}
	else if(buffer_cont.buffer[next_abs_pos] == '#') return 1;
	buffer_cont.buffer[next_abs_pos] = '#';

	// Cuts the tail if the sake didn't eat an apple
	//  and replaces it with the apropiate character
	// Remember that the walls in borderless are different and transparent
	snake.push(next_head);
	if(pop_tail) {
		coordinate tail = snake.front();
		snake.pop();
		char * tail_tile =
			get_tile(
				buffer_cont.buffer,
				tail.xpos, tail.ypos,
				buffer_cont.buffer_width,
				buffer_cont.buffer_height
			);
		*tail_tile = 
			in_border(GAME_WIDTH, GAME_HEIGHT, tail.xpos, tail.ypos)?
			'+' : ' ';
	}

	head = next_head;

	return 0;
}
