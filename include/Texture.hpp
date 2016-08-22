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
    using Texture2dRef = std::shared_ptr<Texture2d>;
  }
}

namespace ci = cinder;

#pragma endregion

namespace Aton
{
  class Texture
  {
  public:
    Texture(const ci::DataSourceRef& dataP);

    const ci::gl::Texture2dRef mTexP;
  };
}