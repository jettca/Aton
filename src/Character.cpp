#pragma once

#include "Character.hpp"
#include "SpriteRenderer.hpp"
#include "Sprite.hpp"
#include "Engine.hpp"

#include <cinder/Cinder.h>

using namespace Aton;

Character::Character(Engine* engineP)
  : GameObject(engineP)
{
  mRendererP = addComponent<SpriteRenderer>(
    std::make_unique<Sprite>(mEngineP->mSpriteManager.getAsset(""))
  );
}

void Character::update(float deltaTime)
{
  updateComponents(deltaTime);
}