#include "Engine.hpp"
#include "Scene.hpp"

using namespace Aton;

Engine::Engine()
  : mSpriteManager{ "textures" }
  , mLastUpdateTimeP{ nullptr }
  , mSceneP{ nullptr }
  , mCurFrameKeyStates(mNumKeys, InputFlag::UP)
  , mLastFrameKeyStates(mNumKeys)
  , mCurFrameMouseStates(mNumMouseButtons, InputFlag::UP)
  , mLastFrameMouseStates(mNumMouseButtons)
{}

void Engine::update()
{
  // update keys
  // TODO: check if input callbacks are on separate thread, create lock
  mLastFrameKeyStates = mCurFrameKeyStates;

  for (auto k : mKeysPressed)
    mCurFrameKeyStates[k] &= ~InputFlag::PRESSED;
  mKeysPressed.clear();

  for (auto k : mKeysReleased)
    mCurFrameKeyStates[k] &= ~InputFlag::RELEASED;
  mKeysReleased.clear();

  for (auto b : mButtonsPressed)
    mCurFrameMouseStates[b] &= ~InputFlag::PRESSED;
  mButtonsPressed.clear();

  for (auto b : mButtonsReleased)
    mCurFrameMouseStates[b] &= ~InputFlag::RELEASED;
  mButtonsReleased.clear();

  // update scene
  mSceneP->update(timeSinceUpdate());
}

void Engine::setScene(Scene& scene)
{
  scene.mEngineP = this;
  mSceneP = &scene;
}

Scene* Engine::getScene() const
{
  return mSceneP;
}

const std::vector<InputFlag>& Engine::getKeyStates()
{
  return mLastFrameKeyStates;
}

const std::vector<InputFlag>& Engine::getMouseStates()
{
  return mLastFrameMouseStates;
}

void Engine::keyEvent(bool pressed, int key)
{
  InputFlag& f = mCurFrameKeyStates[key];
  if (pressed)
  {
    f &= ~InputFlag::UP;
    f |= InputFlag::PRESSED;
    f |= InputFlag::DOWN;
    mKeysPressed.push_back(key);
  }
  else
  {
    f &= ~InputFlag::DOWN;
    f |= InputFlag::RELEASED;
    f |= InputFlag::UP;
    mKeysReleased.push_back(key);
  }
}

void Engine::mouseEvent(bool pressed, int button)
{
  InputFlag& f = mCurFrameKeyStates[button];
  if (pressed)
  {
    f &= ~InputFlag::UP;
    f |= InputFlag::PRESSED;
    f |= InputFlag::DOWN;
    mButtonsPressed.push_back(button);
  }
  else
  {
    f &= ~InputFlag::DOWN;
    f |= InputFlag::RELEASED;
    f |= InputFlag::UP;
    mButtonsReleased.push_back(button);
  }
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
