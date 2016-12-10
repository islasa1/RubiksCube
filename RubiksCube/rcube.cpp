
#include "rcube.hpp"


rcolor_t StringToRColor(std::string s, bool stdNotation)
{
	if(s == "GREEN" || (stdNotation && s[0] == 'F'))
		return GREEN;
	else if(s == "BLUE" || (stdNotation && s[0] == 'B'))
		return BLUE;
	else if(s == "WHITE" || (stdNotation && s[0] == 'U'))
		return WHITE;
	else if(s == "YELLOW" || (stdNotation && s[0] == 'D'))
		return YELLOW;
	else if(s == "RED" || (stdNotation && s[0] == 'R'))
		return RED;
	else if(s == "ORANGE" || (stdNotation && s[0] == 'L'))
		return ORANGE;
	else
	{
		std::cout << "Error: Cannot convert " << s << " to a defined Rubiks Color." << std::endl;
		return BLACK;
	}
}

RCube::RCube()
{
	std::vector<Sticker> s;

	for (int i = 0; i < 6; i++)
	{
		s.push_back(Sticker((rcolor_t)i));
	}

	// Upper Top/Bottom Left/Right Corners
	RCorner* ubr = new RCorner(s[WHITE], s[RED], s[GREEN]);
	RPiece** pubr = new RPiece*;
	
	RCorner* ubl = new RCorner(s[WHITE], s[ORANGE], s[GREEN]);
	RPiece** publ = new RPiece*;
	
	RCorner* utr = new RCorner(s[WHITE], s[RED], s[BLUE]);
	RPiece** putr = new RPiece*;
	
	RCorner* utl = new RCorner(s[WHITE], s[ORANGE], s[BLUE]);
	RPiece** putl = new RPiece*;

	// Down Top/Bottom Left/Right (inverse above) Corners
	RCorner* dbr = new RCorner(s[YELLOW], s[RED], s[GREEN]);
	RPiece** pdbr = new RPiece*;
	
	RCorner* dbl = new RCorner(s[YELLOW], s[ORANGE], s[GREEN]);
	RPiece** pdbl = new RPiece*;
	
	RCorner* dtr = new RCorner(s[YELLOW], s[RED], s[BLUE]);
	RPiece** pdtr = new RPiece*;
	
	RCorner* dtl = new RCorner(s[YELLOW], s[ORANGE], s[BLUE]);
	RPiece** pdtl = new RPiece*;
	

	// Upper Top/Bottom/Right/Left
	REdge* ut = new REdge(s[WHITE], s[BLUE]);
	RPiece** put = new RPiece*;
	
	REdge* ub = new REdge(s[WHITE], s[GREEN]);
	RPiece** pub = new RPiece*;
	
	REdge* ur = new REdge(s[WHITE], s[RED]);
	RPiece** pur = new RPiece*;
	
	REdge* ul = new REdge(s[WHITE], s[ORANGE]);
	RPiece** pul = new RPiece*;
	

	// Upper Top/Bottom/Right/Left
	REdge* dt = new REdge(s[YELLOW], s[BLUE]);
	RPiece** pdt = new RPiece*;
	
	REdge* db = new REdge(s[YELLOW], s[GREEN]);
	RPiece** pdb = new RPiece*;
	
	REdge* dr = new REdge(s[YELLOW], s[RED]);
	RPiece** pdr = new RPiece*;
	
	REdge* dl = new REdge(s[YELLOW], s[ORANGE]);
	RPiece** pdl = new RPiece*;
	

	// Remaining edges, with respect to F/B
	REdge* fl = new REdge(s[GREEN], s[ORANGE]);
	RPiece** pfl = new RPiece*;
	
	REdge* fr = new REdge(s[GREEN], s[RED]);
	RPiece** pfr = new RPiece*;
	
	REdge* bl = new REdge(s[BLUE], s[ORANGE]);
	RPiece** pbl = new RPiece*;
	
	REdge* br = new REdge(s[BLUE], s[RED]);
	RPiece** pbr = new RPiece*;
	
	
	// Centers
	RCenter* cw = new RCenter(s[WHITE]);
	RPiece** pcw = new RPiece*;
	
	RCenter* cy = new RCenter(s[YELLOW]);
	RPiece** pcy = new RPiece*;
	
	RCenter* cg = new RCenter(s[GREEN]);
	RPiece** pcg = new RPiece*;
	
	RCenter* cb = new RCenter(s[BLUE]);
	RPiece** pcb = new RPiece*;
	
	RCenter* cr = new RCenter(s[RED]);
	RPiece** pcr = new RPiece*;
	
	RCenter* co = new RCenter(s[ORANGE]);
	RPiece** pco = new RPiece*;
	

	// Now make faces
	RFace wFace; 
	RFace yFace;
	RFace gFace;
	RFace bFace;
	RFace rFace; 
	RFace oFace;
	
	// init positioning
	wFace.InitPositions(pcw, put, pub, pul, pur, putl, putr, publ, pubr);
	yFace.InitPositions(pcy, pdt, pdb, pdl, pdr, pdtl, pdtr, pdbl, pdbr);
	gFace.InitPositions(pcg, pub, pdb, pfl, pfr, publ, pubr, pdbl, pdbr);
	bFace.InitPositions(pcb, put, pdt, pbl, pbr, putl, putr, pdtl, pdtr);
	rFace.InitPositions(pcr, pur, pdr, pfr, pbr, pubr, putr, pdbr, pdtr);
	oFace.InitPositions(pco, pul, pdl, pfl, pbl, publ, putl, pdbl, pdtl);
	
	wFace.InitPieces(cw, ut, ub, ul, ur, utl, utr, ubl, ubr);
	yFace.InitPieces(cy, dt, db, dl, dr, dtl, dtr, dbl, dbr);
	gFace.InitPieces(cg, ub, db, fl, fr, ubl, ubr, dbl, dbr);
	bFace.InitPieces(cb, ut, dt, bl, br, utl, utr, dtl, dtr);
	rFace.InitPieces(cr, ur, dr, fr, br, ubr, utr, dbr, dtr);
	oFace.InitPieces(co, ul, dl, fl, bl, ubl, utl, dbl, dtl);

	this->faces.push_back(wFace);
	this->faces.push_back(yFace);
	this->faces.push_back(gFace);
	this->faces.push_back(bFace);
	this->faces.push_back(rFace);
	this->faces.push_back(oFace);
}

void RCube::InitSolved()
{
	// Go to all and set colors
	for (int i = 0; i < 6; i++)
	{
		this->faces[i].SetAllColors((rcolor_t)i);
	}
}

RCube::RCube(std::vector<RFace> f)
{
	this->faces = f;
}

// Important b/c casted faces rotate opposite
bool RCube::isCasted(rcolor_t face)
{
	return face == ORANGE || face == BLUE || face == YELLOW;	
}

void RCube::RotateCW(rcolor_t face)
{
	bool casted = isCasted(face);
	
	if(casted)
	{
		this->faces[face].RotateCCW();
	}
	else
	{
		this->faces[face].RotateCW();
	}
}

void RCube::RotateCCW(rcolor_t face)
{
	bool casted = isCasted(face);
	
	if(casted)
	{
		this->faces[face].RotateCW();
	}
	else
	{
		this->faces[face].RotateCCW();
	}
}

void RCube::Rotate180(rcolor_t face)
{
	this->faces[face].Rotate180();
}

int RCube::Move(bool stdNotation)
{
	if(stdNotation)
	{
		std::cout << "Enter Move: ";
	}
	else
	{
		std::cout << "Enter Move (FACE (CW | CCW | 180): ";
	}
	
	std::string move;
	std::getline(std::cin, move);
	std::vector<std::string> moveParts = split(move, ' ');
	
	if(moveParts.size() == 1 && moveParts[0] == "s")
	{
		return 1; // switch notation
	}
	else if(moveParts.size() != 2 && !stdNotation)
	{
		std::cout << "Error: Incorrect move format. Must be FACE (CW | CCW | 180) => e.g. GREEN CCW or WHITE 180" << std::endl;
		return -1;
	}
	else
	{
		int rotate = 0;
		rcolor_t face = BLACK;
		
		std::transform(moveParts[0].begin(), moveParts[0].end(), moveParts[0].begin(), ::toupper);
		if(!stdNotation)
		{
			std::transform(moveParts[1].begin(), moveParts[1].end(), moveParts[1].begin(), ::toupper);
		}
		
		face = StringToRColor(moveParts[0], stdNotation);
		if(face == BLACK)
		{
			std::cout << "Error: Incorrect color format. Must be FACE (CW | CCW | 180) => e.g. GREEN CCW or WHITE 180" << std::endl;
			return -1;
		}
		
		if((stdNotation && moveParts[0].size() == 1) || (moveParts.size() ==  2 && moveParts[1] == "CW"))
			rotate = CW_1;
		else if((stdNotation && moveParts[0].size() ==  2 && (moveParts[0])[1] == '\'') || (moveParts.size() ==  2 && moveParts[1] == "CCW"))
			rotate = CCW_1;
		else if((stdNotation && moveParts[0].size() == 2 && (moveParts[0])[1] == '2') || (moveParts.size() ==  2 && moveParts[1] == "180"))
			rotate = R180_1;
		else
		{
			if(stdNotation)
				std::cout << "Please use standard Rubik\'s Cube Notation" << std::endl;
			else
				std::cout << "Error: Incorrect rotation format. Must be FACE (CW | CCW | 180) => e.g. GREEN CCW or WHITE 180" << std::endl;
			return -1;
		}
		
		
		
		
		// Move is OK
		switch(rotate)
		{
			case CW_1:
				this->RotateCW(face);
				break;
			case CCW_1:
				this->RotateCCW(face);
				break;
			case R180_1:
				this->Rotate180(face);
				break;
		}
		
		return 0;
	}
}

void RCube::BeginInteractive()
{
	std::cout << "To quit, enter an incorrect move. " << std::endl;
	int move = 0;
	bool note = false;
	while(move != -1)
	{
		std::cout << *this;
		move = this->Move(note);
		
		if(move == 1)
			note = !note;
	}
}

std::ostream& operator<<(std::ostream& os, RCube& rcube)
{
	std::vector<std::vector<rcolor_t> > faceColors0;
	
	faceColors0 = rcube.faces[WHITE].GetColors();
	for (int i = 0; i < 3; i++)
	{
		os << "    ";
		for (int j = 0; j < 3; j++)
		{
			os << faceColors0[i][j];
		}
		os << std::endl;
	}

	faceColors0 = rcube.faces[ORANGE].GetColors();
	std::vector<std::vector<rcolor_t> > faceColors1 = rcube.faces[GREEN].GetColors();
	std::vector<std::vector<rcolor_t> > faceColors2 = rcube.faces[RED].GetColors();
	std::vector<std::vector<rcolor_t> > faceColors3 = rcube.faces[BLUE].GetColors();

	for (int i = 0; i < 3; i++)
	{
		// Mirror projected faces ORANGE and BLUE when unravelling
		os  << faceColors0[i][2]
			<< faceColors0[i][1]
			<< faceColors0[i][0] << " " 

			<< faceColors1[i][0]
			<< faceColors1[i][1]
			<< faceColors1[i][2] << " "

			<< faceColors2[i][0]
			<< faceColors2[i][1]
			<< faceColors2[i][2] << " "

			<< faceColors3[i][2]
			<< faceColors3[i][1]
			<< faceColors3[i][0] << std::endl;
	}

	faceColors0 = rcube.faces[YELLOW].GetColors();
	
	// Mirror projected face
	for (int i = 0; i < 3; i++)
	{
		os << "    ";
		for (int j = 0; j < 3; j++)
		{
			os << faceColors0[2 - i][j];
		}
		os << std::endl;
	}

	return os;
}