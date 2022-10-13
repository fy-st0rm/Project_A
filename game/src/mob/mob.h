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
public:
	glm::vec3 get_pos() const   { return this->tcomp->get_pos(); }
	void set_pos(glm::vec3 pos) { this->tcomp->set_pos(pos); }

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

// Function to make camera follow a mob
static void camera_follow_mob(std::shared_ptr<Sparky::OrthoCamera> camera, std::shared_ptr<Mob> mob)
{
	glm::vec3 cam_pos = camera->get_position();
	glm::vec3 mob_pos = mob->get_pos();

	cam_pos.x += (mob_pos.x - cam_pos.x - ZOOM_WIDTH  / 2) / 20;
	cam_pos.y += (mob_pos.y - cam_pos.y - ZOOM_HEIGHT / 2) / 20;

	camera->set_position(cam_pos);
	mob->set_pos(mob_pos);
}
