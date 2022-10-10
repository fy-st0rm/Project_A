#include "global.h"
#include "game/game.h"

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
		add_scene<Game>("game", this);
		switch_scene("game");
	}
};

int main(int argc, char** argv)
{
	App app;
	app.run("Game", WIN_WIDTH, WIN_HEIGHT, FPS, SparkyWindowResizable);
	Global::clean();
	return 0;
}
