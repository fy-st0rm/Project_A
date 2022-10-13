#include "global.h"

std::shared_ptr<Sparky::OrthoCamera>   Global::camera = nullptr;
std::shared_ptr<Sparky::QuadRenderer>  Global::renderer = nullptr;
std::shared_ptr<Sparky::UIRenderer>    Global::ui_renderer = nullptr;
std::shared_ptr<Sparky::EntityManager> Global::e_manager = nullptr;
std::shared_ptr<Sparky::EntityManager> Global::ui_e_manager = nullptr;
std::shared_ptr<Sparky::Texture>       Global::white = nullptr;

void Global::init()
{
	// Initializing all the global stuff
	Global::camera       = std::make_shared<Sparky::OrthoCamera>(glm::vec3(0,0,0), 0.0f, ZOOM_WIDTH, 0.0f, ZOOM_HEIGHT, -100.0f, 100.0f);
	Global::renderer     = std::make_shared<Sparky::QuadRenderer>(MAX_QUAD_CNT, Global::camera);
	Global::ui_renderer  = std::make_shared<Sparky::UIRenderer>(MAX_QUAD_CNT, Global::camera);
	Global::e_manager    = std::make_shared<Sparky::EntityManager>();
	Global::ui_e_manager = Global::ui_renderer->get_entity_manager();
	Global::white        = std::make_shared<Sparky::Texture>();
}

void Global::clean()
{
	Global::camera.reset();
	Global::renderer.reset();
	Global::ui_renderer.reset();
	Global::e_manager.reset();
	Global::ui_e_manager.reset();
	Global::white.reset();
}
