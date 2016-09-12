#include "CharacterControl.hpp"
#include "SpriteRenderer.hpp"
#include "Sprite.hpp"
#include "Engine.hpp"
#include "Transform2d.hpp"
#include "Scene.hpp"
#include "Engine.hpp"
#include "Collider2d.hpp"
#include "GameObject.hpp"

#include <cinder/Cinder.h>

using namespace Aton;

CharacterControl::CharacterControl(Sprite* sprite)
  : mSpriteP{ sprite }
  , mSpeed{ 1 }
{}

void CharacterControl::initialize()
{}

void CharacterControl::update(float deltaTime)
{
  auto& keyStates = getObject()->getEngine()->getKeyStates();
  auto& transform = *mSpriteP->getTransform();

  if (keyStates[Key::KEY_LEFT] & InputFlag::DOWN)
    transform.position.x -= mSpeed * deltaTime;

  if (keyStates[Key::KEY_RIGHT] & InputFlag::DOWN)
    transform.position.x += mSpeed * deltaTime;

  if (keyStates[Key::KEY_UP] & InputFlag::DOWN)
    transform.position.y += mSpeed * deltaTime;

  if (keyStates[Key::KEY_DOWN] & InputFlag::DOWN)
    transform.position.y -= mSpeed * deltaTime;
}
