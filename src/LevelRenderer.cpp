#include "LevelRenderer.hpp"
#include "AssetManager.hpp"
#include "Sprite.hpp"
#include "SpriteRenderer.hpp"

using namespace Aton;

LevelRenderer::LevelRenderer(Engine* e, const std::shared_ptr<AssetManager<Sprite>>& tileManager,
                             const Sprite* toTrack, glm::vec2 offset)
  : GameObject{ e }
  , mTileManager{ tileManager }
  , mToTrack{ toTrack }
  , mOffset{ offset }
{}

void LevelRenderer::update(float deltaTime)
{
}