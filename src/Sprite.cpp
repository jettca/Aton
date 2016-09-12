#include "Sprite.hpp"
#include "Transform2d.hpp"
#include "Texture.hpp"
#include "Game.hpp"
#include "SpriteRenderer.hpp"
#include "Scene.hpp"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

using namespace Aton;

Sprite::Sprite()
  : mTexP{ nullptr }
  , mTransformP{ nullptr }
  , mRendererP{ nullptr }
{}

Sprite::Sprite(GameObject& obj, const std::shared_ptr<Texture>& texP, float depth)
  : mTexP{ texP }
  , mTransformP{ obj.addComponent<Transform2d>() }
  , mRendererP{ obj.getScene()->getRenderer() }
{
  mTransformP->position.z = depth;
  mRendererP->addSprite(*this);
}

Sprite::~Sprite()
{
  mRendererP->removeSprite(*this);
}

std::shared_ptr<Texture> Sprite::getTexture() const
{
  return mTexP;
}