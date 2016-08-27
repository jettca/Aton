#include "Game.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

#include <cinder/gl/gl.h>

using namespace Aton;

Game::Game()
{}

Game::~Game()
{}

void Game::draw()
{
  ci::gl::clear();
  ci::gl::enableAlphaBlending(true);
  ci::gl::enableDepth();

  mEngine.update();
}

void Game::resize()
{
  mEngine.getScene()->getCamera()->getCameraPersp().setAspectRatio(
    static_cast<float>(ci::app::getWindowWidth()) / ci::app::getWindowHeight());
}