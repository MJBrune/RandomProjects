#include <SFML/Graphics.hpp>
#include "Diggy.h"

int main()
{
	DiggyState::Game diggy;
	diggy.setGamestate(DiggyState::Uninitialized);
	diggy.Start();
    return 0;
}