CC = g++ -w

SP = ../../sparky_2.0/sparky/
LINC = -I$(SP) -I$(SP)vendor/GLEW/include -I$(SP)vendor/SDL2_64bit/include -I$(SP)vendor/SDL2_64bit/include/SDL2 -I$(SP)vendor/imgui/
LIBP = -L../../sparky_2.0/bin/
LIB = -lsparky -lmingw32 -lopengl32 -lUser32 -lGdi32 -lShell32 -lglew32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -limm32

CPP = *.cpp
OBJ = *.o
OUT = game.exe

build:
	$(MAKE) --no-print-directory game_cmp_player
	$(MAKE) --no-print-directory game_cmp_game
	$(MAKE) --no-print-directory game_cmp_main
	$(MAKE) --no-print-directory game_build
	$(MAKE) --no-print-directory game_clean
	$(MAKE) --no-print-directory game_run

game_cmp_main:
	$(CC) $(LINC) -c main.cpp global.cpp

game_cmp_game:
	$(CC) $(LINC) -c game/*.cpp

game_cmp_player:
	$(CC) $(LINC) -c player/*.cpp

game_build:
	$(CC) -o $(OUT) $(OBJ) $(LIBP) $(LIB)
	copy $(OUT) ..\bin

game_clean:
	erase *.o
	erase $(OUT)

game_run:
	..\bin\$(OUT)

