#pragma once

#include "Character.h"
#include "Renderer.h"

using namespace Aton;

Character::Character()
{
  mRendererP = addComponent<Renderer>();
}

void Character::update(float deltaTime)
{
  updateComponents(deltaTime);
}