#include "LevelRenderer.hpp"
#include "AssetManager.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "SpriteRenderer.hpp"
#include "Sprite.hpp"
#include "Transform2d.hpp"
#include "Engine.hpp"

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
  , mTileDepth{ 1.0f }
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

  auto zproj = (vp * glm::vec4{ 0, 0, mTileDepth, 0 }).z;
  auto minWorld = invvp * glm::vec4{ -1, -1, zproj, 1 };
  auto maxWorld = invvp * glm::vec4{ 1, 1, zproj, 1 };

  auto spanWorld = maxWorld - minWorld;

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
  catch (std::exception& e)
  {
    return nullptr;
  }


  tileP->coord = std::move(coord);

  auto shiftedCoords = glm::vec2{ mStartTile - tileP->coord } * mTileSize;
  tileP->minCoord = shiftedCoords * mTileSize - mTileSize / 2.0f;
  tileP->maxCoord = shiftedCoords * mTileSize + mTileSize / 2.0f;

  auto& spritePos = tileP->renderer->getSprite()->mTransformP->position;
  spritePos.x = tileP->minCoord.x;
  spritePos.y = tileP->minCoord.y;
  spritePos.z = mTileDepth;

  return tileP;
}