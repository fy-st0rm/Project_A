#include "item.h"

enum SwordType
{
	IRON,
	GOLD
};

class Sword
{
public:
	Sword(glm::vec3 pos, int sword_type);
	~Sword();

private:
	Item* item;
	std::shared_ptr<Sparky::Texture> icon_texture, entity_texture;
	glm::vec4 icon_tex_cord, entity_tex_cord;
};
