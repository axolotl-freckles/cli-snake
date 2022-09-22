#include <menu.h>
#include <array>
#include <string>
#include <conio.h>
#include <iostream>

#include <cctype>
#include <cstring>

extern "C" {
	#include <shittykeyboardlistener.h>
	#include <clirender.h>
}
#include <game.h>

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

void print_menu_options(char const ** const option,int const selection, int const OPT_NUM) {
	for(int i=0; i<OPT_NUM; i++) {
		std::cout<<"   "<< (selection == i? "->" : "  ");
		std::cout<<option[i]<<'\n'; 
	}
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
	int const OPT_NUM   = 4;

	do {
		system(CLEAR_COMMAND);
		std::cout<<display[0]<<"\n\n";
		print_menu_instructions(keys);
		print_menu_options(display + OPT_START, selection, OPT_NUM);

		key = getch();
		update_selection(keys, selection, key);

		if(selection < 1) selection = 4 + selection;
		selection %= 4;
	} while(key != ESCAPE && key != ENTER);

	if (key == ESCAPE || selection == EXIT_OPTION)
		return EXIT_OPTION;

	return selection;
}

void grid_size_config(int * const _dimention, int const * const keys) {
	char const * display[] = {
		"             GAME SIZE",
		"Press ESC to cancel, BACKSPACE to reset to defaults",
		" Width:  ",
		" Height: ",
		" Exit"
	};
	int const EXIT_OPT = 2;
	int const OPT_NUM  = 3;
	int const OPT_ST   = 2;

	int selection = EXIT_OPT;
	int key = ESCAPE;

	auto print_menu_optionsP =
		[display, OPT_NUM, OPT_ST, _dimention]
		(int const select, bool const draw_line = false, char const * new_size_buff = nullptr) -> void {
			for(int i=0; i<OPT_NUM; i++) {
				std::cout<<"   "<< (select == i? "->" : "  ");
				std::cout<<display[i+OPT_ST]; 
				if(i<EXIT_OPT) {
					if(draw_line && i==select) {
						if(new_size_buff != nullptr)
							std::cout<<new_size_buff;
						std::cout<<'_';
					}
					else {
						std::cout<<_dimention[i];
					}
				}
				std::cout<<'\n';
			}
		};

	do {
		system(CLEAR_COMMAND);
		std::cout<<display[0]<<"\n";
		std::cout<<display[1]<<'\n';
		print_menu_instructions(keys);

		print_menu_optionsP(selection);

		// Show warning if the selected size is bigger than the console size
		if(_dimention[0] > get_console_width() || _dimention[1] > get_console_height())
			std::cout<<"\n\n!!!!WARNING: selected size bigger than console's actual size!!!!\n";

		key = getch();
		update_selection(keys, selection, key);

		if(selection < 1) selection = OPT_NUM + selection;
		selection %= OPT_NUM;

		if(key == ENTER) {
			if(selection == EXIT_OPT) return;

			char buffer[256] = {0};
			int const BUFFER_SIZE = 255;
			int idx = 0;

			do {
				system(CLEAR_COMMAND);
				std::cout<<display[0]<<"\n";
				std::cout<<display[1]<<'\n';
				print_menu_instructions(keys);

				print_menu_optionsP(selection, true, buffer);

				key = getch();

				if(idx < 0) idx = 0;
				switch(key) {
					case BACKSPACE:
						buffer[--idx] = '\0';
						break;
					case ENTER:
						_dimention[selection] = std::atoi(buffer);
						break;
					case ESCAPE:
						key = ENTER;
						break;
					default:
						if(std::isdigit( (char)key ) && idx < BUFFER_SIZE) {
							buffer[idx++] = (char)key;
							buffer[idx] = '\0';
						}
						break;
				}
			} while (key != ENTER);
		}
		if(key == BACKSPACE) {
			switch(selection) {
				case 0:
					_dimention[selection] = MIN_HGAME_SIZE;
					break;
				case 1:
					_dimention[selection] = MIN_VGAME_SIZE;
					break;
			}
		}
	} while(key != ESCAPE);
}
void border_type_config(int * const _border_type, int const * const keys) {
	char const * display[] = {
		"             BORDER TYPE",
		"Current selection: ",
		" Borderless (+)",
		" Border     (#)",
		" Exit"
	};
	int const EXIT_OPT = 2;
	int const OPT_NUM  = 3;
	int const OPT_ST   = 2;

	int selection = *_border_type;
	int key = ESCAPE;

	do {
		system(CLEAR_COMMAND);
		std::cout<<display[0]<<"\n\n";
		print_menu_instructions(keys);
		std::cout<<display[1]<<(*_border_type? '#' : '+')<<'\n';

		print_menu_options(display+OPT_ST, selection, OPT_NUM);

		key = getch();
		update_selection(keys, selection, key);

		if(selection < 1) selection = OPT_NUM + selection;
		selection %= OPT_NUM;

		if(key == ENTER) {
			switch(selection) {
				case 0:
				case 1:
					*_border_type = selection;
					break;
				case EXIT_OPT:
					return;
			}
		}
	} while(key != ESCAPE);
}
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
		print_menu_options(display+OPTION_ST, selection, OPTION_NUM);

		key = getch();
		update_selection(keys, selection, key);

		if(selection < 1) selection = OPTION_NUM + selection;
		selection %= OPTION_NUM;

		if (key == ENTER) {
			switch(selection) {
				case BORDER:
					border_type_config(game_params+2, keys);
					break;
				case GRID:
					grid_size_config(game_params, keys);
					break;
				case RETURN_TO_MAIN:
					return;
			}
		}
	} while(key != ESCAPE);
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

	auto print_menu_optionsP =
		[display, OPTION_NUM, OPTION_ST,key_arr]
		(int const select, bool draw_line = false) -> void {
			for(int i=0; i<OPTION_NUM; i++) {
				std::cout<<"   "<< (select == i? "->" : "  ");
				std::cout<<display[i+OPTION_ST];
				if(i<(OPTION_NUM-1)) {
					if(draw_line && i==select)
						std::cout<<'_';
					else
						std::cout<<(char)key_arr[i];
				}
				std::cout<<'\n';
			}
		};

	do {
		system(CLEAR_COMMAND);
		std::cout<<display[0]<<"\n";
		print_menu_instructions(key_arr);
		print_menu_optionsP(selection);

		key = getch();
		update_selection(key_arr, selection, key);

		if(selection < 1) selection = OPTION_NUM + selection;
		selection %= OPTION_NUM;

		if(key == ENTER) {
			if(selection == RETURN_TO_MAIN) break;
			
			system(CLEAR_COMMAND);
			std::cout<<display[0]<<"\n";
			print_menu_instructions(key_arr);
			print_menu_optionsP(selection, true);

			key = getch();
			key_arr[selection] = key;
		}
	} while(key != ESCAPE);
}