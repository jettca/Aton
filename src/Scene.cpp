#include "Scene.hpp"
#include "CollisionDetector.hpp"
#include "SpriteRenderer.hpp"
#include "Camera.hpp"
#include "Transform2d.hpp"

using namespace Aton;

Scene::Scene()
  : mRendererP{ std::make_unique<SpriteRenderer>() }
  , mCollisionsP{ std::make_unique<CollisionDetector>() }
  , mEngineP{ nullptr }
{}

Scene::~Scene()
{}

void Scene::update(float deltaTime)
{
  for (auto& objectP : mCollidableObjects)
  {
    objectP->update(deltaTime);
  }

  mCollisionsP->update();

  for (auto& objectP : mObjects)
  {
    objectP->update(deltaTime);
  }

  mRendererP->draw();

  std::move(mNewObjects.begin(), mNewObjects.end(), std::back_inserter(mObjects));
  mNewObjects.clear();

  std::move(mNewCollidableObjects.begin(), mNewCollidableObjects.end(),
    std::back_inserter(mCollidableObjects));
  mNewCollidableObjects.clear();
}

GameObject* Scene::makeObject()
{
  mNewObjects.push_back(std::unique_ptr<GameObject>(new GameObject(getEngine(), this)));
  return mNewObjects.back().get();
}

Collider2d* Scene::makeCollidableObject(const std::shared_ptr<Texture>& textureP,
  Collider2d::callback_t callback, std::set<std::string> layers)
{
  mNewCollidableObjects.push_back(
    std::unique_ptr<GameObject>(new GameObject(getEngine(), this)));

  return mNewCollidableObjects.back()->addComponent<Collider2d>(textureP,
    callback, layers);
}

void Scene::addCamera(Camera& camera)
{
  mCameras.push_back(&camera);
}

Camera* Scene::getCamera(size_t index)
{
  if (index >= mCameras.size())
    return nullptr;
  return mCameras[index];
}
