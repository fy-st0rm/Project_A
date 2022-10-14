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
	std::unordered_map<std::string, std::shared_ptr<Sparky::UIElement>> elements = Global::ui_renderer->get_elements();

	for (int i = 0; i < this->size; i++)
	{
		Slot* element = (Slot*) elements[std::to_string(i)].get();
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

void Inventory::add_new_item(const std::string& name, std::shared_ptr<Sparky::Texture> item_texture)
{
	this->item_buffer[name] = std::make_pair(1, item_texture);
	int slot = this->item_buffer.size() - 1;

	// Getting the slot
	std::unordered_map<std::string, std::shared_ptr<Sparky::UIElement>> elements = Global::ui_renderer->get_elements();
	Slot* element = (Slot*) elements[std::to_string(slot)].get();

	// Adding item to the slot
	element->add_item(item_texture);
}

void Inventory::add_existing_item(const std::string& name)
{
	std::pair<int, std::shared_ptr<Sparky::Texture>> item = this->item_buffer[name];
	item.first++;
	this->item_buffer[name] = item;
}

void Inventory::add_item(const std::string& name, std::shared_ptr<Sparky::Texture> item_texture)
{
	if (this->item_buffer.size() >= this->size) return;

	if (this->item_buffer.find(name) == this->item_buffer.end())
		this->add_new_item(name, item_texture);
	else
		this->add_existing_item(name);
}

std::shared_ptr<Sparky::Texture> Inventory::get_selected_item()
{
	if (this->curr_slot < 0) return nullptr;
	if (this->curr_slot >= this->item_buffer.size()) return nullptr;

	auto it = this->item_buffer.begin();
	std::advance(it, this->curr_slot);
	return it->second.second;
}
