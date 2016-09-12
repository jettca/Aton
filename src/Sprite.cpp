#include "Sprite.hpp"
#include "Transform2d.hpp"
#include "Texture.hpp"
#include "Game.hpp"
#include "SpriteRenderer.hpp"
#include "Scene.hpp"
#include "GameObject.hpp"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

using namespace Aton;

Sprite::Sprite()
  : mTexP{ nullptr }
  , mTransformP{ nullptr }
  , mRendererP{ nullptr }
{}

Sprite::Sprite(Scene& scene, const std::shared_ptr<Texture>& texP,
    const std::shared_ptr<Texture>& collisionTexP, float depth)
  : mTexP{ texP }
  , mCollisionTexP{ collisionTexP }
{
  if (mCollisionTexP)
  {
    auto colliderP = scene.makeCollidableObject(collisionTexP);
    mTransformP = colliderP->getTransform();
    mGameObjectP = colliderP->getObject();
  }
  else
  {
    mGameObjectP = scene.makeObject();
    mTransformP = mGameObjectP->addComponent<Transform2d>();
  }
  mRendererP = scene.getRenderer();
  mTransformP->position.z = depth;
  mRendererP->addSprite(*this);
}

Sprite::~Sprite()
{
  mRendererP->removeSprite(*this);
}
