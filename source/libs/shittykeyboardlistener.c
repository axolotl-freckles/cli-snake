#include <shittykeyboardlistener.h>

//Windows specific includes
#include <conio.h>
#include <windows.h>

#define SECOND 1000

#define SLEEP_FUNCTION(x) Sleep(x);

void keyboard_listener(int * const _key, int const _stop_key, char const * const stop) {
	int key_code = _stop_key;

	do {
		if(*stop) break;
		key_code = getch();
		*_key = key_code;
		SLEEP_FUNCTION(SECOND / 120);
		// The keyboard listener may have to receive a key before it terminates
		//  if the stop key isn't pressed
	} while (key_code != _stop_key);
}