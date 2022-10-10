#pragma once
#include "../global.h"
#include "../mob/player/player.h"

class Game : public Sparky::Scene
{
public:
	Game(Sparky::Application* app);
	~Game();

public:
	void on_event(SparkyEvent event);
	void on_update(double dt);

private:
	Sparky::Application* app;

	std::shared_ptr<Player> player;
};
