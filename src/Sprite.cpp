#include "Sprite.hpp"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

using namespace Aton;

Sprite::Sprite()
  : Sprite{ ci::gl::Texture2dRef{ nullptr } }
{}

Sprite::Sprite(const ci::DataSourceRef& data)
  : Sprite{ ci::gl::Texture2d::create(ci::loadImage(data)) }
{}

Sprite::Sprite(const ci::gl::Texture2dRef& texP)
  : mTexP{ texP }
  , mPosition{ 0, 0, 1 }
  , mRotation{ glm::pi<float>()/4 }
  , mScale{ 1 }
{}

const Tex2dConstRef& Sprite::getTexture() const
{
  return mTexP;
}