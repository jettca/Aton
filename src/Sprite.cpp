#include "Sprite.hpp"
#include "Transform2d.hpp"
#include "Texture.hpp"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

using namespace Aton;

Sprite::Sprite(Engine* e)
  : Sprite{ e, nullptr }
{}

Sprite::Sprite(Engine* e, const std::shared_ptr<Texture>& texP)
  : GameObject{ e }
  , mTexP{ texP }
  , mTransformP{ addComponent<Transform2d>() }
{
  mTransformP->position = glm::vec3{ 0, 0, 5 };
  mTransformP->rotation = glm::pi<float>() / 4;
}

void Sprite::update(float deltaTime)
{}

Tex2dConstRef Sprite::getTexture() const
{
  return mTexP->mTexP;
}