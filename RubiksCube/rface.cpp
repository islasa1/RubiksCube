// Rubik's Cube Face

#include "rface.hpp"

#define ARR_TLEFT       (*pieces[0][0])
#define ARR_TOP         (*pieces[0][1])
#define ARR_TRIGHT      (*pieces[0][2])
#define ARR_LEFT        (*pieces[1][0])
#define ARR_CENTER      (*pieces[1][1])
#define ARR_RIGHT       (*pieces[1][2])
#define ARR_DLEFT       (*pieces[2][0])
#define ARR_DOWN        (*pieces[2][1])
#define ARR_DRIGHT      (*pieces[2][2])


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
	ARR_CENTER= c;
	ARR_TOP = t;
	ARR_DOWN = b;
	ARR_LEFT = l;
	ARR_RIGHT = r;
	ARR_TRIGHT =  tr;
	ARR_TLEFT = tl;
	ARR_DRIGHT = br;
	ARR_DLEFT= bl;
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
		tempEdgeFace = ((REdge*)ARR_TOP)->GetOtherFace(this->face);
		tempCornerFaces = ((RCorner*)ARR_TRIGHT)->GetOtherFaces(this->face);
		
		switch(rotation)
		{
			case CW_1:
			case CW_2:
				// Edges
				MoveEdge((REdge*)ARR_TOP, (REdge*)ARR_RIGHT);
				MoveEdge((REdge*)ARR_RIGHT, (REdge*)ARR_DOWN);
				MoveEdge((REdge*)ARR_DOWN, (REdge*)ARR_LEFT);
				MoveEdge((REdge*)ARR_LEFT, tempEdgeFace);
				
				// Corners
				MoveCorner((RCorner*)ARR_TRIGHT, (RCorner*)ARR_DRIGHT);
				MoveCorner((RCorner*)ARR_DRIGHT, (RCorner*)ARR_DLEFT);
				MoveCorner((RCorner*)ARR_DLEFT, (RCorner*)ARR_TLEFT);
				MoveCorner((RCorner*)ARR_TLEFT, tempCornerFaces);
				break;
			case CCW_1:
			case CCW_2:
				// Edges
				MoveEdge((REdge*)ARR_TOP, (REdge*)ARR_LEFT);
				MoveEdge((REdge*)ARR_LEFT, (REdge*)ARR_DOWN);
				MoveEdge((REdge*)ARR_DOWN, (REdge*)ARR_RIGHT);
				MoveEdge((REdge*)ARR_RIGHT, tempEdgeFace);
				
				
				// Corners
				MoveCorner((RCorner*)ARR_TRIGHT, (RCorner*)ARR_TLEFT);
				MoveCorner((RCorner*)ARR_TLEFT, (RCorner*)ARR_DLEFT);
				MoveCorner((RCorner*)ARR_DLEFT, (RCorner*)ARR_DRIGHT);
				MoveCorner((RCorner*)ARR_DRIGHT, tempCornerFaces);
				
				break;
			case R180_1:
			case R180_2:
				// Edges
				MoveEdge((REdge*)ARR_TOP, (REdge*)ARR_DOWN);
				MoveEdge((REdge*)ARR_DOWN, tempEdgeFace);
				
				tempEdgeFace = ((REdge*)ARR_LEFT)->GetOtherFace(this->face);
				MoveEdge((REdge*)ARR_LEFT, (REdge*)ARR_RIGHT);
				MoveEdge((REdge*)ARR_RIGHT, tempEdgeFace);
				
				// Corners
				MoveCorner((RCorner*)ARR_TRIGHT, (RCorner*)ARR_DRIGHT);
				MoveCorner((RCorner*)ARR_DRIGHT, (RCorner*)ARR_DLEFT);
				MoveCorner((RCorner*)ARR_DLEFT, (RCorner*)ARR_TLEFT);
				MoveCorner((RCorner*)ARR_TLEFT, tempCornerFaces);
				tempCornerFaces = ((RCorner*)ARR_TRIGHT)->GetOtherFaces(this->face);
				MoveCorner((RCorner*)ARR_TRIGHT, (RCorner*)ARR_DRIGHT);
				MoveCorner((RCorner*)ARR_DRIGHT, (RCorner*)ARR_DLEFT);
				MoveCorner((RCorner*)ARR_DLEFT, (RCorner*)ARR_TLEFT);
				MoveCorner((RCorner*)ARR_TLEFT, tempCornerFaces);
				
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

REdge& RFace::GetEdge(int row, int column) {
	return **((REdge**)pieces[row][column]);
}

RCorner& RFace::GetCorner(int row, int column) {
	return **((RCorner**)pieces[row][column]);
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

	r0.push_back(ARR_TLEFT->GetColor(this->face));
	r0.push_back(ARR_TOP->GetColor(this->face));
	r0.push_back(ARR_TRIGHT->GetColor(this->face));

	r1.push_back(ARR_LEFT->GetColor(this->face));
	r1.push_back(ARR_CENTER->GetColor(this->face));
	r1.push_back(ARR_RIGHT->GetColor(this->face));

	r2.push_back(ARR_DLEFT->GetColor(this->face));
	r2.push_back(ARR_DOWN->GetColor(this->face));
	r2.push_back(ARR_DRIGHT->GetColor(this->face));

	colors.push_back(r0);
	colors.push_back(r1);
	colors.push_back(r2);

	return colors;
}

void RFace::SetAllColors(rcolor_t color)
{
	ARR_CENTER->SetColor(this->face, color);

	ARR_TRIGHT->SetColor(this->face, color);
	ARR_TLEFT->SetColor(this->face, color);
	ARR_DRIGHT->SetColor(this->face, color);
	ARR_DLEFT->SetColor(this->face, color);

	ARR_TOP->SetColor(this->face, color);
	ARR_DOWN->SetColor(this->face, color);
	ARR_LEFT->SetColor(this->face, color);
	ARR_RIGHT->SetColor(this->face, color);
}

bool RFace::SetStickerColor(rcolor_t color, rposition_t pos)
{
	switch(pos)
	{
		case TLEFT:
			return ARR_TLEFT->SetColor(this->face, color);
		case TOP:
			return ARR_TOP->SetColor(this->face, color);
		case TRIGHT:
			return ARR_TRIGHT->SetColor(this->face, color);
		case LEFT:
			return ARR_LEFT->SetColor(this->face, color);
		case CENTER:
			return ARR_CENTER->SetColor(this->face, color);
		case RIGHT:
			return ARR_RIGHT->SetColor(this->face, color);
		case DLEFT:
			return ARR_DLEFT->SetColor(this->face, color);
		case DOWN:
			return ARR_DOWN->SetColor(this->face, color);
		case DRIGHT:
			return ARR_DRIGHT->SetColor(this->face, color);
		default :
			std::cout << "No such position found!" << std::endl;
			return false;	
	}
}

/*
std::ostream& operator<<(std::ostream& os, RFace& face)
{
	std::cout << "Row 1" << std::endl;
	std::cout << *(RCorner*)face.ARR_TLEFT << std::endl;
	std::cout << *(REdge*)face.ARR_TOP << std::endl;
	std::cout << *(RCorner*)face.ARR_TRIGHT << std::endl;
	std::cout << "Row 2" << std::endl;
	std::cout << *(REdge*)face.ARR_LEFT<< std::endl;
	std::cout << *(RARR_CENTER*)face.ARR_CENTER<< std::endl;
	std::cout << *(REdge*)face.ARR_RIGHT << std::endl;
	std::cout << "Row 3" << std::endl;
	std::cout << *(RCorner*)face.ARR_DLEFT<< std::endl;
	std::cout << *(REdge*)face.ARR_DOWN << std::endl;
	std::cout << *(RCorner*)face.ARR_DRIGHT<< std::endl;
}*/
