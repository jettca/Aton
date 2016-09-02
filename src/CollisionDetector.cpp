#include "CollisionDetector.hpp"
#include "Collider2d.hpp"
#include "Transform2d.hpp"

#include <cinder/gl/GlslProg.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

namespace Aton
{
  struct Transform2dData
  {
    glm::vec2 position;
    glm::f64 rotation;
    glm::vec2 size;
  };
}

using namespace Aton;

CollisionDetector::CollisionDetector()
{
  try
  {
    mCornerProg = ci::gl::GlslProg::create(
      ci::gl::GlslProg::Format{}.compute(
        ci::app::loadAsset("shaders/corners.glsl")));
  }
  catch (const std::exception& e)
  {
    std::ofstream out;
    out.open("log.txt");
    out << "Corner shader exception:\n" << e.what() << std::endl;
    throw e;
  }
}

void CollisionDetector::addCollider(Collider2d& collider)
{
  mColliders.push_back(&collider);
  mProxies.push_back(sProxyDefault);
}

void CollisionDetector::removeCollider(Collider2d& collider)
{
  mToRemove.insert(&collider);
}

void CollisionDetector::update()
{
  updateLists();
  updateTransformCorners();
  checkForCollisions();
  updateLastFrameTransforms();
}

void CollisionDetector::updateLists()
{
  if (mToRemove.empty())
    return;

  auto oldColliders = std::move(mColliders);
  auto numOldColliders = oldColliders.size();

  auto oldProxies = std::move(mProxies);
  auto oldLastFrameTransforms = std::move(mLastFrameTransforms);

  mColliders.clear();
  mProxies.clear();
  oldLastFrameTransforms.clear();
  mColliders.reserve(numOldColliders - mToRemove.size());
  mProxies.reserve(mColliders.size());
  mLastFrameTransforms.reserve(mColliders.size());

  for (auto t = int{ 0 }; t < numOldColliders; t++)
  {
    auto& collider = mColliders[t];
    if (mToRemove.find(collider) == mToRemove.end())
    {
      mColliders.push_back(collider);
      mProxies.push_back(oldProxies[t]);
      mLastFrameTransforms.push_back(oldLastFrameTransforms[t]);
    }
  }
  mToRemove.clear();
  mCorners.resize(mColliders.size() * 4);
}

void CollisionDetector::updateTransformCorners()
{
  auto numPoints = mColliders.size() * 4;
  auto cornerSize = sizeof(decltype(mCorners)::value_type);
  auto cornersBuffer = ci::gl::BufferObj::create(
    GL_SHADER_STORAGE_BUFFER, cornerSize * numPoints,
    mCorners.data(),
    GL_STATIC_READ
  );

  auto transformData = std::vector<Transform2dData>{};
  transformData.reserve(mColliders.size());
  for (auto collider : mColliders) {
    auto transform = collider->getTransform();
    auto data = Transform2dData{};
    data.position = glm::vec2(transform->position);
    data.rotation = transform->rotation;
    data.size = transform->size;
    transformData.push_back(data);
  }

  auto transformsBuffer = ci::gl::BufferObj::create(
    GL_SHADER_STORAGE_BUFFER,
    sizeof(decltype(transformData)::value_type) * transformData.size(),
    transformData.data(),
    GL_STATIC_DRAW
  );

  auto points = glm::mat4
  {
    -0.5, -0.5, 0, 0,
    0.5, -0.5, 0, 0,
    -0.5, 0.5, 0, 0,
    0.5, 0.5, 0, 0
  };
  mCornerProg->uniform("points", points);

  mCornerProg->bind();
  ci::gl::bindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, cornersBuffer);
  ci::gl::bindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, transformsBuffer);

  ci::gl::dispatchCompute(numPoints / 128 + 1, 1, 1);

  cornersBuffer->getBufferSubData(0, cornerSize * numPoints,
    mCorners.data());
}

void CollisionDetector::checkForCollisions()
{
  // compute AABBs
  auto numAABBs = mColliders.size();
  for (auto c = int{ 0 }; c < numAABBs; c++)
  {
    auto aabb = b2AABB{};
    aabb.lowerBound = b2Vec2{ std::numeric_limits<float>::infinity(),
                              std::numeric_limits<float>::infinity() };
    aabb.upperBound = -aabb.lowerBound;

    for (auto v = int{ 0 }; v < 4; v++)
    {
      auto& corner = mCorners[4 * c + v];
      if (corner.x < aabb.lowerBound.x)
        aabb.lowerBound.x = corner.x;
      else if (corner.x > aabb.upperBound.x)
        aabb.upperBound.x = corner.x;

      if (corner.y < aabb.lowerBound.y)
        aabb.lowerBound.y = corner.y;
      else if (corner.y > aabb.upperBound.y)
        aabb.upperBound.y = corner.y;
    }

    if (mProxies[c] == sProxyDefault)
    {
      mTree.CreateProxy(aabb, mColliders[c]);
    }
    else
    {
      auto displacement = b2Vec2{ 0.0f, 0.0f };
      if (!mLastFrameTransforms.empty())
      {
        auto& position  = mColliders[c]->getTransform()->position;
        auto deltapos =
          b2Vec2{ position.x - mLastFrameTransforms[c].position.x
                , position.y - mLastFrameTransforms[c].position.y };

        // don't extend aabb if collider "teleports"
        if (deltapos.Length < aabb.GetPerimeter) 
          displacement = deltapos;
      }
      mTree.MoveProxy(mProxies[c], aabb, displacement);
    }
  }

  for (auto c = int{ 0 }; c < numAABBs; c++)
  {
    auto collider = mColliders[c];
    auto lastFrameT = mLastFrameTransforms[c];
    mTree.Query([collider, &lastFrameT](void* data) {
      if (data != collider && 
          collider->checkForCollision(*static_cast<Collider2d*>(data)))
      {
        auto transformP = collider->getTransform();
        transformP->position.x = lastFrameT.position.x;
        transformP->position.y = lastFrameT.position.y;
        transformP->rotation = lastFrameT.rotation;
        transformP->size = lastFrameT.size;

        collider->mCallback(*collider->getObject());
      }
      return true;
    }, mTree.GetFatAABB(mProxies[c]));
  }
}

void CollisionDetector::updateLastFrameTransforms()
{
  auto numColliders = mColliders.size();
  mLastFrameTransforms.resize(numColliders);

  for (auto c = int{ 0 }; c < numColliders; c++)
  {
    auto transformP = mColliders[c]->getTransform();
    mLastFrameTransforms[c].position = glm::vec2{ transformP->position };
    mLastFrameTransforms[c].rotation = transformP->rotation;
    mLastFrameTransforms[c].size = transformP->size;
  }
}