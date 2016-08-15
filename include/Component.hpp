#pragma once

namespace Aton
{
  class GameObject;
  class Engine;

  class Component
  {
  protected:
    Component();

  protected:
    GameObject* mObjectP;
    Engine* mEngineP;

    virtual void update(float deltaTime) = 0;

  private:
    friend class GameObject;
  };
}