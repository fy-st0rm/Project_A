#include "button.h"

Button::Button(const std::string& name, glm::vec3 pos, glm::vec2 size, std::shared_ptr<Sparky::Texture> texture, glm::vec4 active, glm::vec4 inactive)
	:state(INACTIVE), clicked(false), active(active), inactive(inactive)
{
	this->name = name;
	this->ui_entity = Global::ui_e_manager->add_entity<Sparky::Entity>(Global::ui_e_manager);
	this->tcomp = this->ui_entity->add_component<Sparky::TransformComponent>(pos, size, rotation_x(0.0f));
	this->rcomp = this->ui_entity->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,1), inactive, texture);
}

Button::~Button()
{
}

void Button::on_hover()
{
	this->state = ACTIVE;
}

void Button::on_update()
{
	glm::vec4 tex_cord = this->rcomp->get_tex_cord();
	if (this->state == ACTIVE)        tex_cord = this->active;
	else if (this->state == INACTIVE) tex_cord = this->inactive;
	this->rcomp->set_tex_cord(tex_cord);

	this->state   = INACTIVE;
	this->clicked = false;
}

void Button::on_left_click()
{
	this->clicked = true;
}
