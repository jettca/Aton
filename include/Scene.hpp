#pragma once

#include <memory>
#include <vector>
#include <set>
#include <cinder/gl/GlslProg.h>

namespace Aton
{
  class CollisionDetector;
  class Camera;
  class GameObject;
  class Engine;
  class SpriteRenderer;
  class Transform2d;

  class Scene
  {
  public:
    Scene();
    ~Scene();

    void update(float deltaTime);

    void addCamera(Camera& camera);
    GameObject* makeObject();

    Camera* getCamera(size_t index = 0);
    Engine* getEngine() { return mEngineP; }
    SpriteRenderer* getRenderer() { return mRendererP.get(); }
    CollisionDetector* getCollisionDetector() { return mCollisionsP.get(); }
    
  private:
    void updateTransformAABBs();
    ci::gl::GlslProgRef mCornerProg;

  private:
    Engine* mEngineP;

    const std::unique_ptr<SpriteRenderer> mRendererP;
    std::unique_ptr<CollisionDetector> mCollisionsP;
    std::vector<Camera*> mCameras;
    std::vector<std::unique_ptr<GameObject>> mObjects;
    std::vector<std::unique_ptr<GameObject>> mNewObjects;

    std::set<Transform2d*> mTransforms;

    friend class Engine;
  };
}