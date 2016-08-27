#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Component.hpp"

namespace Aton
{
  class Scene;
  class Component;
  class Engine;

  class GameObject 
  {
  public:
    ~GameObject() {};

    template<typename C, typename... Args>
    C* addComponent(Args&&... args)
    {
      auto component = std::make_unique<C>(std::forward<Args>(args)...);
      auto raw = component.get();
      
      assert(dynamic_cast<Component*>(raw) != nullptr);

      component->mGameObjectP = this;
      component->initialize();

      mComponents.push_back(std::move(component));
      return raw;
    }

    Engine* getEngine() const { return mEngineP; }
    Scene* getScene() const { return mSceneP; }
    
  private:
    void update(float deltaTime)
    {
      for (auto& cP : mComponents)
        cP->update(deltaTime);
    }

    friend class Scene;

  private:
    GameObject(Engine* e, Scene* s)
      : mEngineP{ e }
      , mSceneP{ s }
    {};

    Engine* const mEngineP;
    Scene* const mSceneP;

    friend class Scene;

  private:
    std::vector<std::unique_ptr<Component>> mComponents;
  };
}
