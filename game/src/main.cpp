#include "global.h"
#include "network/client.h"
#include "game/game.h"
#include "menu/main_menu.h"
#include "404.h"

class App : public Sparky::Application
{
private:
	std::shared_ptr<Client> client;

public:
	App()  {}
	~App()
	{
		// Sending disconnect payload
		Json::Value payload;
		this->client->send_payload(OP_DISCONNECT, payload);
	}

public:
	void on_start()
	{
		Global::init();

		// Initialzing networking
		this->client = std::make_shared<Client>("127.0.0.1", 5050);

		// Adding scenes
		add_scene<Game>(GAME, this);
		add_scene<MainMenu>(MAIN_MENU, this, this->client.get());
		add_scene<ErrorPage>(ERROR_PAGE, this);

		if (this->client->run() < 0)
			switch_scene(ERROR_PAGE);
		else
			switch_scene(MAIN_MENU);
	}
};

int main(int argc, char** argv)
{
	App app;
	app.run("Game", WIN_WIDTH, WIN_HEIGHT, FPS, SparkyWindowFullscreen);
	return 0;
}
