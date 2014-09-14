#include "character.h"

character::character(void)
{
}

character::character(const character& charact)
{
	//items = charact.items;
	attributes = charact.attributes;
	details = charact.details;
	relationships = charact.relationships;
	sprites = charact.sprites;
	resetPosition = charact.resetPosition;
	history = charact.history;
	traits = charact.traits;
}

character::~character(void)
{
}

void character::modifyAttribute(std::string skill, int modifier)
{
	attributes[skill] += modifier;
}

void character::addDetails(std::string detailName, std::string value)
{
	details[detailName] = value;
}

void character::loadFromFile(std::string fileName)
{
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	std::ifstream jsonFile(fileName, std::ifstream::binary);
	std::string error;
	bool parsingSuccessful = reader.parse( jsonFile, root, false );
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		std::cout  << reader.getFormatedErrorMessages()
			<< "Could not parse character file " << fileName << " it will not be loaded!\n";
	}
	try
	{
		for(unsigned int i = 0; i < root["attributes"].getMemberNames().size(); ++i)
		{
			error = "attributes";
			modifyAttribute(root["attributes"].getMemberNames()[i], root["attributes"][root["attributes"].getMemberNames()[i]].asInt());
		}

		for(unsigned int i = 0; i < root["history"].size(); ++i)
		{
			error = "history";
			//std::cout << root["history"][i].asString() << std::endl;
			history.push_back(root["history"][i].asString());
		}

		for(unsigned int i = 0; i < root["traits"].size(); ++i)
		{
			error = "traits";
			traits.push_back(root["traits"][i].asString());
		}

		for(unsigned int i = 0; i < root.getMemberNames().size(); ++i)
		{
			error = root.getMemberNames()[i] + " generation";
			if (root.getMemberNames()[i] != "attributes" 
				&& root.getMemberNames()[i] != "history" 
				&& root.getMemberNames()[i] != "traits")
				addDetails(root.getMemberNames()[i], root[root.getMemberNames()[i]].asString());
		}
	}
	catch (...)
	{
		std::cout << "Failed to load character file: " << fileName  << " at: " << error << std::endl;
	}
	jsonFile.close();
}

int character::getAttribute(std::string attribute)
{
	return attributes[attribute];
}

std::string character::getDetails(std::string detail)
{
	return details[detail];
}

void character::setDetails(std::string detail, std::string value)
{
	details[detail] = value;
}

//void character::giveItem(std::string itemID)
//{
//	std::transform(itemID.begin(), itemID.end(), itemID.begin(), ::tolower);
//	items.emplace_back(itemID);
//}
//
//bool character::hasItem(std::string item)
//{
//	std::transform(item.begin(), item.end(), item.begin(), ::tolower);
//	for (unsigned int i = 0; i < items.size(); i++)
//	{
//		if (items.at(i).find(item) != std::string::npos)
//			return true;
//	}
//	return false;
//}

int character::getRelationship(std::string charName)
{
	return relationships[charName];
}

void character::modifyRelationship(std::string charName, int modifier)
{
	relationships[charName] += modifier;
}

void character::setPosition(float x, float y)
{
	for(unsigned int i = 0; i < sprites.size(); i++)
	{
		sprites.at(i).setPosition(x,y);
	}
}

sf::Vector2f character::getPosition()
{
	return sprites.at(0).getPosition();
}

bool character::hasTrait(std::string trait)
{
	for (unsigned int i = 0; i < traits.size(); i++)
	{
		if (traits.at(i).find(trait) != std::string::npos)
			return true;
	}
	return false;
}