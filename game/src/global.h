#pragma once
#include "sparky.h"
#include "util.h"
#include "define.h"

// Button states
enum ButtonState
{
	ACTIVE,
	INACTIVE
};

// Global macros
#define MAX_QUAD_CNT 100
#define ASPECT_RATIO 1.77778 // 16:9
#define WIN_WIDTH  1366
#define WIN_HEIGHT WIN_WIDTH / ASPECT_RATIO
#define ZOOM_WIDTH  520
#define ZOOM_HEIGHT ZOOM_WIDTH / ASPECT_RATIO
#define FPS 60.0f

#define MAX_INVENTORY_SIZE 4

// Scene names
#define GAME      "game"
#define MAIN_MENU "main_menu"

// Global variables
class Global
{
public:
	static std::shared_ptr<Sparky::OrthoCamera>   camera;
	static std::shared_ptr<Sparky::OrthoCamera>   ui_camera;
	static std::shared_ptr<Sparky::QuadRenderer>  renderer;
	static std::shared_ptr<Sparky::UIRenderer>    ui_renderer;
	static std::shared_ptr<Sparky::EntityManager> e_manager;
	static std::shared_ptr<Sparky::EntityManager> ui_e_manager;
	static std::shared_ptr<Sparky::Texture>       white;

public:
	static void init();
	static void clean();
};
