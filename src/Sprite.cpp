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

Sprite::Sprite(GameObject& obj, const std::shared_ptr<Texture>& texP)
  : mTexP{ texP }
  , mTransformP{ obj.addComponent<Transform2d>() }
  , mRendererP{ obj.getScene()->getRenderer() }
{
  mRendererP->addSprite(*this);
}

Sprite::~Sprite()
{
  mRendererP->removeSprite(*this);
}

Tex2dConstRef Sprite::getTexture() const
{
  return mTexP->mTexP;
}