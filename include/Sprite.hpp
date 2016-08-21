#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace cinder
{
  class DataSource;
  using DataSourceRef = std::shared_ptr<DataSource>;

  namespace gl
  {
    class Texture2d;
    using Texture2dRef = std::shared_ptr<Texture2d>;
  }
}

namespace ci = cinder;

namespace Aton
{
  using Tex2dConstRef = std::shared_ptr<const ci::gl::Texture2d>;

  class Sprite
  {
#pragma region constructors
  public:
    Sprite();
    Sprite(const ci::DataSourceRef& data);

  private:
    Sprite(const ci::gl::Texture2dRef& texP);
#pragma endregion

  public:
    glm::vec3 mPosition;
    float mRotation, mScale;

    const Tex2dConstRef& getTexture() const;

  private:
    Tex2dConstRef mTexP;
  };
}