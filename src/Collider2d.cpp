#include "Collider2d.hpp"
#include "Texture.hpp"
#include "Transform2d.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include "CollisionDetector.hpp"

#include <cinder/gl/Texture.h>
#include <cinder/gl/Shader.h>
#include <cinder/gl/BufferObj.h>
#include <cinder/app/App.h>

using namespace Aton;

Collider2d::Collider2d(const std::shared_ptr<Texture>& textureP,
  Transform2d* transformP, callback_t callback,
  std::set<std::string> layers)
  : mTextureP{ textureP }
  , mTransformP{ transformP }
  , mCallback{ callback }
  , mLayers{ layers }
{
  try
  {
    mCollisionProg = ci::gl::GlslProg::create(
      ci::gl::GlslProg::Format{}.compute(
        ci::app::loadAsset("shaders/collision2d.glsl")));
  }
  catch (const std::exception& e)
  {
    std::ofstream out;
    out.open("log.txt");
    out << "Collision2D shader exception:\n" << e.what() << std::endl;
    throw e;
  }
}

Collider2d::~Collider2d()
{
  getObject()->getScene()->getCollisionDetector()->removeCollider(*this);
}

void Collider2d::initialize()
{
  getObject()->getScene()->getCollisionDetector()->addCollider(*this);
}

bool Collider2d::checkForCollision(const Collider2d& collider)
{
  bool hasIntersectingLayer = false;
  for (auto l : mLayers)
  {
    if (collider.mLayers.find(l) != collider.mLayers.end())
    {
      hasIntersectingLayer = true;
      break;
    }
  }

  if (mLayers.size() > 0 && !hasIntersectingLayer)
    return false;

  // compute transform between colliders
  auto scale = glm::mat3{};
  scale[0][0] = collider.mTransformP->size.x / mTransformP->size.x;
  scale[1][1] = collider.mTransformP->size.y / mTransformP->size.y;
  scale[2][2] = 1;

  auto angle = collider.mTransformP->rotation - mTransformP->rotation;
  auto sinAngle = glm::sin(angle);
  auto cosAngle = glm::cos(angle);

  auto translate = collider.mTransformP->position - mTransformP->position;
  auto rotateTranslate = glm::mat3{
    cosAngle, sinAngle, translate.x,
    -sinAngle, cosAngle, translate.y,
    0, 0, 1
  };

  auto transform = rotateTranslate * scale;

  // set up shader
  auto collides = std::vector<uint32>{ 0 };
  auto collidesSize = sizeof(decltype(collides)::value_type);
  auto collidesBuffer = ci::gl::BufferObj::create(
    GL_SHADER_STORAGE_BUFFER, collidesSize,
    collides.data(), GL_STATIC_DRAW
  );

  mCollisionProg->bind();

  mTextureP->mTexP->bind(0);
  collider.mTextureP->mTexP->bind(1);
  mCollisionProg->uniform("transform", transform);

  ci::gl::bindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, collidesBuffer);

  auto numThreads = mTextureP->mTexP->getSize() / glm::ivec2{ 32, 32 };
  ci::gl::dispatchCompute(numThreads.x, numThreads.y, 1);

  collidesBuffer->getBufferSubData(0, collidesSize, collides.data());
  return collides[0] == 1;
}

std::shared_ptr<Texture> Collider2d::getTexture() const
{
  return mTextureP;
}

Transform2d* Collider2d::getTransform() const
{
  return mTransformP;
}
