#include "CPlayer.h"

using namespace JP_CSHIPINFO;

CPlayer::CPlayer(unsigned short whichPlayer, char gridSize)
	:m_whichPlayer(whichPlayer),
	m_gridSize(gridSize)
{

	for (short i = 0; i < 2; i++)
		m_gameGrid[i] = NULL;
	allocateMemory();

	for (short j = 0; j < 6; j++)//SHIP_SIZE_ARRAYSIZE
	{
		m_ships[j].setName((MB_CSHIP::Ship)j);

		m_ships[j].setPiecesLeft(MB_CSHIP::shipSize[j + 1]);
	}
	m_piecesLeft = 17; //TOTALPIECES
}

CPlayer::~CPlayer()
{
	deleteMemory();
}

CPlayer::CPlayer(const CPlayer & player)
	: m_whichPlayer(player.m_whichPlayer),
	m_gridSize(player.m_gridSize)
{
	for (short i = 0; i < 2; i++)
		m_gameGrid[i] = NULL;
	allocateMemory();
	
	for (short j = 0; j < 6; j++)//6 = SHIP_SIZE_ARRAYSIZE
	{
		m_ships[j] = player.m_ships[j];
	}
	m_piecesLeft = player.m_piecesLeft;
}

void CPlayer::allocateMemory()
		{
			short numberOfRows = LARGEROWS;
			short numberOfCols = LARGECOLS;
	
			try
			{
				m_gameGrid[0] = new MB_CSHIP::CShip*[numberOfRows];
				m_gameGrid[1] = new MB_CSHIP::CShip*[numberOfRows];
				for(short j = 0; j < numberOfRows; ++j)
				{
					m_gameGrid[0][j] = new MB_CSHIP::CShip[numberOfCols];
					m_gameGrid[1][j] = new MB_CSHIP::CShip[numberOfCols];
	
					for(short k = 0; k < numberOfCols; ++k)
					{
						m_gameGrid[0][j][k] = MB_CSHIP::CShip(MB_CSHIP::NOSHIP);
						m_gameGrid[1][j][k] = MB_CSHIP::CShip(MB_CSHIP::NOSHIP);
					} // end for k
				} // end for j
			} 

			catch(exception e)
			{
				deleteMemory();
				cerr << "exception: " << e.what() << endl;
				cout << "shutting down" << endl;
				cin.ignore(BUFFER_SIZE, '\n');
				exit(EXIT_FAILURE);
			}
	} 

void CPlayer::deleteMemory()
{
	short numberOfRows = LARGEROWS;

		for (short j = 0; j < numberOfRows; j++)
		{
			if (this[m_whichPlayer].m_gameGrid[0][j] != NULL)
				delete[] this[m_whichPlayer].m_gameGrid[0][j];
		}

		if (this[m_whichPlayer].m_gameGrid[0] != NULL)
			delete[] this[m_whichPlayer].m_gameGrid[0];
}

bool CPlayer::isValidLocation(short whichShip)
{
	short numberOfRows = (toupper(m_gridSize)=='L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(m_gridSize)=='L') ? LARGECOLS : SMALLCOLS;

	if(m_ships[whichShip].getOrientaion() == MB_CDIRECTION::HORIZONTAL && 
	   m_ships[whichShip].getBowLocation().getCol() + MB_CSHIP::shipSize[whichShip]  
	   <= numberOfCols)
	{
		for(short i = 0; i < MB_CSHIP::shipSize[whichShip]; i++)
			if(m_gameGrid[0][m_ships[whichShip].getBowLocation().getRow()]
			[m_ships[whichShip].getBowLocation().getCol() + i] != MB_CSHIP::NOSHIP)
			{
				return false;
			}
	}
	else if(m_ships[whichShip].getOrientaion() == MB_CDIRECTION::VERTICAL && 
	   m_ships[whichShip].getBowLocation().getRow() + MB_CSHIP::shipSize[whichShip]  
	   <= numberOfRows)
	{
		for(short i = 0; i < MB_CSHIP::shipSize[whichShip]; i++)
			if(m_gameGrid[0]
			[m_ships[whichShip].getBowLocation().getRow() + i]
			[m_ships[whichShip].getBowLocation().getCol()] 
			!= MB_CSHIP::NOSHIP)
			{
				return false;
			}
	}
	else
	{
		return false;
	}
	
	return true;
}

void CPlayer::printGrid(std::ostream& sout, short whichGrid)
{
	short numberOfRows = (toupper(m_gridSize)=='L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(m_gridSize)=='L') ? LARGECOLS : SMALLCOLS;

	sout << ' ';

	for (short j = 1; j <= numberOfCols; ++j)
		sout << setw(3) << j;
	sout << endl;

	sout << HORIZ << CROSS << HORIZ << HORIZ << CROSS;

	for (short l = 0; l < numberOfCols - 1; l++)
		sout << HORIZ << HORIZ << CROSS;

	sout << endl;

	for (short i = 0; i < numberOfRows; i++)
	{
		sout << static_cast<char>(i + 65) << VERT;

		for (short h = 0; h < numberOfCols; h++)
		{
			m_gameGrid[whichGrid][i][h].print(sout);
		}
		sout << endl;
		sout << HORIZ << CROSS << HORIZ << HORIZ;
		for (short j = 0; j < numberOfCols - 1; j++)
			sout << CROSS << HORIZ << HORIZ;
		sout << CROSS;
		sout << endl;
	}
}

bool CPlayer::getGrid(std::string filename)
{
	char ship;
	std::ifstream ifs;
	short shipCount[MB_CSHIP::SHIP_SIZE_ARRAYSIZE] = {0};
	char cell = ' ';
	char fsize = 'S';
	char line[256];
	char choice = 'N';

	short numberOfRows = (toupper(m_gridSize)=='L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(m_gridSize)=='L') ? LARGECOLS : SMALLCOLS;

	int totalCells = numberOfRows * numberOfCols;

	ifs.open(filename);
	if (!ifs)
	{
		cout << "could not open file " << filename << endl
			<< "press <enter> to continue" << endl;
		cin.ignore(256, '\n');//256 = BUFFER_SIZE
		return false;
	}
	fsize = ifs.get();
	if (fsize != m_gridSize)
	{
		cout << "saved grid is not the correct size " << filename << endl
			<< " press <enter> to continue" << endl;
		cin.get();
		return false;
	}

	ifs.ignore(256, '\n');//magic number
	ifs.getline(line, 256);//magic number

	for (int rows = 0; rows != numberOfRows; rows++)
	{
		ifs.getline(line, 256);

		for (int cols = 0; cols != numberOfCols; cols++)
		{
			ship = ifs.get();

			while (ship != ' ')
				ship = ifs.get();

			ship = ifs.get();

			switch (ship)
			{
			case 'M':
				this[m_whichPlayer].m_gameGrid[0][rows][cols] = MB_CSHIP::MINESWEEPER;
				break;
			case 'S':
				this[m_whichPlayer].m_gameGrid[0][rows][cols] = MB_CSHIP::SUB;
				break;
			case 'F':
				this[m_whichPlayer].m_gameGrid[0][rows][cols] = MB_CSHIP::FRIGATE;
				break;
			case 'B':
				this[m_whichPlayer].m_gameGrid[0][rows][cols] = MB_CSHIP::BATTLESHIP;
				break;
			case 'C':
				this[m_whichPlayer].m_gameGrid[0][rows][cols] = MB_CSHIP::CARRIER;
				break;
			case ' ':
				this[m_whichPlayer].m_gameGrid[0][rows][cols] = MB_CSHIP::NOSHIP;
				break;
			default:
				cout << "The file has become corrupt. Sorry" << endl
					<< " press <enter> to continue" << endl;
				return false;
			}
		}
	}

	system("cls");
	printGrid(cout, m_whichPlayer);
	cin.ignore(256, '\n');//BUFFER_SIZE
	choice = safeChoice("is this the grid you wanted?", 'Y', 'N');
	if (choice == 'Y')
		return true;
	else
	{
		system("cls");
		return false;
	}
}

void CPlayer::saveGrid()
{
	short numberOfRows = (toupper(m_gridSize)=='L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(m_gridSize)=='L') ? LARGECOLS : SMALLCOLS;

	std::ofstream file;
	std::string filename;

	std::cout << "NOTE: .shp will be appended to the filename" << std::endl;
	std::cout << "What should this grid be saved as? ";
	std::cin >> filename;
	file.open(filename + ".shp");
	if (file)
	{
		file << m_gridSize << endl;
		printGrid(file, m_whichPlayer);
		file.close();
		std::cout << "Grid has been saved as " << filename + ".shp" << std::endl;
		std::cin.get();
	}
	else
	{
		std::cout << "could not open file " << filename + ".shp" << std::endl;
		std::cout << "Press <enter> to continue" << endl;
		std::cin.ignore(256, '\n');//BUFFER_SIZE
	}
	std::cin.ignore(256, '\n');//BUFFER_SIZE
}

void CPlayer::setShips(short whichplayer)
{
	char input = 'V';
	char save = 'N';
	MB_CCELL::CCell location(0,0);
	MB_CSHIP::Ship name = MB_CSHIP::NOSHIP;
	m_whichPlayer = whichplayer;
	for(short j = 1; j < MB_CSHIP::SHIP_SIZE_ARRAYSIZE; j++)
	{
		system("cls");
		printGrid(cout, 0);
		//outSStream.str("");
		cout << "Player " << m_whichPlayer + 1 << " Enter ";
		m_ships[j].getName().printName(cout);
		cout << " orientation";

		input =  safeChoice("", 'V', 'H');
		m_ships[j].setOrientaion((input == 'V') ? MB_CDIRECTION::VERTICAL : MB_CDIRECTION::HORIZONTAL);
	
		cout << "Player " << m_whichPlayer + 1 << " Enter " << m_ships[j].getName() <<
			    " bow coordinates <row letter><col #>\n";
		
		location.inputCoordinates(cin, m_gridSize);
		m_ships[j].setBowLocation(location); 

		// if ok
		if(!isValidLocation(j))
		{
			cout << "invalid location. Press <enter>" ;
			cin.get();
			j--; // try again
			continue;
		}
		
		if(m_ships[j].getOrientaion() == MB_CDIRECTION::VERTICAL)
		{
			for(int i = 0; i < MB_CSHIP::shipSize[j]; i++)
			{
				m_gameGrid[0][location.getRow() + i][location.getCol()] = (MB_CSHIP::Ship)j;
			}
		}

		else
		{
			for(int i = 0; i < MB_CSHIP::shipSize[j]; i++)
			{
				m_gameGrid[0][location.getRow()][location.getCol() + i] = (MB_CSHIP::Ship)j;
			}	
		}
		
		system("cls");
		printGrid(cout, 0);
	} // end for j

	save = safeChoice("\nSave starting grid?", 'Y', 'N');
	if(save == 'Y')
		saveGrid();
	system("cls");
}

void CPlayer::randGrid()

{
		char input = 'V';
	char save = 'N';
	MB_CCELL::CCell location(0,0);
	MB_CSHIP::Ship name = MB_CSHIP::NOSHIP;

	for(short j = 1; j < MB_CSHIP::SHIP_SIZE_ARRAYSIZE; j++)
	{
		system("cls");
		printGrid(cout, 0);
		cout << "Player " << m_whichPlayer + 1 << " Enter ";
		m_ships[j].getName().printName(cout);
		cout << " orientation";

		m_ships[j].setOrientaion((rand() % 2 == 0) ? MB_CDIRECTION::VERTICAL : MB_CDIRECTION::HORIZONTAL);
		cout << "Player " << m_whichPlayer + 1 << " Enter " << m_ships[j].getName() <<
			    " bow coordinates <row letter><col #>\n";
		
		location.randomCell(m_gridSize);
		m_ships[j].setBowLocation(location); 

		// if ok
		if(!isValidLocation(j))
		{
			j--; // try again
			continue;
		}
		
		if(m_ships[j].getOrientaion() == MB_CDIRECTION::VERTICAL)
		{
			for(int i = 0; i < MB_CSHIP::shipSize[j]; i++)
			{
				m_gameGrid[0][location.getRow() + i][location.getCol()] = (MB_CSHIP::Ship)j;
			}
		}

		else
		{
			for(int i = 0; i < MB_CSHIP::shipSize[j]; i++)
			{
				m_gameGrid[0][location.getRow()][location.getCol() + i] = (MB_CSHIP::Ship)j;
			}	
		}
		
		system("cls");
		printGrid(cout, 0);
	} // end for j

	save = safeChoice("\nSave starting grid?", 'Y', 'N');
	if(save == 'Y')
		saveGrid();
	system("cls");
}

CShipInfo CPlayer::operator[](short index) const
{
	if (index >= 6)//SHIP_SIZE_ARRAYSIZE
		throw range_error("index out of range");
	return m_ships[index];
}