#include "FMOD.hpp"

#include "Game.hpp"
#include "Scene.hpp"
#include "Character.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "LevelRenderer.hpp"
#include "AssetManager.hpp"

using namespace Aton;

class MyGame : public Game
{
public:
  void setup() override;

  FMOD::System *mSystem;
  FMOD::Sound *mSound;
  FMOD::Channel	*mChannel;

  Scene mScene;
  Camera* mCam;

  int mWidth, mHeight;
};

void MyGame::setup()
{
  std::ofstream out;
  out.open("log.txt");
  auto version = ci::gl::getVersionString();
  out << "Version: " << version << std::endl;

  mEngine.setScene(mScene);

  auto character = mScene.makeObject()->addComponent<Character>();
  mCam = mScene.makeObject()->addComponent<Camera>(
    glm::vec3{ 0, 0, -1 }, character->getSprite()->mTransformP);
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

  mSystem->createSound(ci::app::getAssetPath("Blank__Kytt_-_08_-_RSPN.mp3").string().c_str(),
    FMOD_SOFTWARE, NULL, &mSound);
  mSound->setMode(FMOD_LOOP_NORMAL);

  mSystem->playSound(FMOD_CHANNEL_FREE, mSound, false, &mChannel);
}

ATON_GAME(MyGame)