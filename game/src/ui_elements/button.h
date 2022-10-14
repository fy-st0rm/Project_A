#include "../global.h"

class Button : public Sparky::UIElement
{
public:
	Button(const std::string& name, glm::vec3 pos, glm::vec2 size, std::shared_ptr<Sparky::Texture> texture, glm::vec4 active, glm::vec4 inactive);
	~Button();

public:
	bool is_clicked() const { return this->clicked; }

public:
	void on_hover();
	void on_update();
	void on_left_click();

private:
	ButtonState state;
	bool clicked;
	glm::vec4 active, inactive;
	Sparky::TransformComponent* tcomp;
	Sparky::RenderComponent* rcomp;
};
