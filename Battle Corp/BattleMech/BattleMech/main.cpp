
#include <iostream>
#include <fstream>
#include "Globals.h"
#include "Network/Server.h"
#include "States/MechMenu.h"
#include "States/MainMenu.h"
#include "States/BattleMech.h"
#include "States/OptionMenu.h"
#define WIN

States::MechMenu	States::MainMenu::bMechMenu;
States::BattleMech	bMechGame;
States::MainMenu	bMainMenu;
//States::OptionMenu	States::MainMenu::bOptionMenu;
sf::Image			TileMap::hexImage;

int main()
{
	std::string Version = "1.0.1";
	std::ofstream exeUpdate;
	/*
	sf::Http::Request Request;
	sf::Http Http;
	Http.SetHost("www.mjbrune.org");
	Request.SetMethod(sf::Http::Request::Get);
#ifdef WIN
	Request.SetURI("/files/bc/version.txt");
#else
	Request.SetURI("/files/bc/linversion.txt");
#endif
	Request.SetHttpVersion(1, 1);
	sf::Http::Response Response = Http.SendRequest(Request);
	sf::Http::Response::Status Status = Response.GetStatus();
	unsigned int Major = Response.GetMajorHttpVersion();
	unsigned int Minor = Response.GetMinorHttpVersion();
	std::string Body = Response.GetBody();
	std::string Type = Response.GetField("Content-Type");
	std::cout << "Version: " << Body << " Status: " << Status << std::endl;
	if (Body != Version && Status == sf::Http::Response::Status::Ok )
	{
#ifdef WIN
		Request.SetURI("/files/bc/BattleCorp.exe");
		Response = Http.SendRequest(Request);
		exeUpdate.open ("BattleCorp.exe", std::ios::binary);
		exeUpdate << Response.GetBody();
		exeUpdate.close();
		std::cout << "Update Downloaded";

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		// Start the child process. 
		if( !CreateProcess( NULL,   // No module name (use command line)
			"BattleCorp.exe",        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi )           // Pointer to PROCESS_INFORMATION structure
			) 
		{
			printf( "CreateProcess failed (%d).\n", GetLastError() );
			return 0;
		}
#else
		std::cout << "Please Update to Version: " << Body << std::endl;
#endif
		return 0;
	}
	*/
	srand((unsigned)time(NULL));
	m_mechHRImage.LoadFromFile("Resources/RHeavyLow.png");
	m_mechMRImage.LoadFromFile("Resources/RMediumLow.png");
	m_mechLRImage.LoadFromFile("Resources/RLightLow.png");
	m_mechHBImage.LoadFromFile("Resources/BHeavyLow.png");
	m_mechMBImage.LoadFromFile("Resources/BMediumLow.png");
	m_mechLBImage.LoadFromFile("Resources/BLightLow.png");
	plains.LoadFromFile("Resources/Plains.png");
	lWoods.LoadFromFile("Resources/LWoods.png");
	hWoods.LoadFromFile("Resources/HWoods.png");
	rocks.LoadFromFile("Resources/Rocks.png");
	TileMap::hexImage.LoadFromFile("Resources/Hexagon.png");
	States::MainMenu state;
	MainGame.GetWindow().SetIcon(m_mechMRImage.GetWidth(), m_mechMRImage.GetHeight(), m_mechMRImage.GetPixelsPtr());
	MainGame.SetState(state);
	

	while(MainGame.GetWindow().IsOpened())
	{
		MainGame.Step();
	}	
}
