#include "Transform2d.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"

using namespace Aton;

Transform2d::Transform2d()
  : rotation{ 0 }
  , size{ 1, 1 }
{}

void Transform2d::update(float deltaTime)
{}