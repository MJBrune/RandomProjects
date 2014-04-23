#include "Player.h"

Player::Player(int shov, int heart, int gold, int gem)
	:Shovel(shov),
	Heart(heart),
	Gold(gold),
	Gem(gem)
{
	ShovelText.setString("Shovels: "+convertInt(Shovel));
	HeartText.setString("Heart: "+convertInt(Heart));
	GoldText.setString("Gold: "+convertInt(Gold));
	GemText.setString("Gem: "+ convertInt(Gem));
}

void Player::adjustItem(Item::Type item, int adjust)
{
	switch(item)
	{
	case Item::Type::Shovel:
		Shovel += adjust;
		ShovelText.setString("Shovels: "+convertInt(Shovel));
		break;
	case Item::Type::Heart:
		Heart += adjust;
		HeartText.setString("Heart: "+convertInt(Heart));
		break;
	case Item::Type::Gold:
		Gold += adjust;
		GoldText.setString("Gold: "+convertInt(Gold));
		break;
	case Item::Type::Gem:
		Gem += adjust;
		GemText.setString("Gem: "+ convertInt(Gem));
		break;
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(ShovelText);
	window.draw(HeartText);
	window.draw(GoldText);
	window.draw(GemText);
}

void Player::setTextPosition(int x, int y)
{
	ShovelText.setPosition(x,y);
	HeartText.setPosition(x,y+50);
	GoldText.setPosition(x,y+100);
	GemText.setPosition(x,y+150);
}

void Player::setLeaderPosition(Item::Type type)
{
	switch(type)
	{
	case Item::Type::Heart:
		NameText.setPosition(HeartText.getPosition().x-150,HeartText.getPosition().y);
		HeartText.setString(convertInt(Heart));
		break;
	case Item::Type::Gold:
		NameText.setPosition(GoldText.getPosition().x-150,GoldText.getPosition().y);
		GoldText.setString(convertInt(Gold));
		break;
	case Item::Type::Gem:
		NameText.setPosition(GemText.getPosition().x-150,GemText.getPosition().y);
		GemText.setString(convertInt(Gem));
		break;
	}
}

void Player::SetName(std::string name)
{
	playerName = name;
	NameText.setString(name);
}

void Player::DrawLeader(sf::RenderWindow& window, Item::Type type)
{
	window.draw(NameText);
	switch(type)
	{
	case Item::Type::Heart:
		window.draw(HeartText);
		break;
	case Item::Type::Gold:
		window.draw(GoldText);
		break;
	case Item::Type::Gem:
		window.draw(GemText);
		break;
	}
}