#include "Sprite.hpp"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

using namespace Aton;

Sprite::Sprite()
  : mTexP{ nullptr }
  , mPosition{ 0, 0 }
  , mRotation{ 0 }
  , mScale{ 1 }
{}

Sprite::Sprite(const ci::DataSourceRef& data)
  : mTexP{ ci::gl::Texture2d::create(ci::loadImage(data)) }
  , mPosition{ 0, 0 }
  , mRotation{ 0 }
  , mScale{ 1 }
{}

std::shared_ptr<const ci::gl::Texture2d> Sprite::getTexture() const
{
  return mTexP;
}