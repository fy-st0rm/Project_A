#include "mob.h"

void Mob::init(glm::vec3 pos, glm::vec2 size, float speed, const std::string& img_path)
{
	this->speed   = speed;
	this->texture = std::make_shared<Sparky::Texture>(img_path);

	this->entity = Global::e_manager->add_entity<Sparky::Entity>(Global::e_manager);
	this->tcomp  = this->entity->add_component<Sparky::TransformComponent>(pos, size, rotation_x(this->angle));
	this->rcomp  = this->entity->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,1), glm::vec4(0,0,1,1), this->texture);
	this->acomp  = this->entity->add_component<Sparky::AnimationComponent>();

	this->id = this->entity->get_id();
	this->reset_movement();
}

void Mob::reset_movement()
{
	this->movement[LEFT]  = false;
	this->movement[RIGHT] = false;
	this->movement[UP]    = false;
	this->movement[DOWN]  = false;
}

void Mob::update_movement(double dt)
{
	glm::vec3 pos = this->tcomp->get_pos();
	if (this->movement[UP])    pos.y += this->speed * dt;
	if (this->movement[DOWN])  pos.y -= this->speed * dt;
	if (this->movement[LEFT])  pos.x -= this->speed * dt;
	if (this->movement[RIGHT]) pos.x += this->speed * dt;
	this->tcomp->set_pos(pos);
}

void Mob::update_animation()
{
	if (this->movement[UP])
	{
		std::vector<std::string> state = { WALK };
		this->acomp->switch_state(state);
	}
	else if (this->movement[DOWN])
	{
		std::vector<std::string> state = { WALK };
		this->acomp->switch_state(state);
	}
	else if (this->movement[LEFT])
	{
		this->angle = 180.0f;
		this->tcomp->set_rotation(rotation_y(this->angle));
		std::vector<std::string> state = { WALK };
		this->acomp->switch_state(state);
	}
	else if (this->movement[RIGHT])
	{
		this->angle = 0.0f;
		this->tcomp->set_rotation(rotation_y(this->angle));
		std::vector<std::string> state = { WALK };
		this->acomp->switch_state(state);
	}
	else
	{
		std::vector<std::string> state = { IDLE };
		this->acomp->switch_state(state);
	}
}

void Mob::load_frame(const std::string& name, float speed, float y, float start, float end, float max_w, float max_h)
{
	std::vector<glm::vec4> cords;
	for (float i = start; i < end; i++)
		cords.push_back({ i / max_w, y / max_h, 1 / max_w, 1 / max_h });

	Sparky::AnimationNode node(name, cords, speed);
	this->acomp->add_node(node);
}
