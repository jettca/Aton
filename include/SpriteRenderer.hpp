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

    void initialize() override;
    void update(float deltaTime) override;

    const Sprite* getSprite() const;

  private:
    std::unique_ptr<Sprite> mSpriteP;
  };
}