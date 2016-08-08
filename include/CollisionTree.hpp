#pragma once

namespace Aton
{
  class GameObject;

  class CollisionTree
  {
  public:
    CollisionTree();

    GameObject* collides();

  private:
    class Node
    {
    };

  };
}