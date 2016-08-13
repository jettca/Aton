#include "GameObject.hpp"
#include "Component.hpp"

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