#pragma once
//Basic Vector class I created in a few minutes.
class Vector2i
{
public:
	int m_x;
	int m_y;
	Vector2i();
	Vector2i(int x, int y);
	Vector2i(int v, bool isX = true);
};