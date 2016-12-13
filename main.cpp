// Rubik's Cube Solver
#include <iostream>

#include <stdio.h>

#include "rcube.hpp"

int main(void)
{
	RCube rubiks = RCube();
	
	#ifndef OPENCV
	rubiks.InitSolved();
	#endif
  	rubiks.BeginInteractive();
	
	std::cout << rubiks;
}