#include "Collider2d.hpp"
#include "Texture.hpp"
#include "Transform2d.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include "CollisionDetector.hpp"

using namespace Aton;

Collider2d::Collider2d(const std::shared_ptr<Texture>& textureP,
  Transform2d* transformP)
  : mTextureP{ textureP }
  , mTransformP{ transformP }
{}

Collider2d::~Collider2d()
{
  getObject()->getScene()->getCollisionDetector()->removeCollider(*this);
}

void Collider2d::initialize()
{
  getObject()->getScene()->getCollisionDetector()->addCollider(*this);
}

std::shared_ptr<glm::ivec2> Collider2d::collidesWith(const Collider2d& collider)
{
  return nullptr;
}

std::shared_ptr<Texture> Collider2d::getTexture() const
{
  return mTextureP;
}

Transform2d* Collider2d::getTransform() const
{
  return mTransformP;
}
