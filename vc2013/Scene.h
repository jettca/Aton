#pragma once

#include <memory>

namespace Aton
{
  class CollisionTree;

  class Scene
  {
  public:
    Scene();

    std::unique_ptr<CollisionTree> mTreeP;

    ~Scene();
  };
}