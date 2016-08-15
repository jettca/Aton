#pragma once

#include "GameObject.hpp"

namespace Aton
{
  class SpriteRenderer;

  class Character : public GameObject
  {
  public:
    Character();

    void update(float deltaTime);

  private:
    SpriteRenderer* mRendererP;
  };
}