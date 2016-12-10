// Sticker Class of a rubik's cube

#ifndef __RSTICKER_H__
#define __RSTICKER_H__

#include <iostream>

// Sticker Colors of a standard Western Style Rubik's Cube
typedef enum RubiksColor_Enum
{	
	WHITE = 0,
	YELLOW = 1,
	GREEN = 2,
	BLUE = 3,
	RED = 4,
	ORANGE = 5,
	BLACK = 6
} rcolor_t;

// Apparently must be in header to work
inline std::ostream& operator<<(std::ostream& os, RubiksColor_Enum rc)
{
	switch (rc)
	{
	case WHITE:
		os << 'W';
		break;
	case YELLOW:
		os << 'Y';
		break;
	case GREEN:
		os << 'G';
		break;
	case BLUE:
		os << 'B';
		break;
	case RED:
		os << 'R';
		break;
	case ORANGE:
		os << 'O';
		break;
	case BLACK:
		os << 'X';
		break;
	default:
		os << "Error: Unsupported color" << std::endl;
		break;
	}
	return os;
}

class Sticker
{
	private:
		// Color should never change
		rcolor_t color;

		// Allowed to change based on rotation
		rcolor_t face;

	public:
		// Explicit constructor
		Sticker();
		Sticker(rcolor_t sColor, rcolor_t sFace);
		Sticker(rcolor_t sFace);
		void SetFace(rcolor_t sFace);
		void SetColor(rcolor_t sColor);
		rcolor_t GetFace();
		rcolor_t GetColor();
};

#endif