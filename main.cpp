// Rubik's Cube Solver
#include <iostream>

#include <stdio.h>

#include "rcube.hpp"

int main(void)
{
	RCube rubiks = RCube();

	rubiks.InitSolved();
  
  	rubiks.BeginInteractive();

	std::cout << rubiks;
}