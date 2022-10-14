#pragma once
#include "../mob.h"
#include "../../inventory/inventory.h"

class Player : public Mob
{
public:
	Player(glm::vec3 pos);
	~Player();

public:
	void on_event(SparkyEvent event);
	void on_update(double dt);
	void set_up_frames();

private:
	void calc_item_pos(Sparky::TransformComponent* item_tcomp);
	void create_curr_item();

private:
	std::shared_ptr<Inventory> inventory;

	float item_radius = 30.0f;
	float item_angle  = 0.0f;
	Sparky::Entity* curr_item = nullptr;

	//TODO: temp texture
	std::shared_ptr<Sparky::Texture> item_texture;
};
