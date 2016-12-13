// Rubik's Cube Face

#ifndef __RFACE_H__
#define __RFACE_H__

#include <vector>
#include "sticker.hpp"
#include "pieces.hpp"

// Defined here to be used at top level
#define CW_1    (1)
#define CW_2    (-3)
#define CCW_1   (-1)
#define CCW_2   (3)
#define R180_1  (2)
#define R180_2  (-2)

// Positions
typedef enum RubiksPosition_Enum
{
	TLEFT = 0,
	TOP = 1,
	TRIGHT = 2,
	LEFT = 3,
	CENTER = 4,
	RIGHT = 5,
	DLEFT = 6,
	DOWN = 7,
	DRIGHT = 8
} rposition_t;


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
		bool SetStickerColor(rcolor_t color, rposition_t pos);
		REdge& GetEdge(int row, int column);
		RCorner& GetCorner(int row, int column);
		void RotateCW();
		void RotateCCW();
		void Rotate180();
		void Rotate(int rotation);
	
		//friend std::ostream& operator<<(std::ostream& os, RFace& face);
};
#endif