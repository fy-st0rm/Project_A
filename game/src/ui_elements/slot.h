#pragma once
#include "../global.h"


class Slot : public Sparky::UIElement
{
public:
	Slot(const std::string& name, glm::vec3 pos, glm::vec2 size, std::shared_ptr<Sparky::Texture> texture, glm::vec4 active, glm::vec4 inactive);
	~Slot();

public:
	void on_update();

	void select()   { this->state = ACTIVE;   }
	void unselect() { this->state = INACTIVE; }

	void add_item(std::shared_ptr<Sparky::Texture> texture);
	void remove_item();

private:
	void render_item();

private:
	ButtonState state;
	glm::vec4 active, inactive;

	Sparky::Entity* item = nullptr;
	Sparky::TransformComponent* tcomp;
	Sparky::RenderComponent* rcomp;
};
