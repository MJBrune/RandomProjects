#ifndef _RESMGR_H
#define _RESMGR_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Splashscreen.h"
#include <unordered_map>
class ResourceManager
{
private:
	std::unordered_map<std::string, sf::Texture> textureManager;
	std::unordered_map<std::string, sf::Font> fontManager;
public:
	ResourceManager();
	~ResourceManager();
	void loadTexture(std::string fileName);
	sf::Texture* getTexture(std::string fileName);
	void loadFont(std::string fileName);
	sf::Font* getFont(std::string fileName);
	void setSmooth(bool smooth);
};
#endif