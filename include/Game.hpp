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
  public:
    static ci::app::RendererGl::Options getOptions()
    {
      ci::app::RendererGl::Options options;
      options.setVersion(4, 3);
      return options;
    }

  protected:
    Game();

    ~Game();

    Engine mEngine;

  private:
    void draw() override;
    void resize() override;
  };
}
#define ATON_GAME(GAME) CINDER_APP(GAME, ci::app::RendererGl(Aton::Game::getOptions()))