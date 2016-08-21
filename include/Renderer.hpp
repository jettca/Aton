#pragma once

#include <vector>
#include <cinder/gl/gl.h>
#include <glm/glm.hpp>

namespace cinder
{
  namespace gl
  {
    class Texture2d;
    using Texture2dRef = std::shared_ptr<Texture2d>;
  }
}

namespace Aton
{
  class Sprite;

  using Tex2dConstRef = std::shared_ptr<const ci::gl::Texture2d>;

  class Renderer
  {
  public:
    Renderer();
    void draw();
    void addSprite(const Sprite& sprite);

  private:
    void createRectMesh();

  private:
    std::map<Tex2dConstRef, std::vector<const Sprite*>> mTexToSprite;

    ci::geom::BufferLayout mSpriteLayout;
    ci::gl::Batch::AttributeMapping mSpriteMapping;
    ci::TriMesh mRectMesh;
    ci::gl::GlslProgRef mSpriteShaderP;
  };
}