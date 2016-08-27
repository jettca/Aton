#include "Character.hpp"
#include "SpriteRenderer.hpp"
#include "Sprite.hpp"
#include "Engine.hpp"
#include "Transform2d.hpp"
#include "Scene.hpp"

#include <cinder/Cinder.h>

using namespace Aton;

Character::Character()
  : mSpriteP{ nullptr }
{}

void Character::initialize()
{
  auto texP = getObject()->getEngine()->mSpriteManager.getAsset("thing.png");
  auto objectP = getObject()->getScene()->makeObject();
  mSpriteP = std::make_unique<Sprite>(*objectP, texP);
  mSpriteP->mTransformP->position = glm::vec3{ 0, 0, -5 };
  mSpriteP->mTransformP->rotation = glm::pi<float>() / 6;
}

void Character::update(float deltaTime)
{
}

const Sprite* Character::getSprite() const
{
  return mSpriteP.get();
}