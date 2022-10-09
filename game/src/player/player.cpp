#include "player.h"

Player::Player(glm::vec3 pos, glm::vec2 size)
{
	this->entity = Global::e_manager->add_entity<Sparky::Entity>(Global::e_manager);
	this->tcomp  = this->entity->add_component<Sparky::TransformComponent>(pos, size);
	this->rcomp  = this->entity->add_component<Sparky::RenderComponent>(glm::vec4(1,0,1,1), glm::vec4(0,0,1,1), Global::white);

	this->id = this->entity->get_id();
	this->reset_movement();
}

Player::~Player()
{
}

void Player::reset_movement()
{
	this->movement["left"]  = false;
	this->movement["right"] = false;
	this->movement["up"]    = false;
	this->movement["down"]  = false;
}

void Player::on_event(SparkyEvent event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_w:
				this->movement["up"] = true;
				break;

			case SDLK_a:
				this->movement["left"] = true;
				break;

			case SDLK_s:
				this->movement["down"] = true;
				break;

			case SDLK_d:
				this->movement["right"] = true;
				break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_w:
				this->movement["up"] = false;
				break;

			case SDLK_a:
				this->movement["left"] = false;
				break;

			case SDLK_s:
				this->movement["down"] = false;
				break;

			case SDLK_d:
				this->movement["right"] = false;
				break;
		}
	}
}

void Player::on_update(double dt)
{
	glm::vec3 pos = this->tcomp->get_pos();
	if (this->movement["up"])    pos.y += this->speed * dt;
	if (this->movement["down"])  pos.y -= this->speed * dt;
	if (this->movement["left"])  pos.x -= this->speed * dt;
	if (this->movement["right"]) pos.x += this->speed * dt;
	this->tcomp->set_pos(pos);
}
