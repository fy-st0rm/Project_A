#pragma once
#include "../mob.h"

// Player sprite informations
#define PLAYER_IMG "assets/player.png"
#define PLAYER_IMG_MAX_CNT_X 9.0f
#define PLAYER_IMG_MAX_CNT_Y 1.0f
#define PLAYER_IMG_W 16.0f
#define PLAYER_IMG_H 28.0f
#define PLAYER_SPEED 0.1f
#define ANIME_SPEED  19.0f


class Player : public Mob
{
public:
	Player(glm::vec3 pos);
	~Player();

public:
	void on_event(SparkyEvent event);
	void on_update(double dt);
	void set_up_frames();
};
