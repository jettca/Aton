#include "SpriteRenderer.hpp"
#include "Sprite.hpp"
#include "Transform2d.hpp"
#include "Texture.hpp"

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
  updateTexToSprite();

  for (auto& texData : mTexToSprite)
  {
    // get sprite instance buffer data
    auto spriteData = std::vector<SpriteInstanceData>();
    spriteData.reserve(texData.second.size());
    for (auto sprite : texData.second)
    {
      auto data = SpriteInstanceData{};
      data.position = sprite->getTransform()->position;
      data.rotation = sprite->getTransform()->rotation;
      data.size = sprite->getTransform()->size;
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
    if (texData.first.second)
    {
      texData.first.second->mTexP->bind(0);
      batch->drawInstanced(static_cast<GLsizei>(spriteData.size()));
    }
  }
}

void SpriteRenderer::updateTexToSprite()
{
  // remove deleted sprites
  removeSprites();

  // store changed sprites
  auto spritesChanged = spritemap_t{};
  for (auto& texData : mTexToSprite)
  {
    for (auto sprite : texData.second)
    {
      auto tex = std::make_pair(sprite->getTransform()->position.z,
        sprite->getTexture());
      if (glm::abs(tex.first - texData.first.first) > 1e-4f ||
          tex.second != texData.first.second)
      {
        spritesChanged[tex].push_back(sprite);
        mToRemove.insert(sprite);
      }
    }
  }

  // remove changed sprites
  removeSprites();

  // re-insert changed sprites
  for (auto& texData : spritesChanged)
  {
    mTexToSprite.insert(texData);
  }
}

void SpriteRenderer::removeSprites()
{
  auto texToRemove = std::vector<std::pair<float, TextureRef>>{};
  for (auto& texData : mTexToSprite)
  {
    if (mToRemove.empty())
      break;

    auto sprite_it = mToRemove.begin();
    auto sprites = std::vector<const Sprite*>{};
    sprites.reserve(texData.second.size());
    for (auto sprite : texData.second)
    {
      if ((sprite_it = mToRemove.find(sprite)) == mToRemove.end())
        sprites.push_back(sprite);
      else
        mToRemove.erase(sprite_it);
    }

    if (sprites.size() == 0)
    {
      texToRemove.push_back(texData.first);
      continue;
    }
    texData.second = sprites;
  }

  // erase empty textures
  for (auto& tex : texToRemove)
  {
    mTexToSprite.erase(tex);
  }

  mToRemove.clear();
}

void SpriteRenderer::addSprite(const Sprite& sprite)
{
  mTexToSprite[std::make_pair(sprite.getTransform()->position.z,
    sprite.getTexture())].push_back(&sprite);
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