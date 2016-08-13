#pragma once

#include "Component.hpp"

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