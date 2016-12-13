
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

REdge& RCube::GetEdge(rcolor_t face, int row, int column)
{
	return this->faces[face].GetEdge(row, column);
}

RCorner& RCube::GetCorner(rcolor_t face, int row, int column)
{
	return this->faces[face].GetCorner(row, column);
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

int RCube::Move(bool stdNotation, std::string move)
{
	if(move.compare("solve") == 0) {
        std::cout << this->SolveYellowGreen();
        std::cout << this->SolveYellowOrange();
        std::cout << this->SolveYellowBlue();
        std::cout << this->SolveYellowRed();
        std::cout << std::endl;
        return 0;
    }
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
	int moveRtn = 0;
	bool note = false;
	#ifndef OPENCV
	std::cout << "To quit, enter an incorrect move. " << std::endl;
	while(moveRtn != -1)
	{
		std::cout << *this;
		if(note)
		{
			std::cout << "Enter Move: ";
		}
		else
		{
			std::cout << "Enter Move (FACE (CW | CCW | 180): ";
		}

		std::string move;
		std::getline(std::cin, move);
		
		moveRtn = this->Move(note, move);
		
		if(moveRtn == 1)
			note = !note;
	}
	#else
	
	const char * rubiksWindow = "Internal Model";
    cv::Mat cubeMat(STICKER_SIZE*(9 + 3), STICKER_SIZE*(12+3), CV_8UC3);
	cubeMat.setTo(cv::Scalar(255,255,255));
    cv::namedWindow( rubiksWindow, CV_WINDOW_AUTOSIZE );
	std::vector<char> moveChars;
	
	while(moveRtn >= -1)
	{
        cubeMat << (*this);
        imshow(rubiksWindow, cubeMat);
		
		char c = cvWaitKey(10);
		
		if(c != -1)
		{
			// Process
			if(c == '*') // Read in
			{
				assignRCubeCV(*this);
			}
			else if(c == 'i')
			{
				this->InitSolved();
			}
			else if(c == 'q' || c == 27)
			{
				break;
			}
			else if (c > 0 && c < 256 && c != '\n') // ASCII
			{
				moveChars.push_back(c);
				std::cout << c;
			}
			else if(c == '\n' && moveChars.size() > 0)
			{
				// Make a move
				std::cout << std::endl;
				std::string move(moveChars.begin(), moveChars.end());
				moveRtn = this->Move(note, move);
				moveChars.clear();
				if(moveRtn == 1)
					note = !note;
			}
		}
	}
	
	#endif
}

bool RCube::SetStickerColor(rcolor_t face, rcolor_t color, rposition_t pos)
{
	bool casted = this->isCasted(face);
	
	if(casted)
	{
		if(face == YELLOW)
		{
			// Shift about center row (TOP -> DOWN and vice versa)
			pos = this->getCastedPositionR(pos);
		}
		else // BLUE or ORANGE
		{
			// Shift about the center column (RIGHT -> LEFT and vice versa)
			pos = this->getCastedPositionC(pos);	
		}
	}
	
	return this->faces[face].SetStickerColor(color, pos);
}

// Casted, Rotate about center Row
rposition_t RCube::getCastedPositionR(rposition_t pos)
{
	switch(pos)
	{
		case TLEFT:
		case TOP:
		case TRIGHT:
			pos = (rposition_t)((int)pos + 6);
			break;
		case DLEFT:
		case DOWN:
		case DRIGHT:
			pos = (rposition_t)((int)pos - 6);
			break;
		default:
			// do nothing to position
			break;
	}
	return pos;
}

// Casted, Rotate about center Column
rposition_t RCube::getCastedPositionC(rposition_t pos)
{
	switch(pos)
	{
		case TLEFT:
		case LEFT:
		case DLEFT:
			pos = (rposition_t)((int)pos + 2);
			break;
		case TRIGHT:
		case RIGHT:
		case DRIGHT:
			pos = (rposition_t)((int)pos - 2);
			break;
		default:
			// do nothing to position
			break;
	}
	return pos;
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

std::string RCube::SolveYellowGreen() 
{
	REdge current = this->GetEdge(YELLOW, 2, 1);
	if(current.GetColor(YELLOW) == YELLOW && current.GetColor(GREEN) == GREEN) {return "";}
	if(current.GetColor(YELLOW) == GREEN && current.GetColor(GREEN) == YELLOW) {F() L() D() return "F L D ";}
	
	current = this->GetEdge(YELLOW, 1, 0);
	if(current.GetColor(YELLOW) == YELLOW && current.GetColor(ORANGE) == GREEN) {D() return "D ";}
	if(current.GetColor(YELLOW) == GREEN && current.GetColor(ORANGE) == YELLOW) {LA() FA() return "L' F'";}
	
	current = this->GetEdge(YELLOW, 0, 1);
	if(current.GetColor(YELLOW) == YELLOW && current.GetColor(BLUE) == GREEN) {D2() return "D2 ";}
	if(current.GetColor(YELLOW) == GREEN && current.GetColor(BLUE) == YELLOW) {B() R() DA() return"B R D' ";}
	
	current = this->GetEdge(YELLOW, 1, 2);
	if(current.GetColor(YELLOW) == YELLOW && current.GetColor(RED) == GREEN) {DA() return "D' ";}
	if(current.GetColor(YELLOW) == GREEN && current.GetColor(RED) == YELLOW) {R() F() return "R F ";}
	
	current = this->GetEdge(WHITE, 2, 1);
	if(current.GetColor(WHITE) == YELLOW && current.GetColor(GREEN) == GREEN) {F2() return "F2 ";}
	if(current.GetColor(WHITE) == GREEN && current.GetColor(GREEN) == YELLOW) {F() RA() DA() return "F R' D' ";}
	
	current = this->GetEdge(WHITE, 1, 0);
	if(current.GetColor(WHITE) == YELLOW && current.GetColor(ORANGE) == GREEN) {UA() F2() return "U' F2 ";}
	if(current.GetColor(WHITE) == GREEN && current.GetColor(ORANGE) == YELLOW) {L() FA() return "L F' ";}
	
	current = this->GetEdge(WHITE, 0, 1);
	if(current.GetColor(WHITE) == YELLOW && current.GetColor(BLUE) == GREEN) {U2() F2() return "U2 F2 ";}
	if(current.GetColor(WHITE) == GREEN && current.GetColor(BLUE) == YELLOW) {U() RA() F() return "U R' F ";}
	
	current = this->GetEdge(WHITE, 1, 2);
	if(current.GetColor(WHITE) == YELLOW && current.GetColor(RED) == GREEN) {U() F2() return "U F2 ";}
	if(current.GetColor(WHITE) == GREEN && current.GetColor(RED) == YELLOW) {RA() F() return "R' F ";}
	
	current = this->GetEdge(GREEN, 1, 0);
	if(current.GetColor(GREEN) == GREEN && current.GetColor(ORANGE) == YELLOW) {FA() return "F' ";}
	if(current.GetColor(GREEN) == YELLOW && current.GetColor(ORANGE) == GREEN) {L() D() return "L D ";}
	
	current = this->GetEdge(GREEN, 1, 2);
	if(current.GetColor(GREEN) == GREEN && current.GetColor(RED) == YELLOW) {F() return "F ";}
	if(current.GetColor(GREEN) == YELLOW && current.GetColor(RED) == GREEN) {RA() DA() return "R' D' ";}
	
	current = this->GetEdge(BLUE, 1, 2);
	if(current.GetColor(BLUE) == GREEN && current.GetColor(RED) == YELLOW) {BA() D2() return "B' D2 ";}
	if(current.GetColor(BLUE) == YELLOW && current.GetColor(RED) == GREEN) {R() DA() return "R D' ";}
	
	current = this->GetEdge(BLUE, 1, 0);
	if(current.GetColor(BLUE) == GREEN && current.GetColor(ORANGE) == YELLOW) {B() D2() return "B D2 ";}
	if(current.GetColor(BLUE) == YELLOW && current.GetColor(ORANGE) == GREEN) {LA() D() return "L' D ";}
    return "Invalid cube";
}

std::string RCube::SolveYellowOrange() 
{
	REdge current = this->GetEdge(YELLOW, 1, 0);
	if(current.GetColor(YELLOW) == YELLOW && current.GetColor(ORANGE) == ORANGE) {return "";}
	if(current.GetColor(YELLOW) == ORANGE && current.GetColor(ORANGE) == YELLOW) {L() DA() B() D() return "L D' B D ";}
	
	current = this->GetEdge(YELLOW, 0, 1);
	if(current.GetColor(YELLOW) == YELLOW && current.GetColor(BLUE) == ORANGE) {F() D() FA() return "F D F' ";}
	if(current.GetColor(YELLOW) == ORANGE && current.GetColor(BLUE) == YELLOW) {BA() LA() return "B' L' ";}
	
	current = this->GetEdge(YELLOW, 1, 2);
	if(current.GetColor(YELLOW) == YELLOW && current.GetColor(RED) == ORANGE) {F() D2() FA() return "F D2 F' ";}
	if(current.GetColor(YELLOW) == ORANGE && current.GetColor(RED) == YELLOW) {RA() F() DA() FA() return "F' F D' F' ";}
	
	current = this->GetEdge(WHITE, 1, 0);
	if(current.GetColor(WHITE) == YELLOW && current.GetColor(ORANGE) == ORANGE) {L2() return "L2 ";}
	if(current.GetColor(WHITE) == ORANGE && current.GetColor(ORANGE) == YELLOW) {UA() FA() L() F() return "U' F' L F ";}
	
	current = this->GetEdge(WHITE, 0, 1);
	if(current.GetColor(WHITE) == YELLOW && current.GetColor(BLUE) == ORANGE) {UA() L2() return "U' L2 ";}
	if(current.GetColor(WHITE) == ORANGE && current.GetColor(BLUE) == YELLOW) {B() LA() return "B L' ";}
	
	current = this->GetEdge(WHITE, 1, 2);
	if(current.GetColor(WHITE) == YELLOW && current.GetColor(RED) == ORANGE) {U2() L2() return "U2 L2 ";}
	if(current.GetColor(WHITE) == ORANGE && current.GetColor(RED) == YELLOW) {UA() B() LA() return " U' B L' ";}
	
	current = this->GetEdge(WHITE, 2, 1);
	if(current.GetColor(WHITE) == YELLOW && current.GetColor(GREEN) == ORANGE) {U() L2() return "U L2 ";}
	if(current.GetColor(WHITE) == ORANGE && current.GetColor(GREEN) == YELLOW) {FA() L() F() return "F' L F ";}
	
	current = this->GetEdge(GREEN, 1, 0);
	if(current.GetColor(GREEN) == YELLOW && current.GetColor(ORANGE) == ORANGE) {L() return "L ";}
	if(current.GetColor(GREEN) == ORANGE && current.GetColor(ORANGE) == YELLOW) {FA() DA() F() return "F' D' F ";}
	
	current = this->GetEdge(GREEN, 1, 2);
	if(current.GetColor(GREEN) == YELLOW && current.GetColor(RED) == ORANGE) {F2() L() F2() return "F2 L F ";}
	if(current.GetColor(GREEN) == ORANGE && current.GetColor(RED) == YELLOW) {F() DA() FA() return "F D' F' ";}
	
	current = this->GetEdge(BLUE, 1, 2);
	if(current.GetColor(BLUE) == YELLOW && current.GetColor(RED) == ORANGE) {B2() LA() return "B2 L' ";}
	if(current.GetColor(BLUE) == ORANGE && current.GetColor(RED) == YELLOW) {DA() BA() D() return "D' B' D ";}
	
	current = this->GetEdge(BLUE, 1, 0);
	if(current.GetColor(BLUE) == YELLOW && current.GetColor(ORANGE) == ORANGE) {LA() return "L' ";}
	if(current.GetColor(BLUE) == ORANGE && current.GetColor(ORANGE) == YELLOW) {DA() B() D() return "D' B D ";}
    return "Invalid cube";
}

std::string RCube::SolveYellowBlue()
{
	REdge current = this->GetEdge(YELLOW, 0, 1);
	if(current.GetColor(YELLOW) == YELLOW && current.GetColor(BLUE) == BLUE) {return "";}
	if(current.GetColor(YELLOW) == BLUE && current.GetColor(BLUE) == YELLOW) {B() DA() R() D() return "B D' R D ";}
	
	current = this->GetEdge(YELLOW, 1, 2);
	if(current.GetColor(YELLOW) == YELLOW && current.GetColor(RED) == BLUE) {RA() DA() R() D() return "R' D' R D ";}
	if(current.GetColor(YELLOW) == BLUE && current.GetColor(RED) == YELLOW) {RA() BA() return "R' B' ";}
	
	current = this->GetEdge(WHITE, 0, 1);
	if(current.GetColor(WHITE) == YELLOW && current.GetColor(BLUE) == BLUE) {B2() return "B2 ";}
	if(current.GetColor(WHITE) == BLUE && current.GetColor(BLUE) == YELLOW) {U() R() BA() return "U R B' ";}
	
	current = this->GetEdge(WHITE, 1, 2);
	if(current.GetColor(WHITE) == YELLOW && current.GetColor(RED) == BLUE) {UA() B2() return "U' B2 ";}
	if(current.GetColor(WHITE) == BLUE && current.GetColor(RED) == YELLOW) {R() BA() return "R B' ";}
	
	current = this->GetEdge(WHITE, 2, 1);
	if(current.GetColor(WHITE) == YELLOW && current.GetColor(GREEN) == BLUE) {U2() B2() return "U2 B2 ";}
	if(current.GetColor(WHITE) == BLUE && current.GetColor(GREEN) == YELLOW) {UA() R() BA() return "U' R B' ";}
	
	current = this->GetEdge(WHITE, 1, 0);
	if(current.GetColor(WHITE) == YELLOW && current.GetColor(ORANGE) == BLUE) {U() B2() return "U B2 ";}
	if(current.GetColor(WHITE) == BLUE && current.GetColor(ORANGE) == YELLOW) {LA() B() L() return "L' B L ";}
    
    current = this->GetEdge(GREEN, 1, 0);
    if(current.GetColor(GREEN) == YELLOW && current.GetColor(ORANGE) == BLUE) {D() L() DA() return "D L D' ";}
    if(current.GetColor(GREEN) == BLUE && current.GetColor(ORANGE) == YELLOW) {D2() FA() D2() return "D2 F' D2 ";}
    
    current = this->GetEdge(GREEN, 1, 2);
    if(current.GetColor(GREEN) == YELLOW && current.GetColor(RED) == BLUE) {DA() RA() D() return "D' R' D ";}
    if(current.GetColor(GREEN) == BLUE && current.GetColor(RED) == YELLOW) {D2() F() D2() return "D2 F D2 ";}
    
    current = this->GetEdge(BLUE, 1, 2);
    if(current.GetColor(BLUE) == YELLOW && current.GetColor(RED) == BLUE) {RA() UA() B2() return "R' U' B2 ";}
    if(current.GetColor(BLUE) == BLUE && current.GetColor(RED) == YELLOW) {BA() return "B' ";}
    std::cout << "checking" << std::endl;
    current = this->GetEdge(BLUE, 1, 0);
    if(current.GetColor(BLUE) == YELLOW && current.GetColor(ORANGE) == BLUE) {L() U() LA() B2() return "L U L' B2 ";}
    if(current.GetColor(BLUE) == BLUE && current.GetColor(ORANGE) == YELLOW) {B() return "B ";}
    return "Invalid cube";
}

std::string RCube::SolveYellowRed()
{
    REdge current = this->GetEdge(YELLOW, 1, 2);
    if(current.GetColor(YELLOW) == YELLOW && current.GetColor(RED) == RED) {return "";}
    if(current.GetColor(YELLOW) == RED && current.GetColor(RED) == YELLOW) {R() DA() F() D() return "R D' F D ";}
    
    current = this->GetEdge(WHITE, 1, 2);
    if(current.GetColor(WHITE) == YELLOW && current.GetColor(RED) == RED) {R2() return "R2 ";}
    if(current.GetColor(WHITE) == RED && current.GetColor(RED) == YELLOW) {U() F() RA() FA() return "U F R' F' ";}
    
    current = this->GetEdge(WHITE, 2, 1);
    if(current.GetColor(WHITE) == YELLOW && current.GetColor(GREEN) == RED) {UA() R2() return "U' R2 ";}
    if(current.GetColor(WHITE) == RED && current.GetColor(GREEN) == YELLOW) {F() RA() FA() return "F R' F' ";}
    
    current = this->GetEdge(WHITE, 1, 0);
    if(current.GetColor(WHITE) == YELLOW && current.GetColor(ORANGE) == RED) {U2() R2() return "U2 R2 ";}
    if(current.GetColor(WHITE) == RED && current.GetColor(ORANGE) == YELLOW) {UA() F() RA() FA() return "U' F R' F' ";}
    
    current = this->GetEdge(WHITE, 0, 1);
    if(current.GetColor(WHITE) == YELLOW && current.GetColor(BLUE) == RED) {U() R2() return "U R2 ";}
    if(current.GetColor(WHITE) == RED && current.GetColor(BLUE) == YELLOW) {BA() R() B() return "B' R B";}
    
    current = this->GetEdge(GREEN, 1, 2);
    if(current.GetColor(GREEN) == YELLOW && current.GetColor(RED) == RED) {RA() return "R' ";}
    if(current.GetColor(GREEN) == RED && current.GetColor(RED) == YELLOW) {DA() F() D() return "D' F D ";}
    
    current = this->GetEdge(GREEN, 1, 0);
    if(current.GetColor(GREEN) == YELLOW && current.GetColor(ORANGE) == RED) {DA() F2() D() R() return "D' F2 D R ";}
    if(current.GetColor(GREEN) == RED && current.GetColor(ORANGE) == YELLOW) {DA() FA() D() return "D' F' D ";}
    
    current = this->GetEdge(BLUE, 1, 2);
    if(current.GetColor(BLUE) == YELLOW && current.GetColor(RED) == RED) {R() return "R ";}
    if(current.GetColor(BLUE) == RED && current.GetColor(RED) == YELLOW) {D() BA() DA() return "D B' D' ";}
    
    current = this->GetEdge(BLUE, 1, 0);
    if(current.GetColor(BLUE) == YELLOW && current.GetColor(ORANGE) == RED) {D() B2() DA() R() return "D B2 D' R ";}
    if(current.GetColor(BLUE) == RED && current.GetColor(ORANGE) == YELLOW) {BA() U() B() R2() return "B' U B R2 ";}
    return "Invalid cube";
}

#ifdef OPENCV

void RCube::ResetFace(rcolor_t face)
{
	this->faces[face].SetAllColors(BLACK);
}

cv::Scalar cvtRColor2RGB(RubiksColor_Enum rc)
{
	// Returns a BGR Scalar
	switch (rc)
	{
		case WHITE:
			return cv::Scalar(255,255,255);
		case YELLOW:
			return cv::Scalar(0, 255,255);
		case GREEN:
			return cv::Scalar(0,255,0);
		case BLUE:
			return cv::Scalar(255,0,0);
		case RED:
			return cv::Scalar(0,0,255);
		case ORANGE:
			return cv::Scalar(0,128,255);
		case BLACK:
			return cv::Scalar(0,0,0);
		default:
			std::cout << "Error: Unsupported color" << std::endl;
			return cv::Scalar(0, 0, 0, 0);
	}
}

cv::Mat& operator<<(cv::Mat& mat, RCube& rcube)
{
	cv::Point pos(STICKER_SIZE*4, STICKER_SIZE*1);
	int padding = 2;
	cv::Scalar borderColor(128,128,128);
	cv::Mat stickerMat(STICKER_SIZE - padding*2, STICKER_SIZE - padding*2, CV_8UC3);
	cv::Mat coloredMat(STICKER_SIZE, STICKER_SIZE, CV_8UC3);
	std::vector<std::vector<rcolor_t> > faceColors;
	
	
	faceColors = rcube.faces[WHITE].GetColors();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Create a region of interest
			cv::Rect roi(pos, coloredMat.size());
			stickerMat.setTo(cvtRColor2RGB(faceColors[i][j]));
			copyMakeBorder(stickerMat, coloredMat, padding, padding, padding, padding, 
						   cv::BORDER_CONSTANT, borderColor);
			coloredMat.copyTo(mat(roi));
			pos.x += STICKER_SIZE;
		}
		pos.y += STICKER_SIZE;
		pos.x -= STICKER_SIZE*3;
	}

	faceColors = rcube.faces[ORANGE].GetColors();
	pos.x = STICKER_SIZE*1;
	pos.y = STICKER_SIZE*4;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Create a region of interest
			cv::Rect roi(pos, coloredMat.size());
			stickerMat.setTo(cvtRColor2RGB(faceColors[i][2 - j]));
			copyMakeBorder(stickerMat, coloredMat, padding, padding, padding, padding, 
						   cv::BORDER_CONSTANT, borderColor);
			coloredMat.copyTo(mat(roi));
			pos.x += STICKER_SIZE;
		}
		pos.y += STICKER_SIZE;
		pos.x -= STICKER_SIZE*3;
	}
	
	faceColors = rcube.faces[GREEN].GetColors();
	pos.x = STICKER_SIZE*(1 + 3);
	pos.y = STICKER_SIZE*4;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Create a region of interest
			cv::Rect roi(pos, coloredMat.size());
			stickerMat.setTo(cvtRColor2RGB(faceColors[i][j]));
			copyMakeBorder(stickerMat, coloredMat, padding, padding, padding, padding, 
						   cv::BORDER_CONSTANT, borderColor);
			coloredMat.copyTo(mat(roi));
			pos.x += STICKER_SIZE;
		}
		pos.y += STICKER_SIZE;
		pos.x -= STICKER_SIZE*3;
	}
	
	faceColors = rcube.faces[RED].GetColors();
	pos.x = STICKER_SIZE*(1 + 3 + 3);
	pos.y = STICKER_SIZE*4;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Create a region of interest
			cv::Rect roi(pos, coloredMat.size());
			stickerMat.setTo(cvtRColor2RGB(faceColors[i][j]));
			copyMakeBorder(stickerMat, coloredMat, padding, padding, padding, padding, 
						   cv::BORDER_CONSTANT, borderColor);
			coloredMat.copyTo(mat(roi));
			pos.x += STICKER_SIZE;
		}
		pos.y += STICKER_SIZE;
		pos.x -= STICKER_SIZE*3;
	}

	
	faceColors = rcube.faces[BLUE].GetColors();
	pos.x = STICKER_SIZE*(1 + 3 + 3 + 3);
	pos.y = STICKER_SIZE*4;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Create a region of interest
			cv::Rect roi(pos, coloredMat.size());
			stickerMat.setTo(cvtRColor2RGB(faceColors[i][2 - j]));
			copyMakeBorder(stickerMat, coloredMat, padding, padding, padding, padding, 
						   cv::BORDER_CONSTANT, borderColor);
			coloredMat.copyTo(mat(roi));
			pos.x += STICKER_SIZE;
		}
		pos.y += STICKER_SIZE;
		pos.x -= STICKER_SIZE*3;
	}
	
	faceColors = rcube.faces[YELLOW].GetColors();
	pos.x = STICKER_SIZE*(1 + 3);
	pos.y = STICKER_SIZE*(1 + 3 + 3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Create a region of interest
			cv::Rect roi(pos, coloredMat.size());
			stickerMat.setTo(cvtRColor2RGB(faceColors[2 - i][j]));
			copyMakeBorder(stickerMat, coloredMat, padding, padding, padding, padding, 
						   cv::BORDER_CONSTANT, borderColor);
			coloredMat.copyTo(mat(roi));
			pos.x += STICKER_SIZE;
		}
		pos.y += STICKER_SIZE;
		pos.x -= STICKER_SIZE*3;
	}
	
	pos.x = STICKER_SIZE*(1);
	pos.y = STICKER_SIZE*(1 + 3 + 3 + 3);
	for (int j = 0; j < 14; j++)
	{
		// Create a region of interest
		cv::Rect roi(pos, coloredMat.size());
		coloredMat.setTo(cv::Scalar(255,255,255));

		coloredMat.copyTo(mat(roi));
		pos.x += STICKER_SIZE;
	}
	pos.x = STICKER_SIZE*(1);
	pos.y = STICKER_SIZE*(1 + 3 + 3 + 3 + 1);
	for (int j = 0; j < 14; j++)
	{
		// Create a region of interest
		cv::Rect roi(pos, coloredMat.size());
		coloredMat.setTo(cv::Scalar(255,255,255));

		coloredMat.copyTo(mat(roi));
		pos.x += STICKER_SIZE;
	}

	return mat;
}
#endif