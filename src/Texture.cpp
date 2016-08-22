#include "Texture.hpp"

#include <cinder/gl/Texture.h>

using namespace Aton;

Texture::Texture(const ci::DataSourceRef& dataP)
  : mTexP{ ci::gl::Texture2d::create(ci::loadImage(dataP)) }
{}