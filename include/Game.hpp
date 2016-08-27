#pragma once

#include "Engine.hpp"

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include <vector>
#include <memory>
#include <chrono>

namespace Aton
{
  class Texture;
  class Scene;

  class Game : public ci::app::App
  {
  protected:
    Game();
    ~Game();

    Engine mEngine;

  private:
    void draw() override;
    void resize() override;
  };
}

#define ATON_GAME(GAME) CINDER_APP(GAME, ci::app::RendererGl)