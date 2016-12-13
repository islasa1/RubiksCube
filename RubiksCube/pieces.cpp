
#include "pieces.hpp"

//***********************************************
//
// Rubik's Cube Edge Piece
//
//***********************************************
RCenter::RCenter(Sticker sticker)
{
	this->sticker = sticker;
}

rcolor_t RCenter::GetColor(rcolor_t sFace)
{
	if (this->sticker.GetFace() == sFace)
	{
		return this->sticker.GetColor();
	}
	else
	{
		std::cout << "Error: Piece does not have a sticker on face " << sFace << std::endl;
		return (rcolor_t)-1;
	}
}

rcolor_t RCenter::GetFace()
{
	return this->sticker.GetFace();	
}

bool RCenter::SetColor(rcolor_t sFace, rcolor_t sColor)
{
	if (this->sticker.GetFace() == sFace)
	{
		return this->sticker.SetColor(sColor);
	}
	else
	{
		std::cout << "Error: Piece does not have a sticker on face " << sFace << std::endl;
		return false;
	}
}


std::ostream& operator<<(std::ostream& os, RCenter& piece)
{
	os << piece.sticker.GetColor();
	return os;
}


//***********************************************
//
// Rubik's Cube Edge Piece
//
//***********************************************

REdge::REdge(Sticker s1, Sticker s2)
{
	this->sticker1 = s1;
	this->sticker2 = s2;
}

rcolor_t REdge::GetColor(rcolor_t sFace)
{
	if (this->sticker1.GetFace() == sFace)
	{
		return this->sticker1.GetColor();
	}
	else if (this->sticker2.GetFace() == sFace)
	{
		return this->sticker2.GetColor();
	}
	else
	{
		std::cout << "Error: Piece does not have a sticker on face " << sFace << std::endl;
		return (rcolor_t)-1;
	}
}


bool REdge::SetColor(rcolor_t sFace, rcolor_t sColor)
{
	if (this->sticker1.GetFace() == sFace)
	{
		return this->sticker1.SetColor(sColor);
	}
	else if (this->sticker2.GetFace() == sFace)
	{
		return this->sticker2.SetColor(sColor);
	}
	else
	{
		std::cout << "Error: Piece does not have a sticker on face " << sFace << std::endl;
		return false;
	}
}

void REdge::SetFace(rcolor_t oldFace, rcolor_t newFace)
{
	if (this->sticker1.GetFace() == oldFace)
	{
		this->sticker1.SetFace(newFace);
	}
	else if (this->sticker2.GetFace() == oldFace)
	{
		this->sticker2.SetFace(newFace);
	}
	else
	{
		std::cout << "Error: Piece does not have a sticker on face " << oldFace << std::endl;
		return;
	}
}

rcolor_t REdge::GetOtherFace(rcolor_t sFace)
{
	if (this->sticker1.GetFace() == sFace)
	{
		return this->sticker2.GetFace();
	}
	else if (this->sticker2.GetFace() == sFace)
	{
		return this->sticker1.GetFace();
	}
	else
	{
		std::cout << "Error: Piece does not have a sticker on face " << sFace << std::endl;
		return BLACK;
	}
}

std::ostream& operator<<(std::ostream& os, REdge& piece)
{
	os << piece.sticker1.GetColor() << " | " << piece.sticker2.GetColor();
	return os;
}


//***********************************************
//
// Rubik's Cube Corner Piece
//
//***********************************************

RCorner::RCorner(Sticker s1, Sticker s2, Sticker s3)
{
	this->sticker1 = s1;
	this->sticker2 = s2;
	this->sticker3 = s3;
}

rcolor_t RCorner::GetColor(rcolor_t sFace)
{
	if (this->sticker1.GetFace() == sFace)
	{
		return this->sticker1.GetColor();
	}
	else if (this->sticker2.GetFace() == sFace)
	{
		return this->sticker2.GetColor();
	}
	else if (this->sticker3.GetFace() == sFace)
	{
		return this->sticker3.GetColor();
	}
	else
	{
		std::cout << "Error: Piece does not have a sticker on face " << sFace << std::endl;
		return (rcolor_t)-1;
	}
}

bool RCorner::SetColor(rcolor_t sFace, rcolor_t sColor)
{
	if (this->sticker1.GetFace() == sFace)
	{
		return this->sticker1.SetColor(sColor);
	}
	else if (this->sticker2.GetFace() == sFace)
	{
		return this->sticker2.SetColor(sColor);
	}
	else if (this->sticker3.GetFace() == sFace)
	{
		return this->sticker3.SetColor(sColor);
	}
	else
	{
		std::cout << "Error: Piece does not have a sticker on face " << sFace << std::endl;
		return false;
	}
}

void RCorner::SetFace(rcolor_t oldFace, rcolor_t newFace)
{
	if (this->sticker1.GetFace() == oldFace)
	{
		this->sticker1.SetFace(newFace);
	}
	else if (this->sticker2.GetFace() == oldFace)
	{
		this->sticker2.SetFace(newFace);
	}
	else if (this->sticker3.GetFace() == oldFace)
	{
		this->sticker3.SetFace(newFace);
	}
	else
	{
		std::cout << "Error: Piece does not have a sticker on face " << oldFace << std::endl;
		return;
	}
}

std::vector<rcolor_t> RCorner::GetOtherFaces(rcolor_t sFace)
{
	std::vector<rcolor_t> res;
	rcolor_t temp; // used to stop redundant call to GetFace()
	if ((temp = this->sticker1.GetFace()) != sFace)
	{
		res.push_back(temp);
	}
	if ((temp = this->sticker2.GetFace()) != sFace)
	{
		res.push_back(temp);
	}
	if ((temp = this->sticker3.GetFace()) != sFace)
	{
		res.push_back(temp);
	}
	if(res.size() == 3) // all were added
	{
		std::cout << "Error: Piece does not have a sticker on face " << sFace << std::endl;
	}
	
	return res;
}


std::ostream& operator<<(std::ostream& os, RCorner& piece)
{
	os << piece.sticker1.GetColor() << " | " << piece.sticker2.GetColor() << " | " << piece.sticker3.GetColor();
	return os;
}
