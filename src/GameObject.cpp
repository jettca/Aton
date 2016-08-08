#include "GameObject.h"
#include "Component.h"

using namespace Aton;

GameObject::GameObject()
{}

GameObject::~GameObject()
{}

void GameObject::updateComponents(float deltaTime)
{
  for (auto& cP : mComponents)
    cP->update(deltaTime);
}