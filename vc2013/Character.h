#pragma once

#include "GameObject.h"

namespace Aton
{
  class Renderer;

  class Character : public GameObject
  {
  public:
    Character();

  private:
    Renderer* mRendererP;
  };
}