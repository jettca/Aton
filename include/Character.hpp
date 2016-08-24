#pragma once

#include "GameObject.hpp"

namespace Aton
{
  class SpriteRenderer;
  class Sprite;
  class Transform2d;

  class Character : public GameObject
  {
  public:
    Character(Engine* engineP);

    void update(float deltaTime);

    const Sprite* getSprite() const;

  private:
    SpriteRenderer* mRendererP;
    Transform2d* mTransformP;
  };
}