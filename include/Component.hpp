#pragma once

namespace Aton
{
  class GameObject;
  class Game;

  class Component
  {
  public:
    GameObject* getObject() const { return mGameObjectP; }

  protected:
    Component() {};

    virtual void initialize() {};
    virtual void update(float deltaTime) {};

  private:
    GameObject* mGameObjectP;
    friend class GameObject;
  };
}