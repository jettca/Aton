#include "Engine.h"
#include "CollisionTree.h"
#include "GameObject.h"

using namespace Aton;

Engine::Engine()
  : mObjects{}
  , mCollisionTreeP{ std::make_unique<CollisionTree>() }
{}

void Engine::addObject(const std::shared_ptr<GameObject>& objectP)
{
  mObjects.push_back(objectP);
}