#include "global.h"
#include "game/game.h"
#include "menu/main_menu.h"

class App : public Sparky::Application
{
public:
	App()  {}
	~App() {}

public:
	void on_start()
	{
		SDL_MaximizeWindow(get_sparky_window()->get_sdl_window());
		Global::init();

		// Adding scenes
		add_scene<Game>(GAME, this);
		add_scene<MainMenu>(MAIN_MENU, this);
		switch_scene("main_menu");
	}
};

int main(int argc, char** argv)
{
	App app;
	app.run("Game", WIN_WIDTH, WIN_HEIGHT, FPS, SparkyWindowResizable);
	Global::clean();
	return 0;
}
