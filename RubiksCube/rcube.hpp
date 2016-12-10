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

#include <iostream>
#include <iomanip>
#include <vector>
#include <locale>
#include <algorithm>

#include "stringsplit.hpp"
#include "sticker.hpp"
#include "pieces.hpp"
#include "rface.hpp"


class RCube
{
	private:
		std::vector<RFace> faces;
        
        // Is the face in question a casted face (OBY)
        // Part of how it was modeled
        bool isCasted(rcolor_t face);
	public:
		RCube();
		RCube(std::vector<RFace> f);
		void InitSolved();
		int Move(bool notation);
        void BeginInteractive();
    
        void RotateCW(rcolor_t face);
		void RotateCCW(rcolor_t face);
		void Rotate180(rcolor_t face);
		
		friend std::ostream& operator<<(std::ostream& os, RCube& rcube);
};

#endif