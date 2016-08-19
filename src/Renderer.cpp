#include "Renderer.hpp"
#include "Sprite.hpp"

using namespace Aton;

Renderer::Renderer()
  : mSprites{}
  , mRectMesh{}
{
  createRectMesh();

  mSpriteLayout.append(ci::geom::Attrib::CUSTOM_0,
    sizeof(SpriteInstanceData),
    offsetof(SpriteInstanceData, position), 1);
  mSpriteLayout.append(ci::geom::Attrib::CUSTOM_1,
    sizeof(SpriteInstanceData),
    offsetof(SpriteInstanceData, rotation), 1);
  mSpriteLayout.append(ci::geom::Attrib::CUSTOM_2,
    sizeof(SpriteInstanceData),
    offsetof(SpriteInstanceData, scale), 1);

  mSpriteMapping[ci::geom::Attrib::CUSTOM_0] = "aPosition";
  mSpriteMapping[ci::geom::Attrib::CUSTOM_1] = "aRotation";
  mSpriteMapping[ci::geom::Attrib::CUSTOM_2] = "aScale";
}

void Renderer::draw()
{
  auto spriteVbo = ci::gl::Vbo::create(GL_ARRAY_BUFFER,
    mSpriteData.size() * sizeof(SpriteInstanceData),
    mSpriteData.data(), GL_DYNAMIC_DRAW);

  auto rectVboMesh = ci::gl::VboMesh::create(mRectMesh);
  rectVboMesh->appendVbo(mSpriteLayout, spriteVbo);

  // TODO: create shader, update mSpriteData, pass texture data
  auto batch = ci::gl::Batch::create(rectVboMesh, nullptr, mSpriteMapping);
  batch->drawInstanced(mSpriteData.size());
}

void Renderer::addSprite(const Sprite& sprite)
{
  mSprites.push_back(&sprite);
  auto data = SpriteInstanceData{};

  data.position = sprite.mPosition;
  data.rotation = sprite.mRotation;
  data.scale = sprite.mScale;

  mSpriteData.push_back(std::move(data));
}

void Renderer::createRectMesh()
{
  mRectMesh.appendPosition(glm::vec2{ -0.5, -0.5 });
  mRectMesh.appendPosition(glm::vec2{ 0.5, -0.5 });
  mRectMesh.appendPosition(glm::vec2{ -0.5, 0.5 });
  mRectMesh.appendPosition(glm::vec2{ 0.5, 0.5 });

  mRectMesh.appendTexCoord(glm::vec2{ 0, 0 });
  mRectMesh.appendTexCoord(glm::vec2{ 1, 0 });
  mRectMesh.appendTexCoord(glm::vec2{ 0, 1 });
  mRectMesh.appendTexCoord(glm::vec2{ 1, 1 });

  mRectMesh.appendTriangle(0, 1, 2);
  mRectMesh.appendTriangle(3, 2, 1);
}