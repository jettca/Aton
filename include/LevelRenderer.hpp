#pragma once

#include "GameObject.hpp"
#include "Grid.hpp"

#include <memory>
#include <glm/glm.hpp>
#include <functional>


// TODO: unload long gone tiles from memory

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
    std::shared_ptr<AssetManager<Texture>> mTileManager;
    Camera* mCam;
    glm::vec2 mTileSize;
    glm::ivec2 mStartTile;
    tiletofile_t mTileToFile;
    float mTileDepth;

  private:
    struct Tile
    {
      std::unique_ptr<SpriteRenderer> renderer;
      glm::ivec2 coord;
      glm::vec2 minCoord, maxCoord;
    };

    glm::vec2 tilesPerScreen() const;
    std::shared_ptr<Tile> loadTile(glm::ivec2 coord);

    glm::vec3 mPrevCamCoord;
    glm::vec3 mStartCamCoord;
    glm::vec2 mPrevNumTilesPerScreen;
    Grid<std::shared_ptr<Tile>> mGrid;
  };
}