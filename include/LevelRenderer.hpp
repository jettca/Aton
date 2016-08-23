#pragma once

#include "GameObject.hpp"

#include <memory>
#include <glm/glm.hpp>
#include <functional>

namespace Aton
{
  template<class T>
  class AssetManager;

  class Texture;
  class SpriteRenderer;
  class Camera;

  class LevelRenderer : public GameObject
  {
  public:
    using tiletofile_t = std::function<std::string(glm::ivec2)>;

  public:
    LevelRenderer(Engine* e, const std::shared_ptr<AssetManager<Texture>>& tileManager,
      Camera* cam, glm::vec2 tileSize, glm::ivec2 startTile,
      tiletofile_t tileToFile);

    void update(float deltaTime) override;

  private:
    glm::vec2 tilesPerScreen() const;
    void loadTile(glm::ivec2 coords);

    struct Tile
    {
      std::unique_ptr<SpriteRenderer> renderer;
      glm::ivec2 coords;
      glm::vec2 minCoords, maxCoords;
    };

    std::vector<Tile> mLoadedTiles;
    glm::vec2 mPrevTileCoord;

  private:
    std::shared_ptr<AssetManager<Texture>> mTileManager;
    Camera* mCam;
    glm::vec2 mTileSize;
    glm::ivec2 mStartTile;
    tiletofile_t mTileToFile;
    float mTileDepth;
  };
}