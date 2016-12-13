#ifndef MOVES
#define MOVES
#include "sticker.hpp"
#define U() this->RotateCW(WHITE);
#define UA() this->RotateCCW(WHITE);
#define U2() this->Rotate180(WHITE);
#define D() this->RotateCW(YELLOW);
#define DA() this->RotateCCW(YELLOW);
#define D2() this->Rotate180(YELLOW);
#define F() this->RotateCW(GREEN);
#define FA() this->RotateCCW(GREEN);
#define F2() this->Rotate180(GREEN);
#define B() this->RotateCW(BLUE);
#define BA() this->RotateCCW(BLUE);
#define B2() this->Rotate180(BLUE);
#define R() this->RotateCW(RED);
#define RA() this->RotateCCW(RED);
#define R2() this->Rotate180(RED);
#define L() this->RotateCW(ORANGE);
#define LA() this->RotateCCW(ORANGE);
#define L2() this->Rotate180(ORANGE);
#endif