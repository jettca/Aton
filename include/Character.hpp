#pragma once

#include "GameObject.hpp"

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