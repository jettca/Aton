#pragma once

#include "GameObject.hpp"
#include "Texture.hpp"

#include <memory>
#include <glm/glm.hpp>

namespace Aton
{
  using Tex2dConstRef = std::shared_ptr<const ci::gl::Texture2d>;

  class Transform2d;
  class Texture;
  class SpriteRenderer;

  class Sprite
  {
  public:
    Sprite();
    Sprite(GameObject& obj, const std::shared_ptr<Texture>& texP);
    ~Sprite();

  public:
    Transform2d* const mTransformP;

    Tex2dConstRef getTexture() const;

  private:
    SpriteRenderer* mRendererP;
    std::shared_ptr<Texture> mTexP;
  };
}