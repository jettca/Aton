#pragma once

#include "GameObject.hpp"
#include "Texture.hpp"

#include <memory>
#include <glm/glm.hpp>

namespace Aton
{
  class Transform2d;
  class Texture;
  class SpriteRenderer;

  class Sprite
  {
  public:
    Sprite();
    Sprite(GameObject& obj, const std::shared_ptr<Texture>& texP, float depth = -5);
    ~Sprite();

  public:
    Transform2d* const mTransformP;

    std::shared_ptr<Texture> getTexture() const;

  private:
    SpriteRenderer* mRendererP;
    std::shared_ptr<Texture> mTexP;
  };
}