#pragma once

#include "GameObject.hpp"

namespace Aton
{
  class SpriteRenderer;
  class Sprite;

  class Character : public GameObject
  {
  public:
    Character(Engine* engineP);

    void update(float deltaTime);

    const Sprite* getSprite() const;

  private:
    SpriteRenderer* mRendererP;
  };
}