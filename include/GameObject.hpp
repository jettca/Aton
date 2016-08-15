#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace Aton
{
  class Scene;
  class Component;

  class GameObject 
  {
  public:
    GameObject(Engine* engineP);

    virtual void update(float deltaTime) = 0;

    ~GameObject();

  protected:
    template<typename C, typename... Args>
    C* addComponent(Args... args)
    {
      auto component = std::unique_ptr<C>(new C{ args... });
      auto componentBase = std::dynamic_pointer_cast<Component>(component);
      assert(componentBase != nullptr);

      componentBase->mGameObjectP = this;
      componentBase->mEngineP = mEngineP;

      mComponents.push_back(component);
      return component.get();
    }
    
    void updateComponents(float deltaTime);

  protected:
    Scene* mSceneP;
    Engine* mEngineP;

  private:
    std::vector<std::unique_ptr<Component>> mComponents;
  };
}