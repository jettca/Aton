#pragma once

#include "Character.hpp"
#include "Renderer.hpp"

using namespace Aton;

Character::Character()
{
  mRendererP = addComponent<Renderer>();
}

void Character::update(float deltaTime)
{
  updateComponents(deltaTime);
}