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
    GameObject();

    virtual void update(float deltaTime) = 0;

    ~GameObject();

  protected:
    template<typename C, typename... Args>
    C* addComponent(Args... args)
    {
      mComponents.push_back(std::unique_ptr<C>(new C{ args... }));
      return static_cast<C*>(mComponents.back().get());
    }

  protected:
    Scene* mSceneP;

  private:
    std::vector<std::unique_ptr<Component>> mComponents;
  };
}