#ifndef GAME_BASE_STATE
#define GAME_BASE_STATE


class GameState
{
public:
	GameState();

	virtual void Update(float timespan)	= 0;
	virtual void Render()				= 0;
	virtual void Init()					= 0;
	virtual void Exit()					= 0;
private:
protected:
};


#endif