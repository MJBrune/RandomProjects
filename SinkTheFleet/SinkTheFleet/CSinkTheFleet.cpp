//----------------------------------------------------------------------------
// File:	fleet.cpp
// 
// Functions: 
//	  setShipInfo()	
//	  allocMem() 
//	  deleteMem()
//	  printShip() 
//	  printGrid() 
//	  initializePlayer() 
//	  setships()	      
//	  saveGrid()
//	  getGrid()
//	  getCoord()
//	  validLocation() 
//	  header() 
//	  endBox() 
//----------------------------------------------------------------------------
#include "CSinkTheFleet.h"
using namespace MB_CSHIP;
using namespace MB_CCELL;
//----------------------------------------------------------------------------
// File:	fleet.cpp
// 
// Functions: 
//	  setShipInfo()	
//	  allocMem() 
//	  deleteMem()
//	  printShip() 
//	  printGrid() 
//	  initializePlayer() 
//	  setships()	      
//	  saveGrid()
//	  getGrid()
//	  getCoord()
//	  validLocation() 
//	  header() 
//	  endBox() 
//----------------------------------------------------------------------------
 int CSinkTheFleet::play()
 {
	char again = 'Y';
	bool gameOver = false;			
	bool reshot = false;
	short numRows = SMALLROWS;		// total number of rows in the array
	short numCols = SMALLCOLS;		// total number of columns in the array
	string filename;
	char readfile = 'Y';
	short whichPlayer = 0;			
	CShip shipHit = NOSHIP;
	char randGrid = 'Y';

	system("cls");
	cout << endl;
	header(cout);
	gameOver = false;
	m_gridSize = safeChoice("Which size grid to you want to use",'S','L');
	m_players[0].setGridSize(m_gridSize);
	m_players[1].setGridSize(m_gridSize);

	if( m_gridSize == 'L')
	{
		numRows = LARGEROWS;
		numCols = LARGECOLS;
	}
	else
	{
		numRows = SMALLROWS;
		numCols = SMALLCOLS;
	}
	
	for(whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
	{
		cout << "Player " <<  whichPlayer + 1 <<", would you like to read starting grid from a file?";
		readfile = safeChoice("", 'Y','N');
			
		if(readfile == 'Y')
		{
			string filename;
			cout << "Enter filename:";
			cin >> filename;
			cin.ignore(BUFFER_SIZE, '\n');
			filename += ".shp";

			if(!m_players[whichPlayer].getGrid(filename))
			{
				whichPlayer--;
				system("cls");
				continue;
			}
			system("cls");
				
		}
		else
		{
			cout << "Player " <<  whichPlayer + 1 <<", would you like to generate a random grid?";
			randGrid= safeChoice("", 'Y','N');
			if ( randGrid == 'Y')
			{
				system("cls");
				m_players[whichPlayer].randGrid();
			}
			else
			{
				system("cls");
				//m_players[whichPlayer].printGrid(cout, 0);
				m_players[whichPlayer].setShips(whichPlayer);
				system("cls");
			}
		}
	}

	cout<<" GET UR BUTT READY FOR BATTTLLLLE! " << endl;

	//war it's about TIME! :)
	CCell celShot;
	whichPlayer = 0;
	while(!gameOver)
	{
		reshot = false; 
		cout << "THe game is running yooo !"<< endl;
		// Gameplay!!!!
		m_players[whichPlayer].printGrid(cout, 1);
		cout << "Player " << whichPlayer + 1 << " Enter " << "  coordinates <row letter><col #> to hit" << endl;
			
		celShot.inputCoordinates(cin, m_gridSize);
		//cin.get();
		system("cls");

		shipHit = m_players[!whichPlayer].getCell(0, celShot);
		// Check if the player hit the other player's ships
		if ( m_players[whichPlayer].getCell(1, celShot) != NOSHIP)
		{
			cout << "You have already shot there" << endl;
			system("pause");
		}
		else if(shipHit != NOSHIP && shipHit != HIT)
		{
			m_players[whichPlayer].setCell(1,celShot,(CShip(HIT)));
			m_players[!whichPlayer].hitShip(MB_CSHIP::Ship((int)shipHit - 1));

			if(m_players[!whichPlayer][(int)shipHit - 1].getPiecesLeft() == 0) // Hit it
			{
				cout<< " You hit the bastard" << endl;
				cout << "NICE! You sunk enemy's ";
				shipHit.printName(cout);
				cout << endl;

				m_players[whichPlayer].printGrid(cout, 1);
				system("pause");
			}
			else // didnt sink
			{		
				cout<< " You hit the bastard" << endl;
				m_players[whichPlayer].printGrid(cout, 1);
				system("pause");
			}

		}
		else
		{
				
			m_players[whichPlayer].setCell(1,celShot,CShip(MISSED));
			system("cls");
			m_players[whichPlayer].printGrid(cout,1);
			cout << "you didn't hit anything!"<< endl;
			system("pause");
			whichPlayer = !whichPlayer; // switch players
		}

		system("cls");
		if(m_players[!whichPlayer].getPiecesLeft() == 0)
		{
			gameOver = true;
			break;
		}
		
	}

	return whichPlayer;
	
}

void CSinkTheFleet::header(ostream& sout)
{
		const string empty;
		const string sink("SINK THE FLEET!");
		const string names("ForkBomb Group");
		const string by("Edmonds Community College CS 132");
		boxTop(sout, BOXWIDTH);
		boxLine(sout, empty, BOXWIDTH);
		boxLine(sout, sink , BOXWIDTH, 'C');
		boxLine(sout, empty , BOXWIDTH);
		boxLine(sout, names , BOXWIDTH, 'C');
		boxLine(sout, empty, BOXWIDTH);
		boxLine(sout, by, BOXWIDTH, 'C');
		boxLine(sout, empty, BOXWIDTH);
		boxBottom(sout, BOXWIDTH);
	}

		void endBox(short player)
	{
		const string empty;
		ostringstream msg;
		msg << "Congratulations player " << player + 1 << "!";
		boxTop(cout, BOXWIDTH);
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, msg.str() , BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxBottom(cout, BOXWIDTH);
	}




