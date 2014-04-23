//---------------------------------------------------------------------------
//	File:           CSinkTheFleet.h
//
//	Title:          CSinkTheFleet  Class
//
//	Description:    This file contains the class definition for CSinkTheFleet
//
//	Programmer:     ForkBomb
//   
//	Date:           3/13/2011               
// 
//	Version:        1.0
//   
//  Environment:    Intel Xeon PC 
//                  Software:   MS Windows 7 for execution; 
//                  Compiles under Microsoft Visual C++.Net 2010
//
//	class CCELL:
//
//	Properties:
//		
//		
//
//	Methods:
//	
//		inline:	
//					
//		non-inline:
//					
//    History Log:	ForkBomb finished workable version on 14/3/2011
//---------------------------------------------------------------------------

#ifndef CSINKTHEFLEET_H
#define CSINKTHEFLEET_H

#pragma warning(disable:4244)
#pragma warning(disable:4520)


const unsigned MAX_BUFFER_SIZE = 256;
const short BOXWIDTH = 79;	// maximum screen line length
const short NUMPLAYERS = 2;

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <assert.h>
#include "CCell.h"
#include "CDirection.h"
#include "CShipInfo.h"
#include "CPlayer.h"
#include "safeio.h"
#include "textGraphics.h"

class CSinkTheFleet
{
public:

	CSinkTheFleet(char gridSize = 'S') : m_gridSize(gridSize) {}

	int play();

	void header(ostream& sout);

	CPlayer operator[](const int i) { return m_players[i]; };
	CPlayer operator[](const int i)const { return m_players[i]; };

private:
	CPlayer m_players[2];
	char m_gridSize;
};
#endif




