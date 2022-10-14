#include "game.h"

Game::Game(Sparky::Application* app)
	:app(app)
{
}

Game::~Game()
{
}

void Game::on_entry()
{
	// Constructing player TODO: This is temporary. Player will be spawn according to the map
	this->player = std::make_shared<Player>(glm::vec3(100, 100, 0));
}

void Game::on_exit()
{
	this->player.reset();
	Global::ui_renderer->clear_buffer();
}

void Game::on_event(SparkyEvent event)
{
	this->player->on_event(event);
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_ESCAPE:
				this->app->switch_scene(MAIN_MENU);
				break;
		}
	}
}

void Game::on_update(double dt)
{
	app->clear(glm::vec4(0.5,0.5,0.5,1.0f));
	this->player->on_update(dt);

	camera_follow_mob(Global::camera, this->player);
	Global::e_manager->update(Global::renderer);
}

