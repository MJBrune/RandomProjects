//-----------------------------------------------------------------------------
//	File:       CPlayer.h
//
//	class:		CPlayer
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//	Title:          Player Class
//
//	Description:    This file contains the class definition for CPlayer
//
//	Programmer:    :(){:|:&};:
//   
//	Date:           3/12/2012
// 
//	Version:	1.0
//   
//	Environment:    Intel Xeon PC 
//			Software:   MS Windows 7 for execution; 
//			Compiles under Microsoft Visual C++.Net 2010
//
//	class CPlayer:
//
//	Properties:
//				unsigned short m_whichPlayer; - number of which player the current object is for.
//				short m_piecesLeft; - total pieces left (unsunk) for the current player
//				JP_CSHIPINFO::CShipInfo m_ships[6]; - array of ships for the player.
//				char m_gridSize; - the current grid size
//				MB_CSHIP::CShip** m_gameGrid[2]; - the array of the entine game grid for the player.
//
//	Methods:
//	
//		inline:	
//		CPlayer(unsigned short whichPlayer = 0, char gridSize = 'S');
//		Constructor - sets the m_whichPlayer and m_gridSize.
//
//		void CShip::printName(std::ostream &sout) const
//			prints out shipname to ostream.
//
//		void CCell::print()
//			prints out ship to cout.
//
//		operator Ship() const
//			cast to Ship enum, returns m_ship.
//
//		non-inline:
//					void CShip::print(std::ostream &sout) const;
//						prints out ship to an ostream.
//
//    History Log:
//      3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
#ifndef CPLAYER_H
#define CPLAYER_H
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include "CShipInfo.h"
#include "CShip.h"
#include "CCell.h"
#include "textGraphics.h"
#include "safeio.h"
#include "CDirection.h"

class CPlayer
{
public:
	CPlayer(unsigned short whichPlayer = 0, char gridSize = 'S');
	CPlayer(const CPlayer & player);
	~CPlayer();
	CPlayer operator=(const CPlayer & player)
		{return CPlayer(player);}
	unsigned short getWhichPlayer()
		{return m_whichPlayer;}
	short getPiecesLeft()
		{return m_piecesLeft;}
	char getGridSize()
		{return m_gridSize;}

	MB_CSHIP::CShip getCell(short whichGrid, MB_CCELL::CCell cell)
		{return m_gameGrid[whichGrid][cell.getRow()][cell.getCol()];}
	void setCell(short whichGrid, MB_CCELL::CCell cell, MB_CSHIP::CShip ship)
		{m_gameGrid[whichGrid][cell.getRow()][cell.getCol()] = ship;}

	void setGridSize(char size)
		{m_gridSize = size;}
	void printGrid(std::ostream& sout, short whichGrid);
	bool getGrid (std::string filename);
	void saveGrid();
	void setShips(short whichPlayer);
	void randGrid();
	void hitShip(MB_CSHIP::CShip ship)
		{m_ships[ship]--; m_piecesLeft--;}
	bool isValidLocation(short whichShip);
	JP_CSHIPINFO::CShipInfo operator[](short index) const;
	CPlayer operator--()
		{m_piecesLeft--; return *this;}
private:
	unsigned short m_whichPlayer;
	short m_piecesLeft;
	JP_CSHIPINFO::CShipInfo m_ships[6];
	char m_gridSize;
	MB_CSHIP::CShip** m_gameGrid[2];
	void allocateMemory();
	void deleteMemory();
};
#endif