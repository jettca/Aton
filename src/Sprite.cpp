#include "Sprite.hpp"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

using namespace Aton;

Sprite::Sprite(const ci::DataSourceRef& data)
  : mTexP{ ci::gl::Texture2d::create(ci::loadImage(data)) }
{}

std::shared_ptr<const ci::gl::Texture2d> Sprite::getTexture() const
{
  return mTexP;
}