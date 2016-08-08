#include "Scene.h"
#include "CollisionTree.h"

using namespace Aton;

Scene::Scene()
  : mTreeP{ std::make_unique<CollisionTree>() }
{}

Scene::~Scene()
{}