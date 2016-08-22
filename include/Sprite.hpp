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

  class Sprite : public GameObject
  {
#pragma region constructors
  public:
    Sprite(Engine* e = nullptr);
    Sprite(Engine* e, const std::shared_ptr<Texture>& texP);
#pragma endregion

    void update(float deltaTime) override;

  public:
    Transform2d* const mTransformP;

    Tex2dConstRef getTexture() const;

  private:
    std::shared_ptr<Texture> mTexP;
  };
}