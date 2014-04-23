#include "Item.h"

Item::Item(Item::Type type)
	:VisibleGameObject(),
	itemType(type)
{
	switch(type)
	{
	case Item::Type::Nothing:
		//this->Load("dirt.jpg");
		break;
	case Item::Type::Shovel:
		this->Load("shovel.png");
		break;
	case Item::Type::Heart:
		this->Load("heart.png");
		break;
	case Item::Type::Gold:
		this->Load("gold.png");
		break;
	case Item::Type::Gem:
		this->Load("gem.png");
		break;
	}
}
void Item::setType(Item::Type type)
{
	itemType = type;
		switch(type)
	{
	case Item::Type::Nothing:
		//this->Load("dirt.jpg");
		break;
	case Item::Type::Shovel:
		this->Load("shovel.png");
		break;
	case Item::Type::Heart:
		this->Load("heart.png");
		break;
	case Item::Type::Gold:
		this->Load("gold.png");
		break;
	case Item::Type::Gem:
		this->Load("gem.png");
		break;
	}
}

void Item::Tween(sf::Vector2f destination, float speed){
	isMoving = true;
	moveSpeed = speed;
	destPos = destination;
}

void Item::Draw(sf::RenderWindow & window)
{
	//Should be moved to Update really, but update isn't called atm and cba so I just make an dTime var here kinda equal to 60FPS
	float dTime = 17;
	sf::Vector2f pos = VisibleGameObject::GetPosition();
	if(isMoving){
		sf::Vector2f deltaPos(destPos.x - pos.x, destPos.y - pos.y);

		//Persistent movement, more predictable
		/*
		float lnDeltaPos = sqrt(deltaPos.x * deltaPos.x + deltaPos.y * deltaPos.y);
		sf::Vector2f normalDeltaPos(deltaPos.x * lnDeltaPos, deltaPos.y * lnDeltaPos);
		pos.x += normalDeltaPos.x * (1000/dTime) * moveSpeed;
		pos.y += normalDeltaPos.y * (1000/dTime) * moveSpeed;
		*/
		
		//Smooth movement, less predictable
		pos.x += deltaPos.x * moveSpeed * (dTime / 1000);
		pos.y += deltaPos.y * moveSpeed * (dTime / 1000);
		
		if(abs(deltaPos.x) <= 1 && abs(deltaPos.y) <= 1){
			pos = destPos;
		}

		VisibleGameObject::SetPosition(pos.x, pos.y);
	}


	VisibleGameObject::Draw(window);
}