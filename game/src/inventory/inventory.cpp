#include "inventory.h"

Inventory::Inventory(int size)
	:size(size)
{
	this->invent_texture = std::make_shared<Sparky::Texture>(INVENT_IMG);
	this->generate_ui();
}

Inventory::~Inventory()
{
}

void Inventory::generate_ui()
{
	float x = (Global::camera->get_width() / 2.0f) - ((this->size * INVENT_W) / 2.0f);
	float y = 50.0f;

	for (int i = 0; i < this->size; i++)
	{
		glm::vec3 pos   = { x, y, 0.0f };
		glm::vec2 size  = { INVENT_W, INVENT_H };

		Slot* slot = (Slot*) Global::ui_renderer->add_ui_element<Slot>(std::to_string(i), pos, size, this->invent_texture, this->selected, this->unselected);
		//if (i == 0)
		//	slot->select();

		x += INVENT_W;
	}
}

void Inventory::unselect_all()
{
	for (int i = 0; i < this->size; i++)
	{
		Slot* element = (Slot*) Global::ui_renderer->get_ui_element(std::to_string(i));
		element->unselect();
	}
}

void Inventory::handle_event(SparkyEvent event)
{
	Global::ui_renderer->handle_event(event);
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		switch (event.button.button)
		{
			case SDL_BUTTON_LEFT:
			{
				Slot* focused_ui = (Slot*)Global::ui_renderer->get_focused_ui();
				if (focused_ui)
				{
					this->unselect_all();
					focused_ui->select();
					this->curr_slot = std::stoi(focused_ui->name);
				}
				break;
			}
		}
	}
}

void Inventory::update()
{
	Global::ui_renderer->update();
}

void Inventory::add_new_item(const std::string& name, Item* item)
{
	this->item_buffer[name] = 1;
	int slot = this->item_buffer.size() - 1;

	// Getting the slot
	Slot* element = (Slot*) Global::ui_renderer->get_ui_element(std::to_string(slot));

	// Adding item to the slot
	element->add_item(item);
}

void Inventory::add_existing_item(const std::string& name)
{
	this->item_buffer[name]++;
}

void Inventory::add_item(const std::string& name, Item* item)
{
	if (this->item_buffer.size() >= this->size) return;

	if (this->item_buffer.find(name) == this->item_buffer.end())
		this->add_new_item(name, item);
	else
		this->add_existing_item(name);

	// Removing the item from entity manager
	Global::e_manager->remove_entity_by_id(item->get_id());
}

Item* Inventory::get_selected_item()
{
	if (this->curr_slot < 0) return nullptr;
	if (this->curr_slot >= this->item_buffer.size()) return nullptr;

	// Returning the item from slot
	Slot* element = (Slot*) Global::ui_renderer->get_ui_element(std::to_string(this->curr_slot));
	return element->get_item();
}
