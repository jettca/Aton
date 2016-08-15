#pragma once

#include "Renderer.hpp"

#include <vector>
#include <memory>
#include <chrono>

namespace Aton
{
  class GameObject;
  class CollisionTree;

  class Engine
  {

  public:
    Engine();
    ~Engine();

    void addObject(std::unique_ptr<GameObject> objectP);
    void update();

    Renderer mRenderer;

  private:
    std::vector<std::unique_ptr<GameObject>> mObjects;
    std::unique_ptr<CollisionTree> mCollisionTreeP;

    using mytime_t = std::chrono::high_resolution_clock::time_point;
    std::unique_ptr<mytime_t> lastUpdateTime;

  private:
    static mytime_t clockTime();
    float timeSinceUpdate();
  };
}