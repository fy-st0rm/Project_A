#include "main_menu.h"

MainMenu::MainMenu(Sparky::Application* app, Client* client)
	:app(app), client(client)
{
	this->button_texture = std::make_shared<Sparky::Texture>(BUTTON_IMG);
}

MainMenu::~MainMenu()
{}

void MainMenu::on_entry()
{
	int cent_x = ZOOM_WIDTH / 2 - BUTTON_W / 2;
	// Host button
	glm::vec4 host_button_active   = { 1.0f / BUTTON_MAX_CNT_X, 2.0f / BUTTON_MAX_CNT_Y, 1.0f / BUTTON_MAX_CNT_X, 1.0f / BUTTON_MAX_CNT_Y };
	glm::vec4 host_button_inactive = { 0.0f / BUTTON_MAX_CNT_X, 2.0f / BUTTON_MAX_CNT_Y, 1.0f / BUTTON_MAX_CNT_X, 1.0f / BUTTON_MAX_CNT_Y };
	this->host_button = (Button*) Global::ui_renderer->add_ui_element<Button>(
			"host", glm::vec3(cent_x, 200, 0), glm::vec2(BUTTON_W, BUTTON_H), 
			this->button_texture, host_button_active, host_button_inactive
		);

	// Join button
	glm::vec4 join_button_active   = { 1.0f / BUTTON_MAX_CNT_X, 1.0f / BUTTON_MAX_CNT_Y, 1.0f / BUTTON_MAX_CNT_X, 1.0f / BUTTON_MAX_CNT_Y };
	glm::vec4 join_button_inactive = { 0.0f / BUTTON_MAX_CNT_X, 1.0f / BUTTON_MAX_CNT_Y, 1.0f / BUTTON_MAX_CNT_X, 1.0f / BUTTON_MAX_CNT_Y };
	this->join_button = (Button*) Global::ui_renderer->add_ui_element<Button>(
			"join", glm::vec3(cent_x, 150, 0), glm::vec2(BUTTON_W, BUTTON_H), 
			this->button_texture, join_button_active, join_button_inactive
		);

	// Quit button
	glm::vec4 quit_button_active   = { 1.0f / BUTTON_MAX_CNT_X, 0.0f / BUTTON_MAX_CNT_Y, 1.0f / BUTTON_MAX_CNT_X, 1.0f / BUTTON_MAX_CNT_Y };
	glm::vec4 quit_button_inactive = { 0.0f / BUTTON_MAX_CNT_X, 0.0f / BUTTON_MAX_CNT_Y, 1.0f / BUTTON_MAX_CNT_X, 1.0f / BUTTON_MAX_CNT_Y };
	this->quit_button = (Button*) Global::ui_renderer->add_ui_element<Button>(
			"quit", glm::vec3(cent_x, 100, 0), glm::vec2(BUTTON_W, BUTTON_H), 
			this->button_texture, quit_button_active, quit_button_inactive
		);
}

void MainMenu::on_exit()
{
	Global::ui_renderer->clear_buffer();
}

void MainMenu::on_event(SparkyEvent event)
{
	Global::ui_renderer->handle_event(event);
}

void MainMenu::on_update(double dt)
{
	this->app->clear(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	if (this->host_button->is_clicked())
	{
		// TODO: Send hosting game payload
	}
	if (this->join_button->is_clicked())
	{
		// TODO: Send joining game payload
	}
	if (this->quit_button->is_clicked())
	{
		app->destroy();
	}

	Global::ui_renderer->update();
}
