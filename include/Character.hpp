#pragma once

#include <memory>

namespace Aton
{
  class Sprite;
  class Scene;

  class Character
  {
  public:
    Character(Scene& scene);
    ~Character();

    const Sprite* getSprite() const;

  private:
    std::unique_ptr<Sprite> mSpriteP;
  };
}