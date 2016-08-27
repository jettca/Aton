#include "GameObject.hpp"
#include "Component.hpp"
#include "Engine.hpp"

using namespace Aton;

GameObject::GameObject(Engine* engineP, Scene* sceneP)
  : mEngineP{ engineP }
  , mSceneP{ sceneP }
{}

GameObject::~GameObject()
{}

void GameObject::updateComponents(float deltaTime)
