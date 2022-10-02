SP = ../sparky_2.0/sparky/
LINC = -I$(SP) -I$(SP)vendor/GLEW/include -I$(SP)vendor/SDL2_64bit/include -I$(SP)vendor/SDL2_64bit/include/SDL2 -I$(SP)vendor/imgui/
CPP = *.cpp
OBJ = *.o
LIBP = -L../sparky_2.0/bin/
LIB = -lsparky -lmingw32 -lopengl32 -lUser32 -lGdi32 -lShell32 -lglew32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -limm32

OUT = game.exe

game:
	$(MAKE) --no-print-directory game_cmp
	$(MAKE) --no-print-directory game_clean
	$(MAKE) --no-print-directory game_run

game_cmp:
	g++ $(LINC) -c $(CPP)
	g++ -o $(OUT) $(OBJ) $(LIBP) $(LIB)

game_clean:
	erase *.o

game_run:
	$(OUT)

