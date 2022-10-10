#include "player.h"

Player::Player(glm::vec3 pos)
{
	glm::vec2 size = { PLAYER_IMG_W, PLAYER_IMG_H };
	this->init(pos, size, PLAYER_SPEED, PLAYER_IMG);
	this->set_up_frames();
}

Player::~Player()
{
}

void Player::set_up_frames()
{
	this->load_frame(IDLE, ANIME_SPEED, 0.0f, 0.0f, 4.0f, PLAYER_IMG_MAX_CNT_X, PLAYER_IMG_MAX_CNT_Y);
	this->load_frame(WALK, ANIME_SPEED, 0.0f, 4.0f, 8.0f, PLAYER_IMG_MAX_CNT_X, PLAYER_IMG_MAX_CNT_Y);
	this->load_frame(HIT, ANIME_SPEED, 0.0f, 8.0f, 9.0f, PLAYER_IMG_MAX_CNT_X, PLAYER_IMG_MAX_CNT_Y);
	std::vector<std::string> states = { IDLE };
	this->acomp->switch_state(states);
}

void Player::on_event(SparkyEvent event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_w:
				this->movement[UP] = true;
				break;

			case SDLK_a:
				this->movement[LEFT] = true;
				break;

			case SDLK_s:
				this->movement[DOWN] = true;
				break;

			case SDLK_d:
				this->movement[RIGHT] = true;
				break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_w:
				this->movement[UP] = false;
				break;

			case SDLK_a:
				this->movement[LEFT] = false;
				break;

			case SDLK_s:
				this->movement[DOWN] = false;
				break;

			case SDLK_d:
				this->movement[RIGHT] = false;
				break;
		}
	}
}

void Player::on_update(double dt)
{
	this->update_movement(dt);
	this->update_animation();
}
