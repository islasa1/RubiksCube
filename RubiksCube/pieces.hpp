// Set of all pieces used to create a Rubik's Cube
// 3 Types, all bundled into one main class for file
// clustering sake, and all 3 are necessary

#ifndef __RPIECES_H__
#define __RPIECES_H__

#include <iostream>
#include <vector>

#include "sticker.hpp"

class RPiece
{
	public:
		virtual rcolor_t GetColor(rcolor_t sFace) = 0;
		virtual void SetColor(rcolor_t sFace, rcolor_t sColor) = 0;
};

// Center of Rubik's Cube Face
class RCenter : public RPiece
{
	private:
		Sticker sticker;
	public:
		RCenter(Sticker sticker);
		rcolor_t GetColor(rcolor_t sFace);
		rcolor_t GetFace();
		void SetColor(rcolor_t sFace, rcolor_t sColor);
		friend std::ostream& operator<<(std::ostream& os, RCenter&);
};

// Edge of Rubiks Cube Face
class REdge : public RPiece
{
	private:
		Sticker sticker1;
		Sticker sticker2;
	public:
		REdge(Sticker s1, Sticker s2);
		rcolor_t GetColor(rcolor_t sFace);
		void SetColor(rcolor_t sFace, rcolor_t sColor);
		void SetFace(rcolor_t oldFace, rcolor_t newFace);
		
		rcolor_t GetOtherFace(rcolor_t sFace);
		
		friend std::ostream& operator<<(std::ostream& os, REdge&);
};

// Corner of Rubik's Cube Face
class RCorner : public RPiece
{
	private:
		Sticker sticker1;
		Sticker sticker2;
		Sticker sticker3;
	public:
		RCorner(Sticker s1, Sticker s2, Sticker s3);
		rcolor_t GetColor(rcolor_t sFace);
		void SetColor(rcolor_t sFace, rcolor_t sColor);
		void SetFace(rcolor_t oldFace, rcolor_t newFace);
		
		std::vector<rcolor_t> GetOtherFaces(rcolor_t sFace);
		
		
		friend std::ostream& operator<<(std::ostream& os, RCorner&);
};

#endif
