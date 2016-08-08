#pragma once

#include <vector>
#include <memory>

namespace Aton
{
  class GameObject;
  class CollisionTree;

  class Engine
  {
  public:
    Engine();

    void addObject(const std::shared_ptr<GameObject>& objectP);

  private:
    std::vector<std::shared_ptr<GameObject>> mObjects;
    std::unique_ptr<CollisionTree> mCollisionTreeP;
  };
}