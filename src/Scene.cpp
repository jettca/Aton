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
  for (auto& objectP : mObjects)
  {
    objectP->update(deltaTime);
  }

  std::move(mNewObjects.begin(), mNewObjects.end(), std::back_inserter(mObjects));
  mNewObjects.clear();
  
  mCollisionsP->update();

  mRendererP->draw();
}

GameObject* Scene::makeObject()
{
  mNewObjects.push_back(std::unique_ptr<GameObject>(new GameObject(getEngine(), this)));
  return mNewObjects.back().get();
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
