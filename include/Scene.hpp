#pragma once

#include <memory>
#include <vector>

namespace Aton
{
  class CollisionDetector;
  class Camera;
  class GameObject;
  class Engine;
  class SpriteRenderer;

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

  public:

  private:
    Engine* mEngineP;

    const std::unique_ptr<SpriteRenderer> mRendererP;
    std::unique_ptr<CollisionDetector> mCollisionsP;
    std::vector<Camera*> mCameras;
    std::vector<std::unique_ptr<GameObject>> mObjects;
    std::vector<std::unique_ptr<GameObject>> mNewObjects;

    friend class Engine;
  };
}