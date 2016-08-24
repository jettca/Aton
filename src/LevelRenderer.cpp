#include "LevelRenderer.hpp"
#include "AssetManager.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "SpriteRenderer.hpp"
#include "Sprite.hpp"
#include "Transform2d.hpp"
#include "Engine.hpp"

#include <cinder/app/Platform.h>

using namespace Aton;

LevelRenderer::LevelRenderer(Engine* e,
      const std::shared_ptr<AssetManager<Texture>>& tileManager,
      Camera* cam, glm::vec2 tileSize, glm::ivec2 startTile,
      tiletofile_t tileToFile)
  : GameObject{ e }
  , mTileManager{ tileManager }
  , mCam{ cam }
  , mTileSize{ std::move(tileSize) }
  , mStartTile{ std::move(startTile) }
  , mTileToFile{ std::move(tileToFile) }
  , mTileDepth{ -6.0f }
  , mPrevCamCoord{ cam->getPosition() }
  , mStartCamCoord{ mPrevCamCoord }
  , mPrevNumTilesPerScreen{ tilesPerScreen() }
  , mGrid{ mPrevNumTilesPerScreen, mTileSize, nullptr, mPrevNumTilesPerScreen / 2.0f }
{}

void LevelRenderer::update(float deltaTime)
{
  auto numTiles = tilesPerScreen();
  auto camCoord = mCam->getPosition();

  if (numTiles != mPrevNumTilesPerScreen)
  {
    mGrid.resize(numTiles);
  }

  mGrid.shift(glm::vec2{ camCoord - mPrevCamCoord });

  for (auto w = size_t{ 0 }; w < mGrid.width(); w++) {
    for (auto h = size_t{ 0 }; h < mGrid.height(); h++)
    {
      if (mGrid[w][h] == nullptr)
      {
        auto gridCoord = mGrid.getPosFromIndex(w, h);
        auto worldCoord = gridCoord + glm::vec2{ camCoord - mStartCamCoord };
        auto tile = loadTile(glm::ivec2{ glm::floor(worldCoord / mTileSize) }
                             + mStartTile);
        mGrid[w][h] = tile;
      }
    }
  }

  mPrevNumTilesPerScreen = numTiles;
  mPrevCamCoord = camCoord;
}

glm::vec2 LevelRenderer::tilesPerScreen() const
{
  auto& cam = mEngineP->getCamera()->getCameraPersp();
  auto vp = cam.getProjectionMatrix() * cam.getViewMatrix();
  auto invvp = glm::inverse(vp);

  auto clipSpaceTile = vp * glm::vec4{ glm::vec2{ cam.getEyePoint() }, mTileDepth, 1 };
  auto zproj = clipSpaceTile.z / clipSpaceTile.w;
  auto minWorld = invvp * glm::vec4{ -1, -1, zproj, 1 };
  minWorld /= minWorld.w;
  auto maxWorld = invvp * glm::vec4{ 1, 1, zproj, 1 };
  maxWorld /= maxWorld.w;

  auto spanWorld = glm::abs(maxWorld - minWorld);

  return glm::vec2{ spanWorld } / mTileSize;
}

std::shared_ptr<LevelRenderer::Tile> LevelRenderer::loadTile(glm::ivec2 coord)
{
  auto tileP = std::make_shared<Tile>();

  try
  {
    tileP->renderer = makeComponent<SpriteRenderer>(
      std::make_unique<Sprite>(mEngineP,
        mTileManager->getAsset(mTileToFile(coord))));
  }
  catch (ci::app::AssetLoadExc&)
  {
    return nullptr;
  }


  tileP->coord = std::move(coord);

  auto shiftedCoords = glm::vec2{ tileP->coord - mStartTile } * mTileSize;
  tileP->minCoord = shiftedCoords - mTileSize / 2.0f;
  tileP->maxCoord = shiftedCoords + mTileSize / 2.0f;

  auto spriteTransformP = tileP->renderer->getSprite()->mTransformP;
  spriteTransformP->position.x = shiftedCoords.x;
  spriteTransformP->position.y = shiftedCoords.y;
  spriteTransformP->position.z = mTileDepth;
  spriteTransformP->size = mTileSize;

  return tileP;
}