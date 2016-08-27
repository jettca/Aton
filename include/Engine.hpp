#pragma once

#include "AssetManager.hpp"

#include <vector>
#include <memory>
#include <chrono>

namespace Aton
{
  class Texture;
  class Scene;

  class Engine
  {
  public:
    Engine();
    ~Engine();

    void setScene(Scene& scene);
    Scene* getScene() const;
    void update();

    AssetManager<Texture> mSpriteManager;

  private:
    Scene* mSceneP;
    using mytime_t = std::chrono::high_resolution_clock::time_point;
    std::unique_ptr<mytime_t> mLastUpdateTimeP;

  private:
    static mytime_t clockTime();
    float timeSinceUpdate();
  };
}