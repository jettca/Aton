#include "Character.hpp"
#include "Sprite.hpp"
#include "Transform2d.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Engine.hpp"
#include "CharacterControl.hpp"
#include "GameObject.hpp"

using namespace Aton;

Character::Character(Scene& scene)
{
  auto texP = scene.getEngine()->mSpriteManager.getAsset("thing.png");

  mSpriteP = std::make_unique<Sprite>(scene, texP, texP);
  mSpriteP->getTransform()->position = glm::vec3{ 0, 0, -5 };

  mSpriteP->getObject()->addComponent<CharacterControl>(mSpriteP.get());
}

Character::~Character()
{}

const Sprite* Character::getSprite() const
{
  return mSpriteP.get();
}