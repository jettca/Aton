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
    C* addComponent(Args&&... args);

    template<typename C>
    std::vector<C*> getComponent();

    Engine* getEngine() const { return mEngineP; }
    Scene* getScene() const { return mSceneP; }

  private:
    GameObject(Engine* e, Scene* s)
      : mEngineP{ e }
      , mSceneP{ s }
    {}

    void update(float deltaTime)
    {
      for (auto& cP : mComponents)
        cP->update(deltaTime);
    }

    friend class Scene;

  private:
    Engine* const mEngineP;
    Scene* const mSceneP;

    friend class Scene;

  private:
    std::vector<std::unique_ptr<Component>> mComponents;
  };
}

using namespace Aton;

template<typename C, typename... Args>
C* GameObject::addComponent(Args&&... args)
{
  auto component = std::make_unique<C>(std::forward<Args>(args)...);
  auto raw = component.get();

  assert(dynamic_cast<Component*>(raw) != nullptr);

  component->mGameObjectP = this;
  component->initialize();

  mComponents.push_back(std::move(component));
  return raw;
}

template<typename C>
std::vector<C*> GameObject::getComponent()
{
  std::vector<C*> components;
  for (auto& cP : mComponents)
  {
    auto componentP = dynamic_cast<C*>(cP.get());
    if (componentP)
      components.push_back(componentP);
  }
  return components;
}
