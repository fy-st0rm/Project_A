#include "slot.h"

Slot::Slot(const std::string& name, glm::vec3 pos, glm::vec2 size, std::shared_ptr<Sparky::Texture> texture, glm::vec4 active, glm::vec4 inactive)
	:state(INACTIVE), active(active), inactive(inactive)
{
	this->name = name;
	this->ui_entity = Global::ui_e_manager->add_entity<Sparky::Entity>(Global::ui_e_manager);
	this->tcomp = this->ui_entity->add_component<Sparky::TransformComponent>(pos, size, rotation_x(0.0f));
	this->rcomp = this->ui_entity->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,1), inactive, texture);
}

Slot::~Slot()
{
}

void Slot::add_item(Item* item)
{
	glm::vec3 slot_pos = this->tcomp->get_pos();
	glm::vec3 pos      = { slot_pos.x + 2, slot_pos.y + 2, 0.0f };
	glm::vec2 size     = { 16.0f, 16.0f };

	// Creating new item from old item data in `ui space`
	this->slot_item = Global::ui_e_manager->add_entity<Item>(item->name, Global::ui_e_manager);
	this->slot_item->init(
			pos, size, glm::vec2(SWORD_W, SWORD_H),
			item->get_icon_texture(), item->get_icon_tex_cord(),
			item->get_entity_texture(), item->get_entity_tex_cord()
		);
}

void Slot::remove_item()
{
	//TODO: Figure out a better way to remove the item entity
	if (this->slot_item == nullptr) return;
	Global::ui_e_manager->remove_entity_by_id(this->slot_item->get_id());
	this->slot_item = nullptr;
}

void Slot::on_update()
{
	glm::vec4 tex_cord = this->rcomp->get_tex_cord();
	if (this->state == ACTIVE)        tex_cord = this->active;
	else if (this->state == INACTIVE) tex_cord = this->inactive;
	this->rcomp->set_tex_cord(tex_cord);
}
