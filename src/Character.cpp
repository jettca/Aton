#include "Character.hpp"
#include "SpriteRenderer.hpp"
#include "Sprite.hpp"
#include "Engine.hpp"
#include "Transform2d.hpp"

#include <cinder/Cinder.h>

using namespace Aton;

Character::Character(Engine* engineP)
  : GameObject(engineP)
  , mRendererP{ addComponent<SpriteRenderer>(
      std::make_unique<Sprite>(mEngineP,
        mEngineP->mSpriteManager.getAsset("thing.png"))) }
  , mTransformP{ mRendererP->getSprite()->mTransformP }
{
  mTransformP->position = glm::vec3{ 0, 0, -5 };
  mTransformP->rotation = glm::pi<float>() / 6;
}

void Character::update(float deltaTime)
{
  updateComponents(deltaTime);
}

const Sprite* Character::getSprite() const
{
  return mRendererP->getSprite();
}