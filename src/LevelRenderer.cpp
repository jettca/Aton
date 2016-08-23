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
  , mPrevTileCoord{ -1.0f, -1.0f }
{}

void LevelRenderer::update(float deltaTime)
{
  auto numTiles = tilesPerScreen();
  auto curTile = glm::vec2{ mCam->getPosition() } / mTileSize
    + glm::vec2{ mStartTile };

  auto minCoord = glm::ivec2{ curTile - numTiles / 2.0f };
  auto maxCoord = glm::ivec2{ curTile + numTiles / 2.0f };

  for (int x = minCoord.x; x <= maxCoord.x; x++) {
    for (int y = minCoord.y; y <= maxCoord.y; y++)
    {
    }
  }

  mPrevTileCoord = curTile;
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

void LevelRenderer::loadTile(glm::ivec2 coords)
{
  auto tile = Tile{};

  tile.renderer = makeComponent<SpriteRenderer>(
    std::make_unique<Sprite>(mEngineP,
      mTileManager->getAsset(mTileToFile(coords))));

  tile.coords = std::move(coords);

  auto shiftedCoords = glm::vec2{ mStartTile - tile.coords } * mTileSize;
  tile.minCoords = shiftedCoords - mTileSize / 2.0f;
  tile.maxCoords = shiftedCoords + mTileSize / 2.0f;

  auto& spritePos = tile.renderer->getSprite()->mTransformP->position;
  spritePos.x = tile.minCoords.x;
  spritePos.y = tile.minCoords.y;
  spritePos.z = mTileDepth;

  mLoadedTiles.push_back(std::move(tile));
}