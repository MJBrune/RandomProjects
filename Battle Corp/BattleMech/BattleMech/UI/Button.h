#ifndef UI_BUTTON
#define UI_BUTTON

#include "Widget.h"
#include <SFML/Graphics.hpp>


namespace UI
{
	class Button:public Widget
	{
	public:
		Button(const sf::FloatRect &rect)
		{
			this->bBox = rect;
			evnt_clicked = false;
		}

		virtual void Click(const sf::Mouse::Button &button) 
		{
			evnt_clicked = true;
		}
		
		virtual void UnClick(const sf::Mouse::Button &button){}
		
		virtual void Hover(){};	
		virtual void UnHover(){};

		virtual void KeyPress(const sf::Key::Code &code){}

		virtual void TextInput(const sf::Uint32 &code){}


		const bool &IsClicked()
		{
			bool orig		= evnt_clicked;
			evnt_clicked	= false;

			return orig;
		}

		void ResetEvents()
		{
			evnt_clicked = false;
		}

		void SetPosition(const sf::Vector2f &pos)
		{
			float width		= bBox.GetWidth();
			float height	= bBox.GetHeight();

			bBox = sf::FloatRect(pos.x, pos.y, pos.x + width, pos.y + height);
		}

		const sf::Vector2f GetPosition()
		{
			return sf::Vector2f(bBox.Left, bBox.Top);
		}

	private:
	protected:
		bool evnt_clicked;
	};
}

#endif