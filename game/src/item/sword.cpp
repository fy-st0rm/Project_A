#include "sword.h"

Sword::Sword(glm::vec3 pos, int sword_type)
{
	this->icon_texture = std::make_shared<Sparky::Texture>(SWORD_ICON_IMG);
	this->entity_texture = std::make_shared<Sparky::Texture>(SWORD_IMG);

	if (sword_type == IRON)
	{
		this->icon_tex_cord = { 0.0f / SWORD_ICON_MAX_CNT_X, 0.0f / SWORD_ICON_MAX_CNT_Y, 1.0f / SWORD_ICON_MAX_CNT_X, 1.0f / SWORD_ICON_MAX_CNT_Y };
		this->entity_tex_cord = { 0.0f / SWORD_MAX_CNT_X, 0.0f / SWORD_MAX_CNT_Y, 1.0f / SWORD_MAX_CNT_X, 1.0f / SWORD_MAX_CNT_Y };
	}
	else if (sword_type == GOLD)
	{
		this->icon_tex_cord = { 1.0f / SWORD_ICON_MAX_CNT_X, 0.0f / SWORD_ICON_MAX_CNT_Y, 1.0f / SWORD_ICON_MAX_CNT_X, 1.0f / SWORD_ICON_MAX_CNT_Y };
		this->entity_tex_cord = { 1.0f / SWORD_MAX_CNT_X, 0.0f / SWORD_MAX_CNT_Y, 1.0f / SWORD_MAX_CNT_X, 1.0f / SWORD_MAX_CNT_Y };
	}

	this->item = Global::e_manager->add_entity<Item>(SWORD, Global::e_manager);
	this->item->init(
			pos, glm::vec2(SWORD_ICON_W, SWORD_ICON_H), glm::vec2(SWORD_W, SWORD_H),
			this->icon_texture, this->icon_tex_cord,
			this->entity_texture, this->entity_tex_cord
		);
}

Sword::~Sword()
{
}
