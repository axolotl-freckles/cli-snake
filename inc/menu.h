#define CLEAR_COMMAND "cls"

#define START_OPTION  0
#define GAME_SETTINGS 1
#define KEY_SETTINGS  2
#define EXIT_OPTION   3

int main_menu(int * const keys);
void key_config(int * const key_arr);
void game_config(int * const game_params, int * const keys);