#pragma once
#include "global.h"

class ErrorPage : public Sparky::Scene
{
public:
	ErrorPage(Sparky::Application* app)
		:app(app)
	{
	}
	~ErrorPage(){}

	void on_update(double dt)
	{
		this->app->clear(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	}

private:
	Sparky::Application* app;
};
