#include "LevelRenderer.hpp"
#include "AssetManager.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "Transform2d.hpp"
#include "Engine.hpp"
#include "Scene.hpp"

#include <cinder/app/Platform.h>

using namespace Aton;

LevelRenderer::LevelRenderer(const std::shared_ptr<AssetManager<Texture>>& tileManager,
      Camera* cam, glm::vec2 tileSize, glm::ivec2 startTile,
      tiletofile_t tileToFile)
  : mTileManager{ tileManager }
  , mCam{ cam }
  , mTileSize{ std::move(tileSize) }
  , mStartTile{ std::move(startTile) }
  , mTileToFile{ std::move(tileToFile) }
  , mTileDepth{ -6.0f }
  , mPrevCamCoord{ cam->getPosition() }
  , mStartCamCoord{ mPrevCamCoord }
{}

void LevelRenderer::initialize()
{
  mPrevNumTilesPerScreen = tilesPerScreen();
  mGridP = std::make_unique<Grid<std::shared_ptr<Tile>>>(
    mPrevNumTilesPerScreen * mTileSize,
    mTileSize, nullptr,
    mPrevNumTilesPerScreen * mTileSize / 2.0f);
}

void LevelRenderer::update(float deltaTime)
{
  auto numTiles = tilesPerScreen();
  auto camCoord = mCam->getPosition();

  if (numTiles != mPrevNumTilesPerScreen)
  {
    mGridP->resize(numTiles * mTileSize);
  }

  mGridP->shift(glm::vec2{ camCoord - mPrevCamCoord });

  for (auto w = size_t{ 0 }; w < mGridP->width(); w++) {
    for (auto h = size_t{ 0 }; h < mGridP->height(); h++)
    {
      if ((*mGridP)[w][h] == nullptr)
      {
        auto gridCoord = mGridP->getPosFromIndex(w, h);
        auto worldCoord = gridCoord + glm::vec2{ camCoord - mStartCamCoord };
        auto tile = loadTile(glm::ivec2{ glm::floor(worldCoord / mTileSize) }
                             + mStartTile);
        (*mGridP)[w][h] = tile;
      }
    }
  }

  mPrevNumTilesPerScreen = numTiles;
  mPrevCamCoord = camCoord;
}

glm::vec2 LevelRenderer::tilesPerScreen() const
{
  auto& cam = getObject()->getScene()->getCamera()->getCameraPersp();
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
    auto objectP = getObject()->getScene()->makeObject();
    tileP->sprite = std::make_unique<Sprite>(*objectP,
      mTileManager->getAsset(mTileToFile(coord)), mTileDepth);
  }
  catch (ci::app::AssetLoadExc&)
  {
    return nullptr;
  }

  tileP->coord = std::move(coord);

  auto shiftedCoords = glm::vec2{ tileP->coord - mStartTile } * mTileSize;
  tileP->minCoord = shiftedCoords - mTileSize / 2.0f;
  tileP->maxCoord = shiftedCoords + mTileSize / 2.0f;

  auto spriteTransformP = tileP->sprite->mTransformP;
  spriteTransformP->position.x = shiftedCoords.x;
  spriteTransformP->position.y = shiftedCoords.y;
  spriteTransformP->size = mTileSize;

  return tileP;
}