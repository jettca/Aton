#pragma once

#include <memory>
#include <cinder/Vector.h>

namespace ci
{
  class DataSource;
  using DataSourceRef = std::shared_ptr<DataSource>;

  namespace gl
  {
    class Texture2d;
  }
}

namespace Aton
{
  class Sprite
  {
  public:
    Sprite(const ci::DataSourceRef& data);

    ci::vec2 mPosition;
    float mRotation, mScale;

    std::shared_ptr<const ci::gl::Texture2d> getTexture() const;

  private:

    std::shared_ptr<const ci::gl::Texture2d> mTexP;
  };
}