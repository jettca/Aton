#pragma once

#include "Character.hpp"
#include "SpriteRenderer.hpp"

using namespace Aton;

Character::Character()
{
  mRendererP = addComponent<SpriteRenderer>();
}

void Character::update(float deltaTime)
{
  updateComponents(deltaTime);
}