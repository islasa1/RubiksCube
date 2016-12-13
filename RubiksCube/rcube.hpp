// Rubik's Cube 

// Set up in standard Western Color Scheme
/*
    WWW
    WWW
    WWW
OOO GGG RRR BBB 
OOO GGG RRR BBB   
OOO GGG RRR BBB
    YYY
	YYY
	YYY

   U
 L F R B
   D

   Face Numbers will be assigned based on Color number gotten from sticker.hpp
*/
#ifndef __RCUBE_H__
#define __RCUBE_H__

#ifdef OPENCV
#include "rcubeOpenCV.hpp"
#endif

#include <iostream>
#include <iomanip>
#include <vector>
#include <locale>
#include <algorithm>

#include "stringsplit.hpp"
#include "sticker.hpp"
#include "pieces.hpp"
#include "rface.hpp"
#include "moves.hpp"


class RCube
{
	private:
		std::vector<RFace> faces;
        
        // Is the face in question a casted face (OBY)
        // Part of how it was modeled
        bool isCasted(rcolor_t face);
        rposition_t getCastedPositionR(rposition_t pos);
        rposition_t getCastedPositionC(rposition_t pos);
	public:
		RCube();
		RCube(std::vector<RFace> f);
		void InitSolved();
		int Move(bool notation, std::string move);
        void BeginInteractive();
		REdge& GetEdge(rcolor_t face, int row, int column);
		RCorner& GetCorner(rcolor_t face, int row, int column);
    
        void RotateCW(rcolor_t face);
		void RotateCCW(rcolor_t face);
		void Rotate180(rcolor_t face);
    
        std::string SolveYellowGreen();
        std::string SolveYellowOrange();
        std::string SolveYellowBlue();
        std::string SolveYellowRed();
    
        bool SetStickerColor(rcolor_t face, rcolor_t color, rposition_t pos);
		
		friend std::ostream& operator<<(std::ostream& os, RCube& rcube);
#ifdef OPENCV    
        friend cv::Mat& operator<<(cv::Mat& mat, RCube& rcube);
        void ResetFace(rcolor_t face);
#endif
};

#endif