#pragma once

#include "GameObject.hpp"

#include <memory>
#include <glm/glm.hpp>

namespace Aton
{
  template<class T>
  class AssetManager;

  class Texture;
  class Camera;

  class LevelRenderer : public GameObject
  {
  public:
    LevelRenderer(Engine* e, const std::shared_ptr<AssetManager<Texture>>& tileManager,
      Camera* cam);

    void update(float deltaTime) override;

  private:
    std::shared_ptr<AssetManager<Texture>> mTileManager;
    Camera* mCam;
    glm::vec2 mOffset;
  };
}