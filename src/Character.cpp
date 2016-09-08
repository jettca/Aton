#include "Character.hpp"
#include "SpriteRenderer.hpp"
#include "Sprite.hpp"
#include "Engine.hpp"
#include "Transform2d.hpp"
#include "Scene.hpp"
#include "Engine.hpp"
#include "Collider2d.hpp"

#include <cinder/Cinder.h>

using namespace Aton;

Character::Character()
  : mSpriteP{ nullptr }
  , mSpeed{ 1 }
{}

void Character::initialize()
{
  auto texP = getObject()->getEngine()->mSpriteManager.getAsset("thing.png");
  auto objectP = getObject()->getScene()->makeObject();
  mSpriteP = std::make_unique<Sprite>(*objectP, texP);
  mSpriteP->mTransformP->position = glm::vec3{ 0, 0, -5 };
  mSpriteP->mTransformP->rotation = glm::pi<float>() / 6;

  // TODO: change this to collision texture
  objectP->addComponent<Collider2d>(texP, mSpriteP->mTransformP);
}

void Character::update(float deltaTime)
{
  auto& keyStates = getObject()->getEngine()->getKeyStates();
  auto& transform = *mSpriteP->mTransformP;

  if (keyStates[Key::KEY_LEFT] & InputFlag::DOWN)
    transform.position.x -= mSpeed * deltaTime;

  if (keyStates[Key::KEY_RIGHT] & InputFlag::DOWN)
    transform.position.x += mSpeed * deltaTime;

  if (keyStates[Key::KEY_UP] & InputFlag::DOWN)
    transform.position.y += mSpeed * deltaTime;

  if (keyStates[Key::KEY_DOWN] & InputFlag::DOWN)
    transform.position.y -= mSpeed * deltaTime;
}

const Sprite* Character::getSprite() const
{
  return mSpriteP.get();
}