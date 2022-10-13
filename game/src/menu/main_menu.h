#include "../global.h"
#include "ui_elements/button.h"

#define BUTTON_IMG "assets/buttons.png"
#define BUTTON_MAX_CNT_X 4
#define BUTTON_MAX_CNT_Y 1
#define BUTTON_W 181
#define BUTTON_H 47

class MainMenu : public Sparky::Scene
{
public:
	MainMenu(Sparky::Application* app);
	~MainMenu();

public:
	void on_event(SparkyEvent event);
	void on_update(double dt);

private:
	Sparky::Application* app;
	Button* start_button;
	Button* quit_button;

	std::shared_ptr<Sparky::Texture> button_texture;
};
