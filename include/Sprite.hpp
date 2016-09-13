#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace Aton
{
  class Transform2d;
  class Texture;
  class SpriteRenderer;
  class Scene;
  class GameObject;

  class Sprite
  {
  public:
    Sprite();
    Sprite(Scene& scene, const std::shared_ptr<Texture>& texP,
      const std::shared_ptr<Texture>& collisionTexP = nullptr,
      float depth = -5);
    ~Sprite();

  public:
    std::shared_ptr<Texture> getTexture() const { return mTexP; }
    void setTexture(std::shared_ptr<Texture> texP) { mTexP = texP; }

    Transform2d* getTransform() const { return mTransformP; }
    GameObject* getObject() const { return mGameObjectP; }

  private:
    GameObject* mGameObjectP;
    Transform2d* mTransformP;
    SpriteRenderer* mRendererP;
    std::shared_ptr<Texture> mTexP;
    std::shared_ptr<Texture> mCollisionTexP;
  };
}