#pragma once

#include <glm/vec2.hpp>
#include <Graphics/Sprite.hpp>

class Mob
{
public:
	//Default constructor
	Mob();

	explicit Mob(const glm::vec2& pos, const Graphics::Sprite& sprite);

	virtual void update(float deltaTime);

	void draw(Graphics::Image& image);

	void setPosition(const glm::vec2& pos);

	const glm::vec2& getPosition() const;

private:
//	glm::vec2 position{ 352.0f, 256.0f };
	Graphics::Sprite sprite;
//	float playerSpeed{ 60.0f };

protected:
	glm::vec2 position{ 352.0f, 256.0f };
	float playerSpeed{ 60.0f };
};
