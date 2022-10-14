#include "../global.h"
#include "../ui_elements/button.h"

class MainMenu : public Sparky::Scene
{
public:
	MainMenu(Sparky::Application* app);
	~MainMenu();

public:
	void on_entry();
	void on_exit();
	void on_event(SparkyEvent event);
	void on_update(double dt);

private:
	Sparky::Application* app;
	Button* start_button;
	Button* quit_button;

	std::shared_ptr<Sparky::Texture> button_texture;
};
