#include <stdio.h>
#include <inttypes.h>

typedef struct _worktask {
    uint8_t WorkID;
    uint32_t MidState[8];
    uint32_t Merkle[3];
} WORKTASK;

//WORKTASK Work = { 0, { 0xcb18a156,0x735fadbc,0xea5b3fc9,0x8ddadef9,0x6c3031aa,0x50cee616,0x826a915d,0x88010577 },
//	{ 0x514898af,0x51bc10ac,0x1a011337 } };
#include "work.inc"

uint32_t PreCalc[6], hold[6];

const uint32_t SHA256_K[3] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf
};

#define rotate(x,y) ((x<<y) | (x>>(sizeof(x)*8-y)))
#define rotr(x,y) ((x>>y) | (x<<(sizeof(x)*8-y)))

#define R(a, b, c, d, e, f, g, h, w, k) \
	h = h + (rotate(e, 26) ^ rotate(e, 21) ^ rotate(e, 7)) + (g ^ (e & (f ^ g))) + k + w; \
	d = d + h; \
	h = h + (rotate(a, 30) ^ rotate(a, 19) ^ rotate(a, 10)) + ((a & b) | (c & (a | b)))

void cg_precalc_hash(uint32_t *state, uint32_t *data)
{
	uint32_t A, B, C, D, E, F, G, H;

	A = state[0];
	B = state[1];
	C = state[2];
	D = state[3];
	E = state[4];
	F = state[5];
	G = state[6];
	H = state[7];

	R(A, B, C, D, E, F, G, H, data[0], SHA256_K[0]);
	PreCalc[2] = H;
	PreCalc[5] = D;
	R(H, A, B, C, D, E, F, G, data[1], SHA256_K[1]);
	PreCalc[1] = G;
	PreCalc[4] = C;
	R(G, H, A, B, C, D, E, F, data[2], SHA256_K[2]);
	PreCalc[0] = F;
	PreCalc[3] = B;
}

#define r(x) ((x-n)&7)

uint32_t krotate(uint32_t x, uint8_t y)
{
    return ((x<<y) | (x>>(32-y)));
}

void K16AsicPreCalc(WORKTASK *work)
{
    const uint32_t K[3] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf };
    uint32_t x, y, z;
    uint32_t m[8];
    uint8_t n;
    
    for(n = 0; n < 8; n++)
        m[n] = work->MidState[n];

    for(n = 0; n < 3; n++) {

        x = m[5-n] ^ m[6-n];
        x = x & m[4-n];
        x = m[6-n] ^ x;
        x += K[n];
        x += work->Merkle[n];
        x += m[7-n];
        y = krotate(m[4-n], 26);
        z = krotate(m[4-n], 21);
        z = y^z;
        y = krotate(m[4-n], 7);
        z = y^z;
        m[7-n] = z+x;
        m[3-n] = m[3-n] + m[7-n];
        x = krotate(m[r(0)], 30);
        y = krotate(m[r(0)], 19);
        y = y^x;
        x = krotate(m[r(0)], 10);
        y = x^y;
        x = m[r(0)] | m[r(1)];
        x = m[r(2)] & x;
        z = m[r(0)] & m[r(1)];
        x = x | z;
        m[7-n] += y + x;

        PreCalc[2-n] = m[7-n];
        PreCalc[5-n] = m[3-n];
    }
}

int main(int argc, char **argv)
{
	int n;
	
	for(n = 0; n < sizeof(Work)/sizeof(WORKTASK); n++) {
		int i;
		
		cg_precalc_hash(Work[n].MidState, Work[n].Merkle);
		printf("CG PreCalc - [ %x, %x, %x, %x, %x, %x ]\n", PreCalc[0], PreCalc[1], PreCalc[2], PreCalc[3], PreCalc[4], PreCalc[5]);
		
		for(i = 0; i < 6; i++)
			hold[i] = PreCalc[i];
			
		K16AsicPreCalc(&Work[n]);
		printf("K16 PreCalc - [ %x, %x, %x, %x, %x, %x ]\n\n", PreCalc[0], PreCalc[1], PreCalc[2], PreCalc[3], PreCalc[4], PreCalc[5]);
		
		for(i = 0; i < 6; i++)
			if(hold[i] != PreCalc[i])
				printf("ERROR at [%d]\n", i);
	}
}
