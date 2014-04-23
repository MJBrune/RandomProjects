#ifndef STATE_TEST_CLIENT
#define STATE_TEST_CLIENT
#include "GameState.h"
#include "../Network/GameClient.h"
#include "../TileMap.h"
#include "../Globals.h"

namespace States
{
	class TestClient: public GameState
	{
	public:
		TestClient()
		{
			map.CreateBlankMap(1,1);
			client.Connect(sf::IPAddress("localhost"), 8000);
		}

		virtual void Update(float timespan)
		{
			client.Tick();
		}
		virtual void Render()
		{
			client.GetMap().Render(MainGame.GetWindow());
		}
		virtual void Init()
		{
		}
		virtual void Exit()
		{
		}

	private:
		TileMap map;
		Network::GameClient client;
	};
}

#endif