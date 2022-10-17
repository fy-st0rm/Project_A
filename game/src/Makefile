CC = g++ -w

SP = ../../sparky_2.0/sparky/
LINC = -I$(SP) -I$(SP)vendor/GLEW/include -I$(SP)vendor/SDL2_64bit/include -I$(SP)vendor/SDL2_64bit/include/SDL2 -I$(SP)vendor/imgui/
LIBP = -L../../sparky_2.0/bin/
LIB = -lsparky -lmingw32 -lopengl32 -lUser32 -lGdi32 -lShell32 -lglew32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -limm32

CPP = *.cpp
OBJ = *.o
OUT = game.exe

build:
	$(MAKE) --no-print-directory game_cmp_mob
	$(MAKE) --no-print-directory game_cmp_player
	$(MAKE) --no-print-directory game_cmp_item
	$(MAKE) --no-print-directory game_cmp_inventory
	$(MAKE) --no-print-directory game_cmp_ui
	$(MAKE) --no-print-directory game_cmp_menu
	$(MAKE) --no-print-directory game_cmp_game
	$(MAKE) --no-print-directory game_cmp_main
	$(MAKE) --no-print-directory game_build
	$(MAKE) --no-print-directory game_clean

game_cmp_mob:
	$(CC) $(LINC) -c mob/*.cpp

game_cmp_player:
	$(CC) $(LINC) -c mob/player/*.cpp

game_cmp_item:
	$(CC) $(LINC) -c item/*.cpp

game_cmp_inventory:
	$(CC) $(LINC) -c inventory/*.cpp

game_cmp_ui:
	$(CC) $(LINC) -c ui_elements/*.cpp
	
game_cmp_menu:
	$(CC) $(LINC) -c menu/*.cpp

game_cmp_game:
	$(CC) $(LINC) -c game/*.cpp

game_cmp_main:
	$(CC) $(LINC) -c main.cpp global.cpp

game_build:
	$(CC) -o $(OUT) $(OBJ) $(LIBP) $(LIB)
	copy $(OUT) ..\bin

game_clean:
	erase *.o
	erase $(OUT)

game_run:
	..\bin\$(OUT)

