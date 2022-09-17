#include <menu.h>
#include <array>
#include <string>
#include <conio.h>
#include <iostream>

extern "C" {
	#include <shittykeyboardlistener.h>
	#include <clirender.h>
}

// SNAK 37
// 18.5

void update_selection(int const * const keys, int &selection, int const &key) {
	// keys[LURD] indexed to 0
	// in this case, 1 -> up and 3 -> down
	if(key == keys[1])
		selection--;
	else if(key == keys[3])
		selection++;
}

void print_menu_instructions(int const * const keys) {
	// keys[LURD] indexed to 0
	// in this case, 1 -> up and 3 -> down
	std::cout<<"Press \'"<<(char)keys[3]<<"\' to select down, ";
	std::cout<<"\'"<<(char)keys[1]<<"\' to select up. ENTER to select\n";
}

int main_menu(int * const keys) {
	std::cin.tie(nullptr);

	char const * display[] = {
		"///////   ///  //     ///     ///  //\n///       //// //     ///     ///  //\n///////   // / //    // //    /////  \n    ///   // ////   ///////   /// // \n///////   //  ///   //   //   ///  //",
		" Start",
		" Game settings",
		" Keyboard settings",
		" Exit"
	};

	static int selection = 0;
	int key = ESCAPE;
	int const OPT_START = 1;

	do {
		system(CLEAR_COMMAND);
		std::cout<<display[0]<<"\n\n";
		print_menu_instructions(keys);
		for(int i=0; i<4; i++) {
			std::cout<<"   "<< (selection == i? "->" : "  ");
			std::cout<<display[i+OPT_START]<<'\n';
		}

		key = getch();
		update_selection(keys, selection, key);

		if(selection < 1) selection = 4 + selection;
		selection %= 4;
	} while(key != ESCAPE && key != ENTER);

	if (key == ESCAPE || selection == EXIT_OPTION)
		return EXIT_OPTION;

	return selection;
}

void grid_size_config(int * const _dimention);
void border_type_config(int * const _border_type);
void game_config(int * const game_params, int * const keys) {
	std::cin.tie(nullptr);
	char const * display[] = {
		"             GAME CONFIG",
		" Border Type",
		" Grid size",
		" Exit"
	};
	enum game_option {BORDER, GRID, RETURN_TO_MAIN};
	int const OPTION_NUM = 3;
	int const OPTION_ST  = 1;

	int selection = RETURN_TO_MAIN;
	int key = ESCAPE;

	do {
		system(CLEAR_COMMAND);
		std::cout<<display[0]<<"\n\n";
		print_menu_instructions(keys);
		for (int i=0; i<OPTION_NUM; i++) {
			std::cout<<"   "<< (selection == i? "->" : "  ");
			std::cout<<display[i+OPTION_ST]<<'\n';
		}

		key = getch();
		update_selection(keys, selection, key);

		if(selection < 1) selection = OPTION_NUM + selection;
		selection %= OPTION_NUM;
	} while(key != ESCAPE && key != ENTER);
}

void key_config(int * const key_arr) {
	char const * display[] = {
		"              KEY CONFIG",
		" Move <: ",
		" Move ^: ",
		" Move >: ",
		" Move v: ",
		" Exit"
	};
	enum key_option {MOVE_L, MOVE_U, MOVE_R, MOVE_D, RETURN_TO_MAIN};
	int const OPTION_NUM = 5;
	int const OPTION_ST  = 1;

	int selection = RETURN_TO_MAIN;
	int key = ESCAPE;

	do {
		system(CLEAR_COMMAND);
		std::cout<<display[0]<<"\n";
		print_menu_instructions(key_arr);
		for (int i=0; i<OPTION_NUM; i++) {
			std::cout<<"   "<< (selection == i? "->" : "  ");
			std::cout<<display[i+OPTION_ST];
			if(i<4)
				std::cout<<(char)key_arr[i];
			std::cout<<'\n';
		}

		key = getch();
		update_selection(key_arr, selection, key);

		if(selection < 1) selection = OPTION_NUM + selection;
		selection %= OPTION_NUM;

		if(key == ENTER) {
			if(selection == RETURN_TO_MAIN) break;
			
			system(CLEAR_COMMAND);
			std::cout<<display[0]<<"\n";
			print_menu_instructions(key_arr);
			for (int i=0; i<OPTION_NUM; i++) {
				std::cout<<"   "<< (selection == i? "->" : "  ");
				std::cout<<display[i+OPTION_ST];
				if(i<4) {
					if (i!=selection) std::cout<<(char)key_arr[i];
					else              std::cout<<'_';
				}
				std::cout<<'\n';
			}

			key = getch();
			key_arr[selection] = key;
		}
	} while(key != ESCAPE);
}