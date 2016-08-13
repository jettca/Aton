#include "Scene.hpp"
#include "CollisionTree.hpp"

using namespace Aton;

Scene::Scene()
  : mTreeP{ std::make_unique<CollisionTree>() }
{}

Scene::~Scene()
{}