#include "CollisionDetector.hpp"
#include "Collider2d.hpp"

#include "../box2d/b2DynamicTree.h"

using namespace Aton;

CollisionDetector::CollisionDetector()
{}

void CollisionDetector::addCollider(Collider2d& collider)
{
  mTransforms.push_back(collider.getTransform());
}

void CollisionDetector::removeCollider(Collider2d& collider)
{
  mToRemove.insert(collider.getTransform());
}

void CollisionDetector::updateLists()
{
  // remove transforms
  auto oldTransforms = std::move(mTransforms);
  mTransforms.clear();
  mTransforms.reserve(oldTransforms.size() - mToRemove.size());
  for (auto transform : oldTransforms) {
    if (mToRemove.find(transform) == mToRemove.end()) {
      mTransforms.push_back(transform);
    }
  }
  mToRemove.clear();
  mCorners.resize(mTransforms.size() * 4);
}

void CollisionDetector::checkForCollisions()
{
  // TODO: this
  // (reset positions?)
}