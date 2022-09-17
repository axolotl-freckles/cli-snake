#pragma once

#define BACKSPACE 8
#define SPACE     32
#define ESCAPE    27
#define ENTER     13
#define CTRL_C    3

#define A_KEY 97
#define B_KEY 98
#define C_KEY 99
#define D_KEY 100
#define E_KEY 101
#define F_KEY 102
#define G_KEY 103
#define H_KEY 104
#define I_KEY 105
#define J_KEY 106
#define K_KEY 107
#define L_KEY 108
#define M_KEY 109
#define N_KEY 110
#define O_KEY 111
#define P_KEY 112
#define Q_KEY 113
#define R_KEY 114
#define S_KEY 115
#define T_KEY 116
#define U_KEY 117
#define V_KEY 118
#define W_KEY 119
#define X_KEY 120
#define Y_KEY 121
#define Z_KEY 122

void keyboard_listener(int * const _key, int const _stop_key, char const * const stop);