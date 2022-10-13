#include "player.h"

Player::Player(glm::vec3 pos)
{
	glm::vec2 size = { PLAYER_IMG_W, PLAYER_IMG_H };
	this->init(pos, size, PLAYER_SPEED, PLAYER_IMG);
	this->set_up_frames();

	this->item_texture = std::make_shared<Sparky::Texture>("assets/sword.png");
	this->item = Global::e_manager->add_entity<Sparky::Entity>(Global::e_manager);
	this->item_tcomp = this->item->add_component<Sparky::TransformComponent>(pos, glm::vec2(25, 12), rotation_x(this->item_angle));
	this->item->add_component<Sparky::RenderComponent>(glm::vec4(1, 1, 1, 1), glm::vec4(0,0,1,1), this->item_texture);
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

void Player::calc_item_pos(Sparky::TransformComponent* item_tcomp)
{
	glm::vec2 m_pos = Sparky::Util::get_mouse_pos(Global::camera);

	// Calculating the center
	glm::vec3 player_pos  = this->tcomp->get_pos();
	glm::vec2 player_size = this->tcomp->get_size();
	glm::vec2 center = { (player_pos.x + (player_pos.x + player_size.x)) / 2, (player_pos.y + (player_pos.y + player_size.y)) / 2 };

	// Calculating the perpendicular and base of the triangle
	float P = m_pos.y - center.y;
	float B = m_pos.x - center.x;

	// Making them positive
	if (P < 0.0f) P *= -1;
	if (B < 0.0f) B *= -1;

	// Calculating the angle ( arc tan(P/B) )
	this->item_angle = glm::degrees(atan2(P, B));

	// Converting the angle based on the quadrant it lies on
	if (m_pos.x < center.x && m_pos.y < center.y)
		this->item_angle = 180 + this->item_angle;
	else if (m_pos.x > center.x && m_pos.y < center.y)
		this->item_angle = 360 - this->item_angle;
	else if (m_pos.x < center.x)
		this->item_angle = 180 - this->item_angle;

	// Setting up the items rotation
	item_tcomp->set_rotation(rotation_neg_z(this->item_angle));

	// Calculating item position
	glm::vec3 pos = {0,0,0};
	glm::vec2 size = item_tcomp->get_size();
	pos.x = center.x + this->item_radius * cos(glm::radians(this->item_angle)) - size.x / 2;
	pos.y = center.y + this->item_radius * sin(glm::radians(this->item_angle)) - size.y / 2;
	item_tcomp->set_pos(pos);
}

void Player::on_update(double dt)
{
	this->calc_item_pos(this->item_tcomp);
	this->update_movement(dt);
	this->update_animation();
}
