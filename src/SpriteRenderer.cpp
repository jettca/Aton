#include "SpriteRenderer.hpp"
#include "Engine.hpp"
#include "Sprite.hpp"

using namespace Aton;

SpriteRenderer::SpriteRenderer(std::unique_ptr<Sprite> spriteP)
  : mSpriteP{ std::move(spriteP) }
{}

void SpriteRenderer::initialize()
{
  mEngineP->mRenderer.addSprite(*mSpriteP);
}

SpriteRenderer::~SpriteRenderer()
{
  mEngineP->mRenderer.removeSprite(*mSpriteP);
}

void SpriteRenderer::update(float deltaTime)
{}

const Sprite* SpriteRenderer::getSprite() const
{
  return mSpriteP.get();
}