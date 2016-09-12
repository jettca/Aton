#pragma once

#include <memory>
#include <vector>
#include <set>
#include <functional>

#include "Collider2d.hpp"

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
    Collider2d* makeCollidableObject(const std::shared_ptr<Texture>& textureP,
      Collider2d::callback_t callback = [](GameObject&) {},
      std::set<std::string> layers = std::set<std::string>{});

    Camera* getCamera(size_t index = 0);
    Engine* getEngine() { return mEngineP; }
    SpriteRenderer* getRenderer() { return mRendererP.get(); }
    CollisionDetector* getCollisionDetector() { return mCollisionsP.get(); }
    
  private:
    Engine* mEngineP;

    const std::unique_ptr<SpriteRenderer> mRendererP;
    std::unique_ptr<CollisionDetector> mCollisionsP;
    std::vector<Camera*> mCameras;

    std::vector<std::unique_ptr<GameObject>> mObjects;
    std::vector<std::unique_ptr<GameObject>> mNewObjects;

    std::vector<std::unique_ptr<GameObject>> mCollidableObjects;
    std::vector<std::unique_ptr<GameObject>> mNewCollidableObjects;

    friend class Engine;
  };
}