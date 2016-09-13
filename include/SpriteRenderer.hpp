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
  class Texture;

  class SpriteRenderer
  {
  private:
    using TextureRef = std::shared_ptr<Texture>;
    using spritemap_t =
      std::map<std::pair<float, TextureRef>, std::vector<const Sprite*>>;
  public:
    SpriteRenderer();
    void draw();
    void addSprite(const Sprite& sprite);
    void removeSprite(const Sprite& sprite);

  private:
    void updateTexToSprite();
    void removeSprites();
    void createRectMesh();

  private:
    spritemap_t mTexToSprite;
    std::set<const Sprite*> mToRemove;

    ci::geom::BufferLayout mSpriteLayout;
    ci::gl::Batch::AttributeMapping mSpriteMapping;
    ci::TriMesh mRectMesh;
    ci::gl::GlslProgRef mSpriteShaderP;
  };
}