#pragma once

#include "Component.hpp"

#include <glm/glm.hpp>

namespace Aton
{
  class Transform2d : public Component
  {
  public:
    Transform2d();

    void update(float deltaTime = 0) override;

    glm::vec3 position;
    glm::f64 rotation;
    glm::vec2 size;
  };
}