// Rubik's Cube Face

#include "rface.hpp"

#define CENTER	(*pieces[1][1])
#define TLEFT	  (*pieces[0][0])
#define TRIGHT	(*pieces[0][2])
#define DLEFT	  (*pieces[2][0])
#define DRIGHT	(*pieces[2][2])
#define TOP			(*pieces[0][1])
#define DOWN		(*pieces[2][1])
#define LEFT		(*pieces[1][0])
#define RIGHT		(*pieces[1][2])


void RFace::InitPositions(RPiece** c, RPiece** t, RPiece** b, RPiece** l, RPiece** r, RPiece** tl, RPiece** tr, RPiece** bl, RPiece** br)
{
	pieces[1][1] = c;
	pieces[0][1] = t;
	pieces[2][1] = b;
	pieces[1][0] = l;
	pieces[1][2] = r;
	pieces[0][2] = tr;
	pieces[0][0] = tl;
	pieces[2][2] = br;
	pieces[2][0] = bl;
}

void RFace::InitPieces(RCenter* c, REdge* t, REdge* b, REdge* l, REdge* r, RCorner* tl, RCorner* tr, RCorner* bl, RCorner* br)
{	
	this->face = c->GetFace();
	CENTER= c;
	TOP = t;
	DOWN = b;
	LEFT = l;
	RIGHT = r;
	TRIGHT =  tr;
	TLEFT = tl;
	DRIGHT = br;
	DLEFT= bl;
}

// Rotation - the majority of logic
void RFace::Rotate(int rotation)
{
	RPiece* temp[3][3];
	rotation %= 4;
	int i,j;
	int max = 3;

	// Rotate
	for(i = 0; i < max; i++)
	{
		for(j = 0; j < max; j++)
		{
			switch(rotation)
			{
				case CW_1:
				case CW_2:
					temp[j][i] = *(this->pieces[max - i - 1][j]);
					
					break;
				case R180_1:
				case R180_2:
					temp[j][i] = (*this->pieces[max - j - 1][max - i - 1]);
					break;
				case CCW_1:
				case CCW_2:
					temp[j][i] = (*this->pieces[i][max - j - 1]);
					break;
				case 0: // Do nothing
					temp[i][j] = (*this->pieces[i][j]);
			}
		}
	}
	
	// Fix
	if(rotation != 0)
	{
		rcolor_t tempEdgeFace;
		std::vector<rcolor_t> tempCornerFaces;
		tempEdgeFace = ((REdge*)TOP)->GetOtherFace(this->face);
		tempCornerFaces = ((RCorner*)TRIGHT)->GetOtherFaces(this->face);
		
		switch(rotation)
		{
			case CW_1:
			case CW_2:
				// Edges
				MoveEdge((REdge*)TOP, (REdge*)RIGHT);
				MoveEdge((REdge*)RIGHT, (REdge*)DOWN);
				MoveEdge((REdge*)DOWN, (REdge*)LEFT);
				MoveEdge((REdge*)LEFT, tempEdgeFace);
				
				// Corners
				MoveCorner((RCorner*)TRIGHT, (RCorner*)DRIGHT);
				MoveCorner((RCorner*)DRIGHT, (RCorner*)DLEFT);
				MoveCorner((RCorner*)DLEFT, (RCorner*)TLEFT);
				MoveCorner((RCorner*)TLEFT, tempCornerFaces);
				break;
			case CCW_1:
			case CCW_2:
				// Edges
				MoveEdge((REdge*)TOP, (REdge*)LEFT);
				MoveEdge((REdge*)LEFT, (REdge*)DOWN);
				MoveEdge((REdge*)DOWN, (REdge*)RIGHT);
				MoveEdge((REdge*)RIGHT, tempEdgeFace);
				
				
				// Corners
				MoveCorner((RCorner*)TRIGHT, (RCorner*)TLEFT);
				MoveCorner((RCorner*)TLEFT, (RCorner*)DLEFT);
				MoveCorner((RCorner*)DLEFT, (RCorner*)DRIGHT);
				MoveCorner((RCorner*)DRIGHT, tempCornerFaces);
				
				break;
			case R180_1:
			case R180_2:
				// Edges
				MoveEdge((REdge*)TOP, (REdge*)DOWN);
				MoveEdge((REdge*)DOWN, tempEdgeFace);
				
				tempEdgeFace = ((REdge*)LEFT)->GetOtherFace(this->face);
				MoveEdge((REdge*)LEFT, (REdge*)RIGHT);
				MoveEdge((REdge*)RIGHT, tempEdgeFace);
				
				// Corners
				MoveCorner((RCorner*)TRIGHT, (RCorner*)DRIGHT);
				MoveCorner((RCorner*)DRIGHT, (RCorner*)DLEFT);
				MoveCorner((RCorner*)DLEFT, (RCorner*)TLEFT);
				MoveCorner((RCorner*)TLEFT, tempCornerFaces);
				tempCornerFaces = ((RCorner*)TRIGHT)->GetOtherFaces(this->face);
				MoveCorner((RCorner*)TRIGHT, (RCorner*)DRIGHT);
				MoveCorner((RCorner*)DRIGHT, (RCorner*)DLEFT);
				MoveCorner((RCorner*)DLEFT, (RCorner*)TLEFT);
				MoveCorner((RCorner*)TLEFT, tempCornerFaces);
				
				break;
		}
	}
	
	// Re-assign
	for(i = 0; i < max; i++)
	{
		for(j = 0; j < max; j++)
		{
			*this->pieces[i][j] = temp[i][j];
		}
	}
}

// Pos Old assumes position of Pos New, but Pos New is never modified
void RFace::MoveEdge(REdge* posOld, REdge* posNew)
{
	rcolor_t newFace = posNew->GetOtherFace(this->face);
	rcolor_t oldFace = posOld->GetOtherFace(this->face);
	
	posOld->SetFace(oldFace, newFace);
}

void RFace::MoveEdge(REdge* posOld, rcolor_t newFace)
{
	rcolor_t oldFace = posOld->GetOtherFace(this->face);
	posOld->SetFace(oldFace, newFace);
}

void RFace::MoveCorner(RCorner* posOld, RCorner* posNew)
{
	std::vector<rcolor_t> oldFaces, newFaces;
	oldFaces = posOld->GetOtherFaces(this->face);
	newFaces = posNew->GetOtherFaces(this->face);
	rcolor_t commonFace, shiftAway, shiftTo;
	
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			if(oldFaces[i] == newFaces[j])
			{
				commonFace = oldFaces[i];
				shiftAway = oldFaces[(i + 1) % 2];
				shiftTo = newFaces[(j + 1) % 2];
				break;
			}
		}
	}
	
	posOld->SetFace(commonFace, shiftTo);
	posOld->SetFace(shiftAway, commonFace);
}

void RFace::MoveCorner(RCorner* posOld, std::vector<rcolor_t> newFaces)
{
	std::vector<rcolor_t> oldFaces;
	oldFaces = posOld->GetOtherFaces(this->face);
	rcolor_t commonFace, shiftAway, shiftTo;
	
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			if(oldFaces[i] == newFaces[j])
			{
				commonFace = oldFaces[i];
				shiftAway = oldFaces[(i + 1) % 2];
				shiftTo = newFaces[(j + 1) % 2];
				break;
			}
		}
	}
	
	posOld->SetFace(commonFace, shiftTo);
	posOld->SetFace(shiftAway, commonFace);
}

void RFace::RotateCW()
{
	this->Rotate(CW_1);	
}

void RFace::RotateCCW()
{
	this->Rotate(CCW_1);
}

void RFace::Rotate180()
{
	this->Rotate(R180_1);
}

std::vector<std::vector<rcolor_t> > RFace::GetColors()
{
	std::vector<std::vector<rcolor_t> > colors;

	std::vector<rcolor_t> r0;
	std::vector<rcolor_t> r1;
	std::vector<rcolor_t> r2;

	r0.push_back(TLEFT->GetColor(this->face));
	r0.push_back(TOP->GetColor(this->face));
	r0.push_back(TRIGHT->GetColor(this->face));

	r1.push_back(LEFT->GetColor(this->face));
	r1.push_back(CENTER->GetColor(this->face));
	r1.push_back(RIGHT->GetColor(this->face));

	r2.push_back(DLEFT->GetColor(this->face));
	r2.push_back(DOWN->GetColor(this->face));
	r2.push_back(DRIGHT->GetColor(this->face));

	colors.push_back(r0);
	colors.push_back(r1);
	colors.push_back(r2);

	return colors;
}

void RFace::SetAllColors(rcolor_t color)
{
	CENTER->SetColor(this->face, color);

	TRIGHT->SetColor(this->face, color);
	TLEFT->SetColor(this->face, color);
	DRIGHT->SetColor(this->face, color);
	DLEFT->SetColor(this->face, color);

	TOP->SetColor(this->face, color);
	DOWN->SetColor(this->face, color);
	LEFT->SetColor(this->face, color);
	RIGHT->SetColor(this->face, color);
}

/*
std::ostream& operator<<(std::ostream& os, RFace& face)
{
	std::cout << "Row 1" << std::endl;
	std::cout << *(RCorner*)face.TLEFT << std::endl;
	std::cout << *(REdge*)face.TOP << std::endl;
	std::cout << *(RCorner*)face.TRIGHT << std::endl;
	std::cout << "Row 2" << std::endl;
	std::cout << *(REdge*)face.LEFT<< std::endl;
	std::cout << *(RCenter*)face.CENTER<< std::endl;
	std::cout << *(REdge*)face.RIGHT << std::endl;
	std::cout << "Row 3" << std::endl;
	std::cout << *(RCorner*)face.DLEFT<< std::endl;
	std::cout << *(REdge*)face.DOWN << std::endl;
	std::cout << *(RCorner*)face.DRIGHT<< std::endl;
}*/
