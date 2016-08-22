#include "Engine.hpp"
#include "CollisionTree.hpp"
#include "GameObject.hpp"

using namespace Aton;

Engine::Engine()
  : mRenderer{}
  , mSpriteManager{ "textures" }
  , mObjects{}
  , mCollisionTreeP{ std::make_unique<CollisionTree>() }
  , mLastUpdateTimeP{ nullptr }
{}

Engine::~Engine()
{}

void Engine::addObject(std::unique_ptr<GameObject> objectP)
{
  mObjects.push_back(std::move(objectP));
}

void Engine::update()
{
  auto deltaTime{ timeSinceUpdate() };
  for (auto& objectP : mObjects)
  {
    objectP->update(deltaTime);
  }

  mRenderer.draw();
}

Engine::mytime_t Engine::clockTime()
{
  return std::chrono::high_resolution_clock::now();
}

float Engine::timeSinceUpdate()
{
  using namespace std::chrono;

  auto curTime = clockTime();
  if (!mLastUpdateTimeP)
    mLastUpdateTimeP.reset(new mytime_t{ curTime });

  auto d = duration<float>{ curTime - *mLastUpdateTimeP };

  *mLastUpdateTimeP = curTime;

  return d.count();
}