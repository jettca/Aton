#pragma once

#include "Component.hpp"

#include <memory>

namespace Aton
{
  class Sprite;

  class CharacterControl : public Component
  {
  public:
    CharacterControl(Sprite* sprite);

    void initialize() override;

    void update(float deltaTime) override;

  private:
    float mSpeed;
    Sprite* mSpriteP;
  };
}