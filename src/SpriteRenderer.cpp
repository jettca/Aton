#include "SpriteRenderer.hpp"
#include "Engine.hpp"
#include "Sprite.hpp"

using namespace Aton;

SpriteRenderer::SpriteRenderer(std::unique_ptr<Sprite> spriteP)
  : mSpriteP{ std::move(spriteP) }
{}

void SpriteRenderer::update(float deltaTime)
{
  mEngineP->mRenderer.addSprite(*mSpriteP);
}
const Sprite* SpriteRenderer::getSprite() const
{
  return mSpriteP.get();
}