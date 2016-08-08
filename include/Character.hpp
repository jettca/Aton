#pragma once

#include "GameObject.h"

namespace Aton
{
  class Renderer;

  class Character : public GameObject
  {
  public:
    Character();

    void update(float deltaTime);

  private:
    Renderer* mRendererP;
  };
}