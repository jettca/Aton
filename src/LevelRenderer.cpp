#include "LevelRenderer.hpp"
#include "AssetManager.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

using namespace Aton;

LevelRenderer::LevelRenderer(Engine* e,
    const std::shared_ptr<AssetManager<Texture>>& tileManager,
    Camera* cam)
  : GameObject{ e }
  , mTileManager{ tileManager }
  , mCam{ cam }
{}

void LevelRenderer::update(float deltaTime)
{
}