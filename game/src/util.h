#pragma once
#include "sparky.h"

static glm::mat4 rotation_x(float angle)
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1,0,0));
}

static glm::mat4 rotation_y(float angle)
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0,1,0));
}

static glm::mat4 rotation_z(float angle)
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0,0,1));
}
