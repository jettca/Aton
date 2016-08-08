#pragma once

namespace Aton
{
  class GameObject;

  class Component
  {
  protected:
    Component();

  protected:
    GameObject* mObjectP;
    virtual void update(float deltaTime) = 0;

  private:
    friend class GameObject;
  };
}