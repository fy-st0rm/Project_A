#pragma once
#include "../global.h"
#include "../item/item.h"


class Slot : public Sparky::UIElement
{
public:
	Slot(const std::string& name, glm::vec3 pos, glm::vec2 size, std::shared_ptr<Sparky::Texture> texture, glm::vec4 active, glm::vec4 inactive);
	~Slot();

public:
	void on_update();

	void select()   { this->state = ACTIVE;   }
	void unselect() { this->state = INACTIVE; }

	void add_item(Item* item);
	void remove_item();

public:
	Item* get_item() { return this->slot_item; }

private:
	void render_item();

private:
	ButtonState state;
	glm::vec4 active, inactive;

	Item* slot_item = nullptr;
	Sparky::TransformComponent* tcomp;
	Sparky::RenderComponent* rcomp;
};
