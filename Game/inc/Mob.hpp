#pragma once

#include <glm/vec2.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/ResourceManager.hpp>

#include <Math/AABB.hpp>

class Mob
{
public:
	//Default constructor
	Mob();

	explicit Mob(const Graphics::Sprite& sprite);

	void update(float deltaTime);

	glm::vec2 move(glm::vec2 aPos, float deltaTime);

	void draw(Graphics::Image& image);

	//void setPosition(const glm::vec2& pos);

	//const glm::vec2& getPosition() const;

	//const Math::AABB getAABB() const;

	void translate(const glm::vec2& t);

private:
	Graphics::Sprite sprite;

protected:
	//glm::vec2 position{ 352.0f, 256.0f };
	glm::vec2 velocity{ 0, 0 };
	float playerSpeed{ 60.0f };
	Math::AABB aabb = { {0, 0, 0}, {32, 32, 0} };
};
