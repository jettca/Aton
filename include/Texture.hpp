#pragma once

#include <memory>

#pragma region forward declarations

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

#pragma endregion

namespace Aton
{
  using Tex2dConstRef = std::shared_ptr<const ci::gl::Texture2d>;
  class Texture
  {
  public:
    Texture(const ci::DataSourceRef& dataP);
    Texture(std::shared_ptr<ci::gl::Texture2d> texP);

    Tex2dConstRef mTexP;
  };
}