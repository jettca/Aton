#pragma once

#include "Component.hpp"

#include <memory>

namespace Aton
{
  class Sprite;

  class Character : public Component
  {
  public:
    Character();

    void initialize() override;

    void update(float deltaTime) override;

    const Sprite* getSprite() const;

  private:
    float mSpeed;
    std::unique_ptr<Sprite> mSpriteP;
  };
}