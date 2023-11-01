#include <Light.hpp>

using namespace Graphics;

Light::Light() = default;

Light::Light(const glm::vec2& aPos, Graphics::Image& surface)
	: GameObject{ {aPos.x - 64, aPos.y - 64}, this }
	, darkness{ &surface }
{
	arrayOfptrLights[endOfLightArray++] = this;
	circle.setPosition(aPos);
	isLit = true;
}

void Light::setup()
{
	auto lightSprites = ResourceManager::loadSpriteSheet("assets/textures/lightanim.png", 128, 128, 0, 0, BlendMode::AdditiveBlend);
	lightAnim = SpriteAnim{ lightSprites, 4, {} };
}

void Light::update(float deltaTime, GameObject& player)
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

void Light::initializeCollisionGroup(Math::AABB aObstacle) //static
{
	//check for AABB collision with all immobile AABB objects on screen
	//add all collisions to an array
	for (int i = 0; i < endOfLightArray; ++i)
	{
		arrayOfptrLights[i]->updateColliders();
		if (arrayOfptrLights[i]->box.getAABB().intersect(aObstacle))
		{
			Light* ptrLight = arrayOfptrLights[i];
			ptrLight->arrayOfObstacles[ptrLight->endOfObstaclesArray++] = aObstacle;
		}
	}
}

void Light::litCheck(GameObject* mob) //static
{
	for (int i = 0; i < endOfLightArray; ++i)
	{
		Light* ptrLight = arrayOfptrLights[i];
		if (ptrLight->getLitState())
		{
			//check for circle distance with entity
			if (ptrLight->getCircle().collides(mob->getCircle()))
			{
				//setting the mob to lit activates it
				mob->setLitState(true);
				//check for any AABB collision with the entity and immobile AABB objects within the light's array
				for (int j = 0; j < ptrLight->endOfObstaclesArray; ++j)
				{
					//correct entity position on AABB collision
					Math::AABB aabb = ptrLight->arrayOfObstacles[j];
					if (mob->getBox().getAABB().intersect(aabb))
					{
						mob->handleCollision(aabb);
					}
				}
			}
		}
	}
}

void Light::updateColliders()
{
	box.setPosition(position);
}

Light* Light::arrayOfptrLights[64]{ nullptr };
int Light::endOfLightArray{ 0 };
