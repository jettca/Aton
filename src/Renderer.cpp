#include "Renderer.hpp"
#include "Sprite.hpp"
#include "Transform2d.hpp"

#include <cinder/app/App.h>
#include <fstream>

namespace Aton
{
  struct SpriteInstanceData
  {
    glm::vec3 position;
    float rotation, scale;
  };
}

using namespace Aton;

Renderer::Renderer()
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
    1,
    sizeof(SpriteInstanceData),
    offsetof(SpriteInstanceData, scale),
    1);

  mSpriteMapping[ci::geom::Attrib::CUSTOM_0] = "aPosition";
  mSpriteMapping[ci::geom::Attrib::CUSTOM_1] = "aRotation";
  mSpriteMapping[ci::geom::Attrib::CUSTOM_2] = "aScale";

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
    out << "Shader exception: " << e.what() << std::endl;
  }

}

void Renderer::draw()
{
  for (auto& texData : mTexToSprite)
  {
    // remove removed sprites
    {
      auto sprites = std::vector<const Sprite*>{};
      sprites.reserve(texData.second.size());
      for (auto sprite : texData.second)
        if (toRemove.find(sprite) == toRemove.end())
          sprites.push_back(sprite);
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
      data.scale = sprite->mTransformP->scale;
      spriteData.push_back(data);
    }
    
    // create VBO
    auto spriteVbo = ci::gl::Vbo::create(GL_ARRAY_BUFFER,
      spriteData.size() * sizeof(SpriteInstanceData),
      spriteData.data(), GL_DYNAMIC_DRAW);

    auto rectVboMesh = ci::gl::VboMesh::create(mRectMesh);
    rectVboMesh->appendVbo(mSpriteLayout, spriteVbo);

    auto batch = ci::gl::Batch::create(rectVboMesh, mSpriteShaderP, mSpriteMapping);

    // draw sprites
    texData.first->bind(0);

    {
      ci::gl::ScopedModelMatrix smm;
      batch->drawInstanced(spriteData.size());
    }
  }

  toRemove.clear();
}

void Renderer::addSprite(const Sprite& sprite)
{
  mTexToSprite[sprite.getTexture()].push_back(&sprite);
}

void Renderer::removeSprite(const Sprite& sprite)
{
  toRemove.insert(&sprite);
}

void Renderer::createRectMesh()
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