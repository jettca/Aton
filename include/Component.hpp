#pragma once

namespace Aton
{
  class GameObject;
  class Game;

  class Component
  {
  protected:
    Component() {};

  protected:
    GameObject* getObject() const { return mGameObjectP; }

    virtual void initialize() {};
    virtual void update(float deltaTime) {};

  private:
    GameObject* mGameObjectP;
    friend class GameObject;
  };
}