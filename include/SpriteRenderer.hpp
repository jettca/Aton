#pragma once

#include "Component.hpp"

#include <memory>

namespace Aton
{
  class Sprite;

  class SpriteRenderer : public Component
  {
  public:
    SpriteRenderer(std::unique_ptr<Sprite> spriteP);
    void update(float deltaTime);

    const Sprite* getSprite() const;

  private:
    std::unique_ptr<Sprite> mSpriteP;
  };
}