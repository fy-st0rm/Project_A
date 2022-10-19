#include "../global.h"
#include "../ui_elements/button.h"
#include "../network/client.h"

class MainMenu : public Sparky::Scene
{
public:
	MainMenu(Sparky::Application* app, Client* client);
	~MainMenu();

public:
	void on_entry();
	void on_exit();
	void on_event(SparkyEvent event);
	void on_update(double dt);

private:
	Sparky::Application* app;
	Client* client;
	Button* host_button;
	Button* join_button;
	Button* quit_button;

	std::shared_ptr<Sparky::Texture> button_texture;
};
