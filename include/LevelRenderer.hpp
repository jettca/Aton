#pragma once

#include "GameObject.hpp"

#include <memory>
#include <glm/glm.hpp>

namespace Aton
{
  template<class T>
  class AssetManager;

  class Sprite;

  class LevelRenderer : public GameObject
  {
  public:
    LevelRenderer(Engine* e, const std::shared_ptr<AssetManager<Sprite>>& tileManager,
      const Sprite* toTrack, glm::vec2 offset = glm::vec2{ 0, 0 });

    void update(float deltaTime) override;

  private:
    std::shared_ptr<AssetManager<Sprite>> mTileManager;
    const Sprite* mToTrack;
    glm::vec2 mOffset;
  };
}