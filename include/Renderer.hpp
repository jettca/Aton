#pragma once

namespace Aton
{
  class Sprite;

  class Renderer
  {
  public:
    Renderer();
    void draw();
    void addSprite(const Sprite& sprite);
  };
}