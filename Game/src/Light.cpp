#include <Light.hpp>

using namespace Graphics;

Light::Light() = default;

Light::Light(const glm::vec2& aPos, Graphics::Image& surface)
	: GameObject{ {aPos.x - 64, aPos.y - 64}, this }
	, darkness{ &surface }
{
	arrayOfprtLights[endOfLightArray++] = this;
	circle.setPosition(aPos);
	isLit = true;
}

void Light::setup()
{
	auto lightSprites = ResourceManager::loadSpriteSheet("assets/textures/lightanim.png", 128, 128, 0, 0, BlendMode::AdditiveBlend);
	lightAnim = SpriteAnim{ lightSprites, 4, {} };
}

void Light::update(float deltaTime)
{
	lightAnim.update(deltaTime);
}

void Light::draw()
{
	darkness->drawSprite(lightAnim, position.x, position.y);
}

CircleCollider& Light::getCircle()
{
	return circle;
}

void Light::initializeCollisionGroup(Math::AABB& aObstacle)
{
	//check for AABB collision with all immobile AABB objects on screen
	//add all collisions to an array
	for (int i = 0; i < endOfLightArray; ++i)
	{
		if (arrayOfprtLights[i]->box.getAABB().intersect(aObstacle))
		{
			arrayOfprtLights[i]->arrayOfObstacles[arrayOfprtLights[i]->endOfObstaclesArray] = &aObstacle;
			arrayOfprtLights[i]->endOfObstaclesArray += 1;
		}
	}
}

void Light::litCheck(GameObject* mob) //static
{
	for (int i = 0; i < endOfLightArray; ++i)
	{
		if (arrayOfprtLights[i]->getLitState())
		{
			//check for circle distance with entity
			if (arrayOfprtLights[i]->getCircle().collides(mob->getCircle()))
			{
				//setting the mob to lit activates it
				mob->setLitState(true);
				//check for any AABB collision with the entity and immobile AABB objects within the light's array
				//correct entity position on AABB collision
			}
		}
	}
}

Light* Light::arrayOfprtLights[64]{ nullptr };
int Light::endOfLightArray{ 0 };
