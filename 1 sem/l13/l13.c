#include <stdio.h>
#include <stdbool.h>
typedef unsigned long long set;

int const a_rus = 1072;
int const ya_rus = 1103;
int const A_rus = 1040;
int const YA_rus = 1071;

int const B_rus = 1;   int const V_rus = 2;
int const G_rus = 3;   int const D_rus = 4;
int const J_rus = 6;   int const Z_rus = 7;
int const I_rus = 9;   int const K_rus = 10;
int const L_rus = 11;  int const M_rus = 12;
int const N_rus = 13;  int const P_rus = 15;
int const R_rus = 16;  int const S_rus = 17;
int const T_rus = 18;  int const F_rus = 20;
int const X_rus = 21;  int const C_rus = 22;
int const CH_rus = 23; int const SH_rus = 24;
int const SHI_rus = 25;

int const b_rus = 33;  int const v_rus = 34;
int const g_rus = 35;  int const d_rus = 36;
int const j_rus = 38;  int const z_rus = 39;
int const i_rus = 41;  int const k_rus = 42;
int const l_rus = 43;  int const m_rus = 44;
int const n_rus = 45;  int const p_rus = 47;
int const r_rus = 48;  int const s_rus = 49;
int const t_rus = 50;  int const f_rus = 52;
int const x_rus = 53;  int const c_rus = 54;
int const ch_rus = 55; int const sh_rus = 56;
int const shi_rus = 57;

unsigned int read_code_point() {
	int c = getchar();
	if (c < 128) {
		return c; // ascii or EOF
	}
	if (c >= 192 && c < 224) {  // for 2 bite
		unsigned int c1 = getchar();
		c = c & ((1 << 5) - 1);
		c1 = c1 & ((1 << 6) - 1);
		return c << 6 | c1;
	} else if (c >= 224 && c < 240) {  // for 3 bite
		unsigned int c1 = getchar();
		unsigned int c2 = getchar();
		c = c & ((1 << 4) - 1);
		c1 = c1 & ((1 << 6) - 1);
		c2 = c2 & ((1 << 6) - 1);
		return c << 12 | c1 << 6 | c2;
	} else if (c >= 240 && c < 248) {  // for 4 bite
		unsigned int c1 = getchar();
		unsigned int c2 = getchar();
		unsigned int c3 = getchar();
		c = c & ((1 << 3) - 1);
		c1 = c1 & ((1 << 6) - 1);
		c2 = c2 & ((1 << 6) - 1);
		c3 = c3 & ((1 << 6) - 1);
		return c << 18 | c1 << 12 | c2 << 6 | c3;
	} else if (c >= 248 && c < 252) {  // for 5 bite
		unsigned int c1 = getchar();
		unsigned int c2 = getchar();
		unsigned int c3 = getchar();
		unsigned int c4 = getchar();
		c = c & ((1 << 2) - 1);
		c1 = c1 & ((1 << 6) - 1);
		c2 = c2 & ((1 << 6) - 1);
		c3 = c3 & ((1 << 6) - 1);
		c4 = c4 & ((1 << 6) - 1);
		return c << 24 | c1 << 18 | c2 << 12 | c3 << 6 | c4;
	} else if (c >= 252 && c < 254) {  // for 6 bite
		unsigned int c1 = getchar();
		unsigned int c2 = getchar();
		unsigned int c3 = getchar();
		unsigned int c4 = getchar();
		unsigned int c5 = getchar();
		c = c & ((1 << 1) - 1);
		c1 = c1 & ((1 << 6) - 1);
		c2 = c2 & ((1 << 6) - 1);
		c3 = c3 & ((1 << 6) - 1);
		c4 = c4 & ((1 << 6) - 1);
		c5 = c5 & ((1 << 6) - 1);
		return c << 30 | c1 << 24 | c2 << 18 | c3 << 12 | c4 << 6 | c5;
	} else return 0;
}

set char_to_set(int j) {
	if (j <= ya_rus && j >= A_rus) {
		return (1llu << (j - A_rus));
	} else
		return 0;
}

bool sep(char c) {
	return c == ' ' || c == '\t';
}

typedef enum {
	LOOKING_FOR_SIGN,
	FIND_WORD,
	WORD
} state_t;


int main() {

	unsigned long long letter = 0;
	letter = letter  | 1llu << (B_rus) | 1llu << (V_rus) | 1llu << (G_rus) | 1llu << (D_rus) | 1llu << (J_rus) | 1llu << (Z_rus) | 1llu << (I_rus) | 1llu << (K_rus) | 1llu << (L_rus) |
		1llu << (M_rus) | 1llu << (N_rus) | 1llu << (P_rus) | 1llu << (R_rus) | 1llu << (S_rus) | 1llu << (T_rus) | 1llu << (F_rus) | 1llu << (X_rus) | 1llu << (C_rus) | 1 << (CH_rus) | 1llu << (SH_rus) |
		1llu << (SHI_rus) | 1llu << (b_rus) | 1llu << (v_rus) | 1llu << (g_rus) | 1llu << (d_rus) | 1llu << (j_rus) | 1llu << (z_rus) | 1llu << (p_rus) | 1llu << (r_rus) | 1llu << (s_rus) | 1llu << (t_rus) |
		1llu << (f_rus) | 1llu << (x_rus) | 1llu << (c_rus) | 1llu << (ch_rus ) | 1llu << (sh_rus) | 1llu << (shi_rus) | 1llu << (k_rus) | 1llu << (l_rus) | 1llu << (m_rus) | 1llu << (n_rus) ;
	state_t state = LOOKING_FOR_SIGN;
	set a1 = 0, a2 = 0;
	int n = 0, q = 0;
	int k;
	do {
		k = read_code_point();
		char_to_set (k);
		if (state == LOOKING_FOR_SIGN) {
			if (!sep(k) && k != '\n' && a1 == 0) {
				a1 = a1 | char_to_set(k);
				state = FIND_WORD;
			} else if (!sep(k) && k != '\n' && a1 != 0) {
				a2 = a2 | char_to_set(k);
				n+=1;
				state = WORD;
			} else state = LOOKING_FOR_SIGN;

		} else if (state == FIND_WORD) {
			if (!sep(k) && k != '\n' ) {
				a1 = a1 | char_to_set(k);
				state = FIND_WORD;
			} else if  (k == '\n' ) {
				state = LOOKING_FOR_SIGN;
				q = 0;
				n = 0;
				a1 = 0;
				a2 = 0;
			} else state = LOOKING_FOR_SIGN;

		} else {
			if (!sep(k) && k != '\n' ) {
				a2 = a2 | char_to_set(k);
				n+=1;
				state = WORD;
			} else if (k == '\n'){
				if ((a1 &a2 & letter) != 0) {
					if (n != 0 && q == 0) {
						printf("ECTb\n");
					}
					n = 0;
					a1 = 0;
					q = 0;
					a2 = 0;
					state = LOOKING_FOR_SIGN;
				}
			} else if (sep(k)){
				state = LOOKING_FOR_SIGN;
				if ((a1 & a2 & letter) != 0) {
					if (n != 0 && q == 0) {
						printf("ECTb\n");
						n = 0;
						q += 1;
					}
				}
				a1 = a2;
				a2 = 0;
			}
		}
	} while (k != EOF);
}


