#pragma once
#include "sparky.h"

#define MAX_QUAD_CNT 100
#define WIN_WIDTH  800
#define WIN_HEIGHT 600
#define FPS 60.0f

class Global
{
public:
	static std::shared_ptr<Sparky::OrthoCamera>   camera;
	static std::shared_ptr<Sparky::QuadRenderer>  renderer;
	static std::shared_ptr<Sparky::EntityManager> e_manager;
	static std::shared_ptr<Sparky::Texture>       white;

public:
	static void init();
	static void clean();
};
