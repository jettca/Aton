#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace Aton
{
  class Scene;
  class Component;
  class Engine;

  class GameObject 
  {
  public:
    GameObject(Engine* engineP);

    virtual void update(float deltaTime) = 0;

    ~GameObject();

  protected:
    template<typename C, typename... Args>
    C* addComponent(Args&&... args)
    {
      auto component = std::make_unique<C>(std::forward<Args>(args)...);
      auto raw = component.get();

      assert(dynamic_cast<Component*>(raw) != nullptr);

      component->mGameObjectP = this;
      component->mEngineP = mEngineP;
      component->initialize();

      mComponents.push_back(std::move(component));
      return raw;
    }
    
    void updateComponents(float deltaTime);

  protected:
    Scene* mSceneP;
    Engine* mEngineP;

  private:
    std::vector<std::unique_ptr<Component>> mComponents;
  };
}