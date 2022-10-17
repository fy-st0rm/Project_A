#pragma once
#include "../global.h"

class Item : public Sparky::Entity
{
public:
	std::string name;

public:
	Item(const std::string& name, std::shared_ptr<Sparky::EntityManager> manager);
	~Item();

	void init (
			glm::vec3 pos, glm::vec2 icon_size, glm::vec2 entity_size,
			std::shared_ptr<Sparky::Texture> icon_texture, glm::vec4 icon_tex_cord,
			std::shared_ptr<Sparky::Texture> entity_texture, glm::vec4 entity_tex_cord
		);

public:
	std::shared_ptr<Sparky::Texture> get_icon_texture()   const { return this->icon_texture; }
	std::shared_ptr<Sparky::Texture> get_entity_texture() const { return this->entity_texture; }

	glm::vec4 get_icon_tex_cord()   const { return this->icon_tex_cord; }
	glm::vec4 get_entity_tex_cord() const { return this->entity_tex_cord; }
	glm::vec2 get_icon_size()   const { return this->icon_size; }
	glm::vec2 get_entity_size() const { return this->entity_size; }

protected:
	std::shared_ptr<Sparky::Texture> icon_texture, entity_texture;
	glm::vec4 icon_tex_cord, entity_tex_cord;
	glm::vec2 icon_size, entity_size;
};
