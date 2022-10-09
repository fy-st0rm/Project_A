#pragma once
#include "../global.h"

class Player
{
public:
	Player(glm::vec3 pos, glm::vec2 size);
	~Player();

public:
	void on_event(SparkyEvent event);
	void on_update(double dt);

private:
	void reset_movement();

private:
	std::string id;
	std::unordered_map<std::string, bool> movement;
	float speed = 0.5f;

	Sparky::Entity* entity;
	Sparky::TransformComponent* tcomp;
	Sparky::RenderComponent* rcomp;
	Sparky::AnimationComponent* acomp;
};
