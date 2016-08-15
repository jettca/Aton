#include "GameObject.hpp"
#include "Component.hpp"
#include "Engine.hpp"

using namespace Aton;

GameObject::GameObject(Engine* engineP)
  : mEngineP{ engineP }
{}

GameObject::~GameObject()
{}

void GameObject::updateComponents(float deltaTime)
{
  for (auto& cP : mComponents)
    cP->update(deltaTime);
}