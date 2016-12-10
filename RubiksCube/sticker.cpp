// Sticker Class of a rubik's cube

#include "sticker.hpp"
Sticker::Sticker()
{
	this->color = BLACK;
	this->face = BLACK;
}

Sticker::Sticker(rcolor_t sColor, rcolor_t sFace)
{
	// A one-time only set color
	this->color = sColor;
	this->face = sFace;
}

Sticker::Sticker(rcolor_t sFace)
{
	this->face = sFace;
	this->color = BLACK;
}

void Sticker::SetFace(rcolor_t sFace)
{
	this->face = sFace;
}

void Sticker::SetColor(rcolor_t sColor)
{
	if (this->color == BLACK)
	{
		this->color = sColor;
	}
	else
	{
		std::cout << "Error: Cannot set sticker color more than once." << std::endl;
	}
}

rcolor_t Sticker::GetFace()
{
	return this->face;
}

rcolor_t Sticker::GetColor()
{
	return this->color;
}
