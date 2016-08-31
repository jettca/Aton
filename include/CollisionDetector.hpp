#pragma once

#include <vector>
#include <set>
#include <glm/glm.hpp>
#include "../box2d/b2DynamicTree.h"

namespace Aton
{
  class GameObject;
  class Collider2d;
  class Transform2d;

  class CollisionDetector
  {
  public:
    CollisionDetector();
    void addCollider(Collider2d& collider);
    void removeCollider(Collider2d& collider);
    void updateLists();
    void checkForCollisions();

  private:
    b2DynamicTree mTree;
    std::vector<Transform2d*> mTransforms;
    std::set<Transform2d*> mToRemove;
    std::vector<glm::vec2> mCorners;

    friend class Scene;
  };
}