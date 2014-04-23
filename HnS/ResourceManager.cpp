#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadTexture(std::string fileName)
{
	textureManager[fileName].loadFromFile(fileName);
}

sf::Texture* ResourceManager::getTexture(std::string fileName)
{
	return &textureManager[fileName];
}

void ResourceManager::setSmooth(bool smooth)
{
	for(std::unordered_map<std::string, sf::Texture>::iterator iterator = textureManager.begin(); iterator != textureManager.end(); iterator++) 
	{
		iterator->second.setSmooth(smooth);
	}
}

void ResourceManager::loadFont(std::string fileName)
{
	fontManager[fileName].loadFromFile(fileName);
}

sf::Font* ResourceManager::getFont(std::string fileName)
{
	return &fontManager[fileName];
}