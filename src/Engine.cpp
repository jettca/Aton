#include "Engine.hpp"
#include "Scene.hpp"

using namespace Aton;

Engine::Engine()
  : mSpriteManager{ "textures" }
  , mLastUpdateTimeP{ nullptr }
  , mSceneP{ nullptr }
{}

void Engine::setScene(Scene& scene)
{
  scene.mEngineP = this;
  mSceneP = &scene;
}

Scene* Engine::getScene() const
{
  return mSceneP;
}

void Engine::update()
{
  mSceneP->update(timeSinceUpdate());
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
