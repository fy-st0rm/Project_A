#pragma once
#include "../global.h"
#include "../ui_elements/slot.h"
#include "../item/item.h"

class Inventory
{
public:
	Inventory(int size);
	~Inventory();

public:
	void handle_event(SparkyEvent event);
	void update();

	void add_item(const std::string& name, Item* item);
	Item* get_selected_item();

private:
	void generate_ui();
	void unselect_all();

	void add_new_item(const std::string& name, Item* item);
	void add_existing_item(const std::string& name);

private:
	int size;
	int curr_slot = -1;
	std::unordered_map<std::string, int> item_buffer;

	std::shared_ptr<Sparky::Texture> invent_texture;
	glm::vec4 unselected = { 0.0f / INVENT_MAX_CNT_X, 0.0f, 1.0f / INVENT_MAX_CNT_X, 1.0f };
	glm::vec4 selected   = { 1.0f / INVENT_MAX_CNT_X, 0.0f, 1.0f / INVENT_MAX_CNT_X, 1.0f };
};
