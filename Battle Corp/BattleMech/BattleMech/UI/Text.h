#ifndef UI_TEXT
#define UI_TEXT

#include "Widget.h"
#include <string>
#include <iostream>

namespace UI
{
	class Text:public Widget
	{
	public:
		
		Text(const std::string &startText = "")
		{
			textStr			= startText;
			isActive		= false;
			evnt_entered	= false;
		}
		
		virtual void Click(const sf::Mouse::Button &button) 
		{
			isActive = true;
		}//Mouse clicks inside the	bBox
		
		virtual void UnClick(const sf::Mouse::Button &button)
		{
			isActive = false;
		}//Mouse clicks outside the	bBox
		
		virtual void Hover(){};										//Mouse is hovered over the bBox
		virtual void UnHover(){};										//Mouse is not hovered over bBox

		virtual void KeyPress(const sf::Key::Code &code){}

		virtual void TextInput(const sf::Uint32 &code)
		{
			switch(code)
			{
				default:
				textStr += (char)code;
				break;
				case 8://backspace
				if(textStr.size() > 0)
				{
					textStr.pop_back();
				}
				break;
				case 13://enter key
				evnt_entered = true;
				break;
			}
		}

		const std::string &TextString()
		{
			return textStr;
		}

		const bool TextEntered()
		{
			bool org = evnt_entered;
			evnt_entered = false;
			return org;
		}

	private:

		bool			isActive;
		bool			evnt_entered;
		
		std::string		textStr;

	};

}
#endif