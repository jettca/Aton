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
    GameObject* mGameObjectP;
    Engine* mEngineP;

    virtual void initialize() {};
    virtual void update(float deltaTime) = 0;

  private:
    friend class GameObject;
  };
}