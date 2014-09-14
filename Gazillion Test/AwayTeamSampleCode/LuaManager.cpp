#include "LuaManager.h"


luaManager::luaManager(MissionManager& miss, CharacterManager& charact, ship& PShip)
	:
	msnMgr(miss),
	charMgr(charact),
	playerShip(PShip),
	lastStatus(0)
{
	try
	{
		LuaState = luaL_newstate();

		luabind::open(LuaState);
		//changed
		luabind::module(LuaState) [
			luabind::class_<MissionManager>("missionManager")
				.def("addMessage", (void (MissionManager::*)(std::string))&MissionManager::addLuaMessage)
				.def("addHeader", (void (MissionManager::*)(std::string))&MissionManager::addHeader)
				.def("addQuestItem", &MissionManager::addQuestItem)
				.def("removeQuestItem", &MissionManager::removeQuestItem)
				.def("hasQuestItem", &MissionManager::hasQuestItem)
				.def("buildChoice", &MissionManager::buildChoice)
				.def("finalizeChoice", &MissionManager::finalizeChoice)
				.def("getChoiceResponse", &MissionManager::getChoiceResponse)
				.def("endMission", &MissionManager::endMission)
				.def("getDeployStatus", &MissionManager::getDeployStatus)
		];

		luabind::module(LuaState) [
			luabind::class_<ship>("ship")
				.def("getHealth", &ship::getHealth)
				.def("getSensors", &ship::getSensors)
				.def("getShields", &ship::getShields)
				.def("getEngineSpeed", &ship::getEngineSpeed)
				.def("adjustFood", &ship::adjustFood)
				.def("adjustFuel", &ship::adjustFuel)
				.def("adjustHealth", &ship::adjustHealth)
				.def("adjustSensors", &ship::adjustSensors)
				.def("adjustShields", &ship::adjustShields)
				.def("adjustEngineSpeed", &ship::adjustEngineSpeed)
		];

		luabind::module(LuaState) [
			luabind::class_<CharacterManager>("characterManager")
				.def("getCharDetail", &CharacterManager::getCharDetail)
				.def("getCharAttr", &CharacterManager::getCharAttr)
				//.def("giveCharItem", &CharacterManager::giveCharItem)
				//.def("takeCharItem", &CharacterManager::takeCharItem)
				//.def("charHasItem", &CharacterManager::charHasItem)
				//.def("getItemAttr", &CharacterManager::getItemAttr)
				//.def("getItemDetail", &CharacterManager::getItemDetail)
				.def("getCrewTraits", &CharacterManager::getCrewTraits)
				.def("getCharTrait", &CharacterManager::getCharTrait)
				.def("randomCrew", &CharacterManager::randomCrew)
				.def("leastAttr", &CharacterManager::leastAttr)
				.def("mostAttr", &CharacterManager::mostAttr)
				.def("totalAttr", &CharacterManager::totalAttr)
				.def("crewWithMost", &CharacterManager::crewWithMost)
				.def("crewWithLeast", &CharacterManager::crewWithLeast)
				.def("killCrew", &CharacterManager::killCrew)
				.def("depCrewLeft", &CharacterManager::depCrewLeft)
				.def("newCrew", &CharacterManager::newCrew)
				.def("modifyRelationship", &CharacterManager::modifyRelationship)
				.def("getRelationship", &CharacterManager::getRelationship)
				.def("getMed", &CharacterManager::getMed)
				.def("getEng", &CharacterManager::getEng)
				.def("getLead", &CharacterManager::getLead)
		];

		luabind::globals(LuaState)["msnMgr"] = &msnMgr;
		luabind::globals(LuaState)["charMgr"] = &charMgr;
		luabind::globals(LuaState)["ship"] = &playerShip;
	}	
	catch(const std::exception &TheError)
	{
		std::cerr << "Lua Environment Failed!: " << TheError.what() << std::endl;
		exit(1);
	}
	std::cout << "Lua Environment Loaded" << std::endl;
}

void luaManager::doFile(std::string fileName)
{
	try
	{
		lastStatus = luaL_dofile(LuaState, fileName.c_str());
	}
	catch(const std::exception &TheError)
	{
		std::cerr << "Lua Environment Failed!: " << TheError.what() << std::endl;
		exit(1);
	}
	if (lastStatus != 0)
		std::cerr << "-- " << lua_tostring(LuaState, -1) << std::endl;
}

void luaManager::doString(std::string string)
{
	try
	{
		lastStatus = luaL_dostring(LuaState, string.c_str());
	}
	catch(const std::exception &TheError)
	{
		std::cerr << "Lua Environment Failed!: " << TheError.what() << std::endl;
		exit(1);
	}
	if (lastStatus != 0)
		std::cerr << "-- " << lua_tostring(LuaState, -1) << std::endl;
}

void luaManager::doThreadedFile(std::string fileName)
{
	if (!msnMgr.inDeploy)
	{
		msnMgr.inDeploy = true;
		msnMgr.deploy();
		task = std::async(std::launch::async, &luaManager::doFile, this, fileName);
	}
}

luaManager::~luaManager(void)
{
	if (msnMgr.inDeploy)
	{
		msnMgr.inDeploy = false;
		task.wait();
	}
	lua_close(LuaState);
}