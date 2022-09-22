#pragma once

#define SECOND 1000

int get_console_width();
int get_console_height();

struct buff_container {
	char * buffer;
	unsigned long buffer_size;
	unsigned long buffer_width;
	unsigned long buffer_height;
};

char * get_tile(
	char * const buffer,
	unsigned long const x_pos,
	unsigned long const y_pos,
	unsigned long const hresolution,
	unsigned long const vresolution
);

unsigned long get_tile_pos
(
	unsigned long const x_pos,
	unsigned long const y_pos,
	unsigned long const hresolution,
	unsigned long const vresolution
);

struct buff_container create_buffer
(
	unsigned long const hresolution,
	unsigned long const vresolution
);

int bufferRenderLoop
(
	char * const buffer,
	unsigned long const  buffer_size,
	char const * pause,
	char const * stop,
	unsigned long const framerate
);

void delete_buffer(char * buff);
