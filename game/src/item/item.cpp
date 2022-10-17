#include "item.h"

Item::Item(const std::string& name, std::shared_ptr<Sparky::EntityManager> manager)
	:name(name), Sparky::Entity(manager)
{
}

Item::~Item()
{
}

void Item::init(
			glm::vec3 pos, glm::vec2 icon_size, glm::vec2 entity_size,
			std::shared_ptr<Sparky::Texture> icon_texture, glm::vec4 icon_tex_cord,
			std::shared_ptr<Sparky::Texture> entity_texture, glm::vec4 entity_tex_cord
		)
{
	// Assigning the texture
	this->icon_size       = icon_size;
	this->entity_size     = entity_size;
	this->icon_texture	  = icon_texture;
	this->entity_texture  = entity_texture;
	this->icon_tex_cord   = icon_tex_cord;
	this->entity_tex_cord = entity_tex_cord;

	// Adding the components
	this->add_component<Sparky::TransformComponent>(pos, icon_size, rotation_x(0.0f));
	this->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,1), this->icon_tex_cord, this->icon_texture);
	this->add_component<Sparky::BoxColliderComponent>(glm::vec4(pos.x, pos.y, icon_size.x, icon_size.y), true);
	this->add_component<Sparky::TagComponent>(ITEM_TAG);
}
