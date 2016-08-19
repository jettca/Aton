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
  }
}

namespace ci = cinder;

namespace Aton
{
  class Sprite
  {
  public:
    Sprite();

    Sprite(const ci::DataSourceRef& data);

    glm::vec2 mPosition;
    float mRotation, mScale;

    const std::shared_ptr<const ci::gl::Texture2d>& getTexture() const;

  private:

    std::shared_ptr<const ci::gl::Texture2d> mTexP;
  };
}