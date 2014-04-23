#ifndef STATES_MAINMENU
#define STATES_MAINMENU

#include <SFML/Graphics.hpp>
#include "../GameState.h"
#include "../Globals.h"
#include "../UI/Text.h"
#include "../UI/Button.h"
#include "BattleMech.h"
#include "MechMenu.h"
#include "OptionMenu.h"

extern States::BattleMech bMechGame;

namespace States
{
	class MainMenu: public GameState
	{
	private:
		std::vector<UI::Widget*>	widgets;
		UI::Button	*				exitBtn;
		UI::Text	*				ipText;
		UI::Button  *				joinBtn;
		UI::Button  *				hostJoinBtn;


		bool						enteringIpInfo;
		bool						enterForHostJoin;
		
		
		// debug only mechmenu button
	//	UI::Button *				OptionBtn;
	//	static States::OptionMenu	bOptionMenu;
		static States::MechMenu		bMechMenu;
	public:

		MainMenu();
		virtual void Update(float timespan);
		virtual void Render();
		virtual void Init();
		virtual void Exit();

	};
}

#endif