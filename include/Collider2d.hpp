#pragma once

#include "Component.hpp"

#include <memory>
#include <glm/glm.hpp>

namespace Aton
{
  class Transform2d;
  class Texture;

  class Collider2d : public Component
  {
  public:
    Collider2d(const std::shared_ptr<Texture>& textureP,
      Transform2d* transformP);
    ~Collider2d();

    void initialize() override;

    std::shared_ptr<glm::ivec2> collidesWith(const Collider2d& collider);

    std::shared_ptr<Texture> getTexture() const;
    Transform2d* getTransform() const;

  private:
    std::shared_ptr<Texture> mTextureP;
    Transform2d* mTransformP;
  };
}