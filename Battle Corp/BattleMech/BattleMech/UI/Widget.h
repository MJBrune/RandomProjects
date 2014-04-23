#ifndef GUI_WIDGET
#define GUI_WIDGET

#include <SFML/Window.hpp>



namespace UI
{
	class Widget
	{
	public:
		Widget()
			:bBox(0,0,0,0)
		{

		}

		virtual void Click(const sf::Mouse::Button &button) = 0;		//Mouse clicks inside the	bBox
		
		virtual void UnClick(const sf::Mouse::Button &button) = 0;		//Mouse clicks outside the	bBox
		
		virtual void Hover() = 0;										//Mouse is hovered over the bBox
		virtual void UnHover() = 0;										//Mouse is not hovered over bBox

		virtual void KeyPress(const sf::Key::Code &code) = 0;
		virtual void TextInput(const sf::Uint32 &code) = 0;

		const sf::FloatRect &GetBoundingBox(){return bBox;}

	protected:
		sf::FloatRect bBox;

	};
}

#endif