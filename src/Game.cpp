#include "Game.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Engine.hpp"

#include <cinder/gl/gl.h>
#include <cinder/app/KeyEvent.h>

using namespace Aton;

Game::Game()
{}

Game::~Game()
{}

void Game::keyDown(ci::app::KeyEvent e)
{
  mEngine.keyEvent(true, e.getCode());
}

void Game::keyUp(ci::app::KeyEvent e)
{
  mEngine.keyEvent(false, e.getCode());
}

void Game::mouseDown(ci::app::MouseEvent e)
{
  int button;
  if (e.isLeft())
    button = Button::LEFT;
  else if (e.isRight())
    button = Button::RIGHT;
  else if (e.isMiddle())
    button = Button::MIDDLE;
  else
    return;

  mEngine.mouseEvent(true, button);
}

void Game::mouseUp(ci::app::MouseEvent e)
{
  int button;
  if (e.isLeft())
    button = Button::LEFT;
  else if (e.isRight())
    button = Button::RIGHT;
  else if (e.isMiddle())
    button = Button::MIDDLE;
  else
    return;

  mEngine.mouseEvent(false, button);
}

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