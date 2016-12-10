// Rubik's Cube Face

#ifndef __RFACE_H__
#define __RFACE_H__

#include <vector>
#include "sticker.hpp"
#include "pieces.hpp"

// Defined here to be used at top level
#define CW_1    (1)
#define CW_2    (-3)
#define CCW_1  (-1)
#define CCW_2  (3)
#define R180_1  (2)
#define R180_2  (-2)

class RFace
{
	private:
		rcolor_t face;
		RPiece** pieces[3][3];
	
		void MoveEdge(REdge* posOld, REdge* posNew);
		void MoveEdge(REdge* posOld, rcolor_t newFace);
		void MoveCorner(RCorner* posOld, RCorner* posNew);
		void MoveCorner(RCorner* posOld, std::vector<rcolor_t> newFaces);
	
	public:
		void InitPositions(RPiece** c, RPiece** t, RPiece** b, RPiece** l, RPiece** r, RPiece** tl, RPiece** tr, RPiece** bl, RPiece** br);
		void InitPieces(RCenter* c, REdge* t, REdge* b, REdge* l, REdge* r, RCorner* tl, RCorner* tr, RCorner* bl, RCorner* br);
		std::vector<std::vector<rcolor_t> > GetColors();
		void SetAllColors(rcolor_t color);
		void RotateCW();
		void RotateCCW();
		void Rotate180();
		void Rotate(int rotation);
	
		//friend std::ostream& operator<<(std::ostream& os, RFace& face);
};
#endif