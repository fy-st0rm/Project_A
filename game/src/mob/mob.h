#pragma once
#include "../global.h"

// Mob states
#define IDLE "<idle>"
#define WALK "<walk>"
#define HIT  "<hit>"

// Movement directions
#define LEFT  "<left>"
#define RIGHT "<right>"
#define UP    "<up>"
#define DOWN  "<down>"


class Mob
{
protected:
	void init(glm::vec3 pos, glm::vec2 size, float speed, const std::string& img_path);
	void update_movement(double dt);
	void update_animation();
	void reset_movement();
	void load_frame(const std::string& name, float speed, float y, float start, float end, float max_w, float max_h);

protected:
	float speed;
	float angle = 0.0f;
	std::string id;
	std::unordered_map<std::string, bool> movement;
	std::shared_ptr<Sparky::Texture> texture;

	Sparky::Entity* entity;
	Sparky::TransformComponent* tcomp;
	Sparky::RenderComponent* rcomp;
	Sparky::AnimationComponent* acomp;
};
