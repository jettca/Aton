#pragma once

#include "../box2d/b2DynamicTree.h"

#include <vector>
#include <set>
#include <memory>
#include <glm/glm.hpp>

namespace cinder
{
  namespace gl
  {
    class GlslProg;
    using GlslProgRef = std::shared_ptr<GlslProg>;
  }
}

namespace ci = cinder;

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
    void update();

  private:
    void updateLists();
    void updateTransformCorners();
    void checkForCollisions();
    void updateLastFrameTransforms();
    ci::gl::GlslProgRef mCornerProg;

  private:
    b2DynamicTree mTree;
    std::vector<Collider2d*> mColliders;
    std::vector<int32> mProxies;
    std::set<Collider2d*> mToRemove;
    std::vector<glm::vec2> mCorners;

    struct Transform2dData
    {
      glm::vec2 position;
      glm::f64 rotation;
      glm::vec2 size;
    };

    std::vector<Transform2dData> mLastFrameTransforms;

    static const int32 sProxyDefault = -1;
  };
}