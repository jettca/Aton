#include "SpriteRenderer.hpp"
#include "Sprite.hpp"
#include "Transform2d.hpp"

#include <cinder/app/App.h>
#include <fstream>

namespace Aton
{
  struct SpriteInstanceData
  {
    glm::vec3 position;
    glm::f64 rotation;
    glm::vec2 size;
  };
}

using namespace Aton;

SpriteRenderer::SpriteRenderer()
{
  createRectMesh();

  mSpriteLayout.append(ci::geom::Attrib::CUSTOM_0,
    3,
    sizeof(SpriteInstanceData),
    offsetof(SpriteInstanceData, position),
    1);

  mSpriteLayout.append(ci::geom::Attrib::CUSTOM_1,
    1,
    sizeof(SpriteInstanceData),
    offsetof(SpriteInstanceData, rotation),
    1);

  mSpriteLayout.append(ci::geom::Attrib::CUSTOM_2,
    2,
    sizeof(SpriteInstanceData),
    offsetof(SpriteInstanceData, size),
    1);

  mSpriteMapping[ci::geom::Attrib::CUSTOM_0] = "aPosition";
  mSpriteMapping[ci::geom::Attrib::CUSTOM_1] = "aRotation";
  mSpriteMapping[ci::geom::Attrib::CUSTOM_2] = "aSize";

  try
  {
    mSpriteShaderP = ci::gl::GlslProg::create(
      ci::app::loadAsset("shaders/sprites.vert"),
      ci::app::loadAsset("shaders/sprites.frag"));

    mSpriteShaderP->uniform("Texture0", 0);
  }
  catch (const std::exception& e)
  {
    std::ofstream out;
    out.open("log.txt");
    out << "Sprite shader exception:\n" << e.what() << std::endl;
    throw e;
  }
}

void SpriteRenderer::draw()
{
  auto texToRemove = std::vector<std::pair<float, Tex2dConstRef>>{};
  for (auto& texData : mTexToSprite)
  {
    // remove removed sprites
    {
      auto sprites = std::vector<const Sprite*>{};
      sprites.reserve(texData.second.size());
      for (auto sprite : texData.second)
        if (mToRemove.find(sprite) == mToRemove.end())
          sprites.push_back(sprite);

      if (sprites.size() == 0)
      {
        texToRemove.push_back(texData.first);
        continue;
      }
      texData.second = sprites;
    }

    // get sprite instance buffer data
    auto spriteData = std::vector<SpriteInstanceData>();
    spriteData.reserve(texData.second.size());
    for (auto sprite : texData.second)
    {
      auto data = SpriteInstanceData{};
      data.position = sprite->mTransformP->position;
      data.rotation = sprite->mTransformP->rotation;
      data.size = sprite->mTransformP->size;
      spriteData.push_back(data);
    }
    
    // create VBO
    auto spriteVbo = ci::gl::Vbo::create(GL_ARRAY_BUFFER,
      spriteData.size() * sizeof(SpriteInstanceData),
      spriteData.data(), GL_STATIC_DRAW);

    auto rectVboMesh = ci::gl::VboMesh::create(mRectMesh);
    rectVboMesh->appendVbo(mSpriteLayout, spriteVbo);

    auto batch = ci::gl::Batch::create(rectVboMesh, mSpriteShaderP, mSpriteMapping);

    // draw sprites
    texData.first.second->bind(0);
    batch->drawInstanced(static_cast<GLsizei>(spriteData.size()));
  }
  for (auto& tex : texToRemove)
  {
    mTexToSprite.erase(tex);
  }

  mToRemove.clear();
}

void SpriteRenderer::addSprite(const Sprite& sprite)
{
  mTexToSprite[std::make_pair(sprite.mTransformP->position.z,
    sprite.getTexture()->mTexP)].push_back(&sprite);
}

void SpriteRenderer::removeSprite(const Sprite& sprite)
{
  mToRemove.insert(&sprite);
}

void SpriteRenderer::createRectMesh()
{
  mRectMesh.appendPosition(glm::vec3{ -0.5, -0.5, 0.0 });
  mRectMesh.appendPosition(glm::vec3{ 0.5, -0.5, 0.0 });
  mRectMesh.appendPosition(glm::vec3{ -0.5, 0.5, 0.0 });
  mRectMesh.appendPosition(glm::vec3{ 0.5, 0.5, 0.0 });

  mRectMesh.appendTexCoord(glm::vec2{ 0, 0 });
  mRectMesh.appendTexCoord(glm::vec2{ 1, 0 });
  mRectMesh.appendTexCoord(glm::vec2{ 0, 1 });
  mRectMesh.appendTexCoord(glm::vec2{ 1, 1 });

  mRectMesh.appendTriangle(0, 1, 2);
  mRectMesh.appendTriangle(3, 2, 1);
}