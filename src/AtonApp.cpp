#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/Batch.h"

#include "FMOD.hpp"

using namespace ci;
using namespace ci::app;

#include "Engine.hpp"
#include "Character.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "LevelRenderer.hpp"
#include "AssetManager.hpp"

class AtonApp : public App
{
public:
  void setup() override;
  void draw() override;
  void resize() override;

  FMOD::System *mSystem;
  FMOD::Sound *mSound;
  FMOD::Channel	*mChannel;

  Aton::Engine mEngine;

  int mWidth, mHeight;
};

void AtonApp::setup()
{
  auto character = std::make_unique<Aton::Character>(&mEngine);
  auto camera = std::make_unique<Aton::Camera>(&mEngine, glm::vec3{ 0, 0, 1 },
    character->getSprite()->mTransformP);

  mHeight = 200;
  mWidth = static_cast<int>(mHeight * camera->getCameraPersp().getAspectRatio());
  gl::viewport(0, 0, mWidth, mHeight);

  mEngine.addObject(std::make_unique<Aton::LevelRenderer>(&mEngine,
    std::make_shared<Aton::AssetManager<Aton::Texture>>("level"),
    camera.get()));
  mEngine.addObject(std::move(camera));
  mEngine.addObject(std::move(character));

  FMOD::System_Create(&mSystem);
  mSystem->init(32, FMOD_INIT_NORMAL | FMOD_INIT_ENABLE_PROFILE, NULL);

  mSystem->createSound(getAssetPath("Blank__Kytt_-_08_-_RSPN.mp3").string().c_str(), FMOD_SOFTWARE, NULL, &mSound);
  mSound->setMode(FMOD_LOOP_NORMAL);

  mSystem->playSound(FMOD_CHANNEL_FREE, mSound, false, &mChannel);
}

void AtonApp::draw()
{
  gl::clear();
  gl::enableAlphaBlending(true);
  gl::enableDepth();
  mEngine.update();

  //	// grab 512 samples of the wave data
  //	float waveData[512];
  //	mSystem->getWaveData(waveData, 512, 0);
  //	
  //	// render the 512 samples to a VertBatch
  //	gl::VertBatch vb( GL_LINE_STRIP );
  //	for( int i = 0; i < 512; ++i )
  //		vb.vertex(getWindowWidth() / 512.0f * i, getWindowCenter().y + 100 * waveData[i]);

  //	// draw the points as a line strip
  //	gl::color(Color(1.0f, 0.5f, 0.25f));
  //	vb.draw();
}

void AtonApp::resize()
{
  gl::viewport(0, 0, mWidth, mHeight);
}

CINDER_APP(AtonApp, RendererGl)
