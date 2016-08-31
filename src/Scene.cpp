#include "Scene.hpp"
#include "CollisionDetector.hpp"
#include "SpriteRenderer.hpp"
#include "Camera.hpp"
#include "Transform2d.hpp"

#include <cinder/app/App.h>

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

Scene::Scene()
  : mRendererP{ std::make_unique<SpriteRenderer>() }
  , mCollisionsP{ std::make_unique<CollisionDetector>() }
  , mEngineP{ nullptr }
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
  
  mCollisionsP->updateLists();
  updateTransformAABBs();

  auto err = ci::gl::getErrorString(ci::gl::getError());
  std::ofstream out;
  out.open("log.txt", std::fstream::ate);
  out << "Update transform errors:\n" << err << std::endl;

  mCollisionsP->checkForCollisions();

  mRendererP->draw();
}

void Scene::updateTransformAABBs()
{
  auto numPoints = mCollisionsP->mTransforms.size() * 4;
  auto cornerSize = sizeof(decltype(mCollisionsP->mCorners)::value_type);
  auto cornersBuffer = ci::gl::BufferObj::create(
    GL_SHADER_STORAGE_BUFFER, cornerSize * numPoints,
    mCollisionsP->mCorners.data(),
    GL_STATIC_READ
  );

  auto transformData = std::vector<Transform2dData>{};
  transformData.reserve(mCollisionsP->mTransforms.size());
  for (auto transform : mCollisionsP->mTransforms) {
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
    mCollisionsP->mCorners.data());
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
