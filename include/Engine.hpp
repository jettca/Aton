#pragma once

#include "AssetManager.hpp"

namespace Aton
{
  class Scene;
  class Texture;

  class Engine
  {
  public:
    Engine();

    AssetManager<Texture> mSpriteManager;

    void update();

    void setScene(Scene& scene);
    Scene* getScene() const;

  private:
    Scene* mSceneP;
    using mytime_t = std::chrono::high_resolution_clock::time_point;
    std::unique_ptr<mytime_t> mLastUpdateTimeP;

  private:
    static mytime_t clockTime();
    float timeSinceUpdate();
  };
}