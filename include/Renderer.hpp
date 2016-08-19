#pragma once

#include <vector>
#include <cinder/gl/gl.h>
#include <glm/glm.hpp>

namespace Aton
{
  class Sprite;

  class Renderer
  {
  public:
    Renderer();
    void draw();
    void addSprite(const Sprite& sprite);

  private:
    void createRectMesh();

  private:
    struct SpriteInstanceData
    {
      glm::vec2 position;
      float rotation, scale;
    };

    std::vector<const Sprite*> mSprites;
    std::vector<SpriteInstanceData> mSpriteData;
    ci::geom::BufferLayout mSpriteLayout;
    ci::gl::Batch::AttributeMapping mSpriteMapping;
    ci::TriMesh mRectMesh;
  };
}