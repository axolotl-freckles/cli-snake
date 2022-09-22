#include <clirender.h>
#include <stdlib.h>
#include <stdio.h>

#include <Windows.h>

int get_console_width() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int get_console_height() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

char * get_tile
	(
		char * const buffer,
		unsigned long const x_pos,
		unsigned long const y_pos,
		unsigned long const hresolution,
		unsigned long const vresolution
	)
{
	unsigned long const buff_pos = get_tile_pos(x_pos, y_pos, hresolution, vresolution);
	return buffer + buff_pos;
}

unsigned long get_tile_pos
	(
		unsigned long const x_pos,
		unsigned long const y_pos,
		unsigned long const hresolution,
		unsigned long const vresolution
	)
{
	unsigned long const Y_DISPLACEMENT = (y_pos%vresolution) * (hresolution+1);
	unsigned long const X_DISPLACEMENT = x_pos % hresolution;
	unsigned long const MAX_BUFF_SIZE  = vresolution * (hresolution+1);
	return (X_DISPLACEMENT + Y_DISPLACEMENT) % MAX_BUFF_SIZE;
}

struct buff_container create_buffer(unsigned long const hresolution, unsigned long const vresolution) {
	unsigned long const BUFFER_SIZE = vresolution * (hresolution+1);
	char * buff_start;
	do {
		buff_start = (char*)malloc(BUFFER_SIZE * sizeof(char));
	} while(buff_start == NULL);

	memset(buff_start, ' ', BUFFER_SIZE * sizeof(char));

	for (unsigned long i=hresolution; i<BUFFER_SIZE; i+=(hresolution+1))
		buff_start[i] = '\n';
	buff_start[BUFFER_SIZE-1] = '\0';
	
	struct buff_container ret;
	ret.buffer        = buff_start;
	ret.buffer_size   = BUFFER_SIZE;
	ret.buffer_height = vresolution;
	ret.buffer_width  = hresolution;
	return ret;
}

int bufferRenderLoop
	(
		char * const buffer,
		unsigned long const  buffer_size,
		char const * pause,
		char const * stop,
		unsigned long const framerate
	)
{
	int ret_val = 0;

	do {
		if(*pause) {
			Sleep(1);
			continue;
		}
		system("cls");
		buffer[buffer_size-1] = '\0';
		ret_val = printf_s("%s", buffer);
		if(*stop) break;

		Sleep(framerate);
	} while (ret_val != -1 && !(*stop));

	return ret_val;
}

void delete_buffer(char * buffer) {
	free(buffer);
}
