# Compiler flags...
CPP_COMPILER = g++ --std=c++11
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=
Release_Include_Path=

# Library paths...
Debug_Library_Path=
Release_Library_Path=

# Additional libraries...
Debug_Libraries=-Wl,--start-group -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network  -Wl,--end-group
Release_Libraries=-Wl,--start-group -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network  -Wl,--end-group

# Preprocessor definitions...
Debug_Preprocessor_Definitions=-D GCC_BUILD 
Release_Preprocessor_Definitions=-D GCC_BUILD 

# Implictly linked object files...
Debug_Implicitly_Linked_Objects=
Release_Implicitly_Linked_Objects=

# Compiler flags...
Debug_Compiler_Flags=-O0 -g 
Release_Compiler_Flags=-O2 -g 

# Builds all configurations for this project...
.PHONY: build_all_configurations
build_all_configurations: Debug Release 

# Builds the Debug configuration...
.PHONY: Debug
Debug: create_folders gccDebug/GameManager.o gccDebug/GameState.o gccDebug/Globals.o gccDebug/HelperFunctions.o gccDebug/main.o gccDebug/Mech.o gccDebug/Tile.o gccDebug/TileMap.o gccDebug/Network/GameClient.o gccDebug/Network/Server.o gccDebug/Network/ServerClient.o gccDebug/States/BattleMech.o gccDebug/States/MainMenu.o gccDebug/States/MechMenu.o gccDebug/States/OptionMenu.o gccDebug/Network/Button.o gccDebug/Network/Text.o gccDebug/Network/Widget.o 
	g++ gccDebug/GameManager.o gccDebug/GameState.o gccDebug/Globals.o gccDebug/HelperFunctions.o gccDebug/main.o gccDebug/Mech.o gccDebug/Tile.o gccDebug/TileMap.o gccDebug/Network/GameClient.o gccDebug/Network/Server.o gccDebug/Network/ServerClient.o gccDebug/States/BattleMech.o gccDebug/States/MainMenu.o gccDebug/States/MechMenu.o gccDebug/States/OptionMenu.o gccDebug/Network/Button.o gccDebug/Network/Text.o gccDebug/Network/Widget.o  $(Debug_Library_Path) $(Debug_Libraries) -Wl,-rpath,./ -o ../gccDebug/BattleCorp

# Compiles file GameManager.cpp for the Debug configuration...
-include gccDebug/GameManager.d
gccDebug/GameManager.o: GameManager.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c GameManager.cpp $(Debug_Include_Path) -o gccDebug/GameManager.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM GameManager.cpp $(Debug_Include_Path) > gccDebug/GameManager.d

# Compiles file GameState.cpp for the Debug configuration...
-include gccDebug/GameState.d
gccDebug/GameState.o: GameState.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c GameState.cpp $(Debug_Include_Path) -o gccDebug/GameState.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM GameState.cpp $(Debug_Include_Path) > gccDebug/GameState.d

# Compiles file Globals.cpp for the Debug configuration...
-include gccDebug/Globals.d
gccDebug/Globals.o: Globals.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Globals.cpp $(Debug_Include_Path) -o gccDebug/Globals.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Globals.cpp $(Debug_Include_Path) > gccDebug/Globals.d

# Compiles file HelperFunctions.cpp for the Debug configuration...
-include gccDebug/HelperFunctions.d
gccDebug/HelperFunctions.o: HelperFunctions.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c HelperFunctions.cpp $(Debug_Include_Path) -o gccDebug/HelperFunctions.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM HelperFunctions.cpp $(Debug_Include_Path) > gccDebug/HelperFunctions.d

# Compiles file main.cpp for the Debug configuration...
-include gccDebug/main.d
gccDebug/main.o: main.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c main.cpp $(Debug_Include_Path) -o gccDebug/main.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM main.cpp $(Debug_Include_Path) > gccDebug/main.d

# Compiles file Mech.cpp for the Debug configuration...
-include gccDebug/Mech.d
gccDebug/Mech.o: Mech.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Mech.cpp $(Debug_Include_Path) -o gccDebug/Mech.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Mech.cpp $(Debug_Include_Path) > gccDebug/Mech.d

# Compiles file Tile.cpp for the Debug configuration...
-include gccDebug/Tile.d
gccDebug/Tile.o: Tile.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Tile.cpp $(Debug_Include_Path) -o gccDebug/Tile.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Tile.cpp $(Debug_Include_Path) > gccDebug/Tile.d

# Compiles file TileMap.cpp for the Debug configuration...
-include gccDebug/TileMap.d
gccDebug/TileMap.o: TileMap.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c TileMap.cpp $(Debug_Include_Path) -o gccDebug/TileMap.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM TileMap.cpp $(Debug_Include_Path) > gccDebug/TileMap.d

# Compiles file Network/GameClient.cpp for the Debug configuration...
-include gccDebug/Network/GameClient.d
gccDebug/Network/GameClient.o: Network/GameClient.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Network/GameClient.cpp $(Debug_Include_Path) -o gccDebug/Network/GameClient.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Network/GameClient.cpp $(Debug_Include_Path) > gccDebug/Network/GameClient.d

# Compiles file Network/Server.cpp for the Debug configuration...
-include gccDebug/Network/Server.d
gccDebug/Network/Server.o: Network/Server.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Network/Server.cpp $(Debug_Include_Path) -o gccDebug/Network/Server.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Network/Server.cpp $(Debug_Include_Path) > gccDebug/Network/Server.d

# Compiles file Network/ServerClient.cpp for the Debug configuration...
-include gccDebug/Network/ServerClient.d
gccDebug/Network/ServerClient.o: Network/ServerClient.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Network/ServerClient.cpp $(Debug_Include_Path) -o gccDebug/Network/ServerClient.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Network/ServerClient.cpp $(Debug_Include_Path) > gccDebug/Network/ServerClient.d

# Compiles file States/BattleMech.cpp for the Debug configuration...
-include gccDebug/States/BattleMech.d
gccDebug/States/BattleMech.o: States/BattleMech.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c States/BattleMech.cpp $(Debug_Include_Path) -o gccDebug/States/BattleMech.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM States/BattleMech.cpp $(Debug_Include_Path) > gccDebug/States/BattleMech.d

# Compiles file States/MainMenu.cpp for the Debug configuration...
-include gccDebug/States/MainMenu.d
gccDebug/States/MainMenu.o: States/MainMenu.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c States/MainMenu.cpp $(Debug_Include_Path) -o gccDebug/States/MainMenu.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM States/MainMenu.cpp $(Debug_Include_Path) > gccDebug/States/MainMenu.d

# Compiles file States/MechMenu.cpp for the Debug configuration...
-include gccDebug/States/MechMenu.d
gccDebug/States/MechMenu.o: States/MechMenu.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c States/MechMenu.cpp $(Debug_Include_Path) -o gccDebug/States/MechMenu.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM States/MechMenu.cpp $(Debug_Include_Path) > gccDebug/States/MechMenu.d

# Compiles file States/OptionMenu.cpp for the Debug configuration...
-include gccDebug/States/OptionMenu.d
gccDebug/States/OptionMenu.o: States/OptionMenu.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c States/OptionMenu.cpp $(Debug_Include_Path) -o gccDebug/States/OptionMenu.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM States/OptionMenu.cpp $(Debug_Include_Path) > gccDebug/States/OptionMenu.d

# Compiles file Network/Button.cpp for the Debug configuration...
-include gccDebug/Network/Button.d
gccDebug/Network/Button.o: Network/Button.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Network/Button.cpp $(Debug_Include_Path) -o gccDebug/Network/Button.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Network/Button.cpp $(Debug_Include_Path) > gccDebug/Network/Button.d

# Compiles file Network/Text.cpp for the Debug configuration...
-include gccDebug/Network/Text.d
gccDebug/Network/Text.o: Network/Text.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Network/Text.cpp $(Debug_Include_Path) -o gccDebug/Network/Text.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Network/Text.cpp $(Debug_Include_Path) > gccDebug/Network/Text.d

# Compiles file Network/Widget.cpp for the Debug configuration...
-include gccDebug/Network/Widget.d
gccDebug/Network/Widget.o: Network/Widget.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Network/Widget.cpp $(Debug_Include_Path) -o gccDebug/Network/Widget.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Network/Widget.cpp $(Debug_Include_Path) > gccDebug/Network/Widget.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/GameManager.o gccRelease/GameState.o gccRelease/Globals.o gccRelease/HelperFunctions.o gccRelease/main.o gccRelease/Mech.o gccRelease/Tile.o gccRelease/TileMap.o gccRelease/Network/GameClient.o gccRelease/Network/Server.o gccRelease/Network/ServerClient.o gccRelease/States/BattleMech.o gccRelease/States/MainMenu.o gccRelease/States/MechMenu.o gccRelease/States/OptionMenu.o gccRelease/Network/Button.o gccRelease/Network/Text.o gccRelease/Network/Widget.o 
	g++ gccRelease/GameManager.o gccRelease/GameState.o gccRelease/Globals.o gccRelease/HelperFunctions.o gccRelease/main.o gccRelease/Mech.o gccRelease/Tile.o gccRelease/TileMap.o gccRelease/Network/GameClient.o gccRelease/Network/Server.o gccRelease/Network/ServerClient.o gccRelease/States/BattleMech.o gccRelease/States/MainMenu.o gccRelease/States/MechMenu.o gccRelease/States/OptionMenu.o gccRelease/Network/Button.o gccRelease/Network/Text.o gccRelease/Network/Widget.o  $(Release_Library_Path) $(Release_Libraries) -Wl,-rpath,./ -o ../gccRelease/BattleCorp

# Compiles file GameManager.cpp for the Release configuration...
-include gccRelease/GameManager.d
gccRelease/GameManager.o: GameManager.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c GameManager.cpp $(Release_Include_Path) -o gccRelease/GameManager.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM GameManager.cpp $(Release_Include_Path) > gccRelease/GameManager.d

# Compiles file GameState.cpp for the Release configuration...
-include gccRelease/GameState.d
gccRelease/GameState.o: GameState.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c GameState.cpp $(Release_Include_Path) -o gccRelease/GameState.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM GameState.cpp $(Release_Include_Path) > gccRelease/GameState.d

# Compiles file Globals.cpp for the Release configuration...
-include gccRelease/Globals.d
gccRelease/Globals.o: Globals.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Globals.cpp $(Release_Include_Path) -o gccRelease/Globals.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Globals.cpp $(Release_Include_Path) > gccRelease/Globals.d

# Compiles file HelperFunctions.cpp for the Release configuration...
-include gccRelease/HelperFunctions.d
gccRelease/HelperFunctions.o: HelperFunctions.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c HelperFunctions.cpp $(Release_Include_Path) -o gccRelease/HelperFunctions.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM HelperFunctions.cpp $(Release_Include_Path) > gccRelease/HelperFunctions.d

# Compiles file main.cpp for the Release configuration...
-include gccRelease/main.d
gccRelease/main.o: main.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c main.cpp $(Release_Include_Path) -o gccRelease/main.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM main.cpp $(Release_Include_Path) > gccRelease/main.d

# Compiles file Mech.cpp for the Release configuration...
-include gccRelease/Mech.d
gccRelease/Mech.o: Mech.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Mech.cpp $(Release_Include_Path) -o gccRelease/Mech.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Mech.cpp $(Release_Include_Path) > gccRelease/Mech.d

# Compiles file Tile.cpp for the Release configuration...
-include gccRelease/Tile.d
gccRelease/Tile.o: Tile.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Tile.cpp $(Release_Include_Path) -o gccRelease/Tile.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Tile.cpp $(Release_Include_Path) > gccRelease/Tile.d

# Compiles file TileMap.cpp for the Release configuration...
-include gccRelease/TileMap.d
gccRelease/TileMap.o: TileMap.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c TileMap.cpp $(Release_Include_Path) -o gccRelease/TileMap.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM TileMap.cpp $(Release_Include_Path) > gccRelease/TileMap.d

# Compiles file Network/GameClient.cpp for the Release configuration...
-include gccRelease/Network/GameClient.d
gccRelease/Network/GameClient.o: Network/GameClient.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Network/GameClient.cpp $(Release_Include_Path) -o gccRelease/Network/GameClient.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Network/GameClient.cpp $(Release_Include_Path) > gccRelease/Network/GameClient.d

# Compiles file Network/Server.cpp for the Release configuration...
-include gccRelease/Network/Server.d
gccRelease/Network/Server.o: Network/Server.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Network/Server.cpp $(Release_Include_Path) -o gccRelease/Network/Server.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Network/Server.cpp $(Release_Include_Path) > gccRelease/Network/Server.d

# Compiles file Network/ServerClient.cpp for the Release configuration...
-include gccRelease/Network/ServerClient.d
gccRelease/Network/ServerClient.o: Network/ServerClient.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Network/ServerClient.cpp $(Release_Include_Path) -o gccRelease/Network/ServerClient.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Network/ServerClient.cpp $(Release_Include_Path) > gccRelease/Network/ServerClient.d

# Compiles file States/BattleMech.cpp for the Release configuration...
-include gccRelease/States/BattleMech.d
gccRelease/States/BattleMech.o: States/BattleMech.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c States/BattleMech.cpp $(Release_Include_Path) -o gccRelease/States/BattleMech.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM States/BattleMech.cpp $(Release_Include_Path) > gccRelease/States/BattleMech.d

# Compiles file States/MainMenu.cpp for the Release configuration...
-include gccRelease/States/MainMenu.d
gccRelease/States/MainMenu.o: States/MainMenu.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c States/MainMenu.cpp $(Release_Include_Path) -o gccRelease/States/MainMenu.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM States/MainMenu.cpp $(Release_Include_Path) > gccRelease/States/MainMenu.d

# Compiles file States/MechMenu.cpp for the Release configuration...
-include gccRelease/States/MechMenu.d
gccRelease/States/MechMenu.o: States/MechMenu.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c States/MechMenu.cpp $(Release_Include_Path) -o gccRelease/States/MechMenu.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM States/MechMenu.cpp $(Release_Include_Path) > gccRelease/States/MechMenu.d

# Compiles file States/OptionMenu.cpp for the Release configuration...
-include gccRelease/States/OptionMenu.d
gccRelease/States/OptionMenu.o: States/OptionMenu.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c States/OptionMenu.cpp $(Release_Include_Path) -o gccRelease/States/OptionMenu.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM States/OptionMenu.cpp $(Release_Include_Path) > gccRelease/States/OptionMenu.d

# Compiles file Network/Button.cpp for the Release configuration...
-include gccRelease/Network/Button.d
gccRelease/Network/Button.o: Network/Button.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Network/Button.cpp $(Release_Include_Path) -o gccRelease/Network/Button.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Network/Button.cpp $(Release_Include_Path) > gccRelease/Network/Button.d

# Compiles file Network/Text.cpp for the Release configuration...
-include gccRelease/Network/Text.d
gccRelease/Network/Text.o: Network/Text.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Network/Text.cpp $(Release_Include_Path) -o gccRelease/Network/Text.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Network/Text.cpp $(Release_Include_Path) > gccRelease/Network/Text.d

# Compiles file Network/Widget.cpp for the Release configuration...
-include gccRelease/Network/Widget.d
gccRelease/Network/Widget.o: Network/Widget.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Network/Widget.cpp $(Release_Include_Path) -o gccRelease/Network/Widget.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Network/Widget.cpp $(Release_Include_Path) > gccRelease/Network/Widget.d

# Creates the intermediate and output folders for each configuration...
.PHONY: create_folders
create_folders:
	mkdir -p gccDebug
	mkdir -p gccDebug/Network
	mkdir -p gccDebug/States
	mkdir -p ../gccDebug
	mkdir -p gccRelease
	mkdir -p gccRelease/Network
	mkdir -p gccRelease/States
	mkdir -p ../gccRelease

# Cleans intermediate and output files (objects, libraries, executables)...
.PHONY: clean
clean:
	rm -f gccDebug/*.o
	rm -f gccDebug/*.d
	rm -f ../gccDebug/*.a
	rm -f ../gccDebug/*.so
	rm -f ../gccDebug/*.dll
	rm -f ../gccDebug/*.exe
	rm -f gccRelease/*.o
	rm -f gccRelease/*.d
	rm -f ../gccRelease/*.a
	rm -f ../gccRelease/*.so
	rm -f ../gccRelease/*.dll
	rm -f ../gccRelease/*.exe

