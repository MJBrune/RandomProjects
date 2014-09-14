#include "Vector2i.h"

Vector2i::Vector2i()
{
	m_x = 0;
	m_y = 0;
}

Vector2i::Vector2i(int x, int y)
{
	m_x = x;
	m_y = y;
}

Vector2i::Vector2i(int v, bool isX)
{
	if (isX)
		m_x = v;
	else
		m_y = v;
}