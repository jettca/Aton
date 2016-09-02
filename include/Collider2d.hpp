#pragma once

#include "Component.hpp"

#include <memory>
#include <glm/glm.hpp>
#include <functional>
#include <set>

namespace cinder
{
  namespace gl
  {
    class GlslProg;
    using GlslProgRef = std::shared_ptr<GlslProg>;
  }
}

namespace ci = cinder;

namespace Aton
{
  class Transform2d;
  class Texture;

  class Collider2d : public Component
  {
  public:
    using callback_t = std::function<void(GameObject&)>;

  public:
    Collider2d(const std::shared_ptr<Texture>& textureP,
      Transform2d* transformP, callback_t callback,
      std::set<std::string> layers);
    ~Collider2d();

    void initialize() override;

    std::shared_ptr<Texture> getTexture() const;
    Transform2d* getTransform() const;

  public:
    std::set<std::string> mLayers;

  private:
    bool checkForCollision(const Collider2d& collider);

  private:
    std::shared_ptr<Texture> mTextureP;
    Transform2d* mTransformP;
    callback_t mCallback;

    ci::gl::GlslProgRef mCollisionProg;

    friend class CollisionDetector;
  };
}