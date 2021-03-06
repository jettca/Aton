#include "FMOD.hpp"

#include "Game.hpp"
#include "Scene.hpp"
#include "Character.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "LevelRenderer.hpp"
#include "AssetManager.hpp"
#include "Transform2d.hpp"
#include "Collider2d.hpp"

using namespace Aton;
class Meme;

class MyGame : public Game
{
public:
  void setup() override;
  static void prepareSettings(Settings *settings);

  FMOD::System *mSystem;
  FMOD::Sound *mSound;
  FMOD::Channel	*mChannel;
  std::shared_ptr<Sprite> mSprite;
  std::shared_ptr<Meme> mLady;


  Scene mScene;
  Camera* mCam;
  std::unique_ptr<Character> mCharacterP;

  int mWidth, mHeight;
};

void MyGame::setup()
{
  mEngine.setScene(mScene);

  auto textureP = mEngine.mSpriteManager.getAsset("thing.png");
  mSprite = std::make_shared<Sprite>(mScene, textureP, textureP);
  mSprite->getTransform()->position = glm::vec3{ 3, 3, -5 };

  mCharacterP = std::make_unique<Character>(mScene);

  mCam = mScene.makeObject()->addComponent<Camera>(
    glm::vec3{ 0, 0, -1 }, mCharacterP->getSprite()->getTransform());
  mScene.addCamera(*mCam);

  auto tileManager = std::make_shared<AssetManager<Texture>>("level");
  auto tileToFile = [](glm::ivec2 coord)
  {
    return std::to_string(coord.x) + "_" + std::to_string(coord.y) + ".png";
  };

  mScene.makeObject()->addComponent<LevelRenderer>(tileManager,
    mCam, glm::vec2{ 3, 3 }, glm::ivec2{ 1, 1 }, tileToFile);

  FMOD::System_Create(&mSystem);
  mSystem->init(32, FMOD_INIT_NORMAL | FMOD_INIT_ENABLE_PROFILE, NULL);

//  mSystem->createSound(ci::app::getAssetPath("Blank__Kytt_-_08_-_RSPN.mp3").string().c_str(),
//    FMOD_SOFTWARE, NULL, &mSound);
//  mSound->setMode(FMOD_LOOP_NORMAL);

//  mSystem->playSound(FMOD_CHANNEL_FREE, mSound, false, &mChannel);
}

void MyGame::prepareSettings(Settings* settings)
{
  settings->setWindowSize(1280, 720);
  settings->setFrameRate(60);
}

ATON_GAME(MyGame, MyGame::prepareSettings)