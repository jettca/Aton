#pragma once

#include "Component.h"

namespace Aton
{
  class Renderer : public Component
  {
  public:
    void update(float deltaTime);

  private:
    Renderer();

    friend GameObject;
  };
}