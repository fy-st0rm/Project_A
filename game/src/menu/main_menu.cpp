#include "main_menu.h"

MainMenu::MainMenu(Sparky::Application* app)
	:app(app)
{
	this->button_texture = std::make_shared<Sparky::Texture>(BUTTON_IMG);
}

MainMenu::~MainMenu()
{}

void MainMenu::on_entry()
{
	// Start button
	glm::vec4 start_button_active   = { 3.0f / BUTTON_MAX_CNT_X, 0.0f / BUTTON_MAX_CNT_Y, 1.0f / BUTTON_MAX_CNT_X, 1.0f / BUTTON_MAX_CNT_Y };
	glm::vec4 start_button_inactive = { 2.0f / BUTTON_MAX_CNT_X, 0.0f / BUTTON_MAX_CNT_Y, 1.0f / BUTTON_MAX_CNT_X, 1.0f / BUTTON_MAX_CNT_Y };
	this->start_button = (Button*) Global::ui_renderer->add_ui_element<Button>("start", glm::vec3(100, 200, 0), glm::vec2(BUTTON_W, BUTTON_H), this->button_texture, start_button_active, start_button_inactive);

	glm::vec4 quit_button_active   = { 1.0f / BUTTON_MAX_CNT_X, 0.0f / BUTTON_MAX_CNT_Y, 1.0f / BUTTON_MAX_CNT_X, 1.0f / BUTTON_MAX_CNT_Y };
	glm::vec4 quit_button_inactive = { 0.0f / BUTTON_MAX_CNT_X, 0.0f / BUTTON_MAX_CNT_Y, 1.0f / BUTTON_MAX_CNT_X, 1.0f / BUTTON_MAX_CNT_Y };
	this->quit_button = (Button*) Global::ui_renderer->add_ui_element<Button>("quit", glm::vec3(100, 140, 0), glm::vec2(BUTTON_W, BUTTON_H), this->button_texture, quit_button_active, quit_button_inactive);
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

	if (this->start_button->is_clicked())
		app->switch_scene(GAME);
	if (this->quit_button->is_clicked())
		app->destroy();

	Global::ui_renderer->update();
}
