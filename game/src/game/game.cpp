#include "game.h"

Game::Game(Sparky::Application* app)
	:app(app)
{
	// Constructing player TODO: This is temporary. Player will be spawn according to the map
	this->player = std::make_shared<Player>(glm::vec3(100, 100, 0), glm::vec2(100, 100));
	
	Sparky::Log::sucess("Constructed game.", Sparky::SPARKY_NULL);
}

Game::~Game()
{
}

void Game::on_event(SparkyEvent event)
{
	this->player->on_event(event);
}

void Game::on_update(double dt)
{
	this->player->on_update(dt);
	Global::e_manager->update(Global::renderer);
}

