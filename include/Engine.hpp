#pragma once

#include "AssetManager.hpp"

#include <cinder/app/KeyEvent.h>

namespace Aton
{
  class Scene;
  class Texture;

  enum InputFlag {
    PRESSED = 1 << 0,
    DOWN = 1 << 1,
    RELEASED = 1 << 2,
    UP = 1 << 3 
  };


#pragma region input flag operators

  inline InputFlag operator|(InputFlag a, InputFlag b)
  {
    return static_cast<InputFlag>(static_cast<int>(a) | static_cast<int>(b));
  }

  inline InputFlag& operator|=(InputFlag& a, InputFlag b)
  {
    return a = static_cast<InputFlag>(static_cast<int>(a) | static_cast<int>(b));
  }

  inline InputFlag operator&(InputFlag a, InputFlag b)
  {
    return static_cast<InputFlag>(static_cast<int>(a) & static_cast<int>(b));
  }

  inline InputFlag& operator&=(InputFlag& a, InputFlag b)
  {
    return a = static_cast<InputFlag>(static_cast<int>(a) & static_cast<int>(b));
  }

  inline InputFlag operator~(InputFlag a)
  {
    return static_cast<InputFlag>(~static_cast<int>(a));
  }

#pragma endregion

  enum Button { LEFT, MIDDLE, RIGHT };

  using Key = ci::app::KeyEvent::Key;

  class Engine
  {
  public:
    Engine();

    AssetManager<Texture> mSpriteManager;

    void update();

    void setScene(Scene& scene);
    Scene* getScene() const;

#pragma region key press stuff

  public:
    const std::vector<InputFlag>& getKeyStates();
    const std::vector<InputFlag>& getMouseStates();

    void keyEvent(bool pressed, int key);
    void mouseEvent(bool pressed, int button);
    
  private:
    std::vector<InputFlag> mCurFrameKeyStates, mLastFrameKeyStates;
    std::vector<InputFlag> mCurFrameMouseStates, mLastFrameMouseStates;

    std::vector<int> mKeysPressed;
    std::vector<int> mKeysReleased;
    std::vector<int> mButtonsPressed;
    std::vector<int> mButtonsReleased;

    const static size_t mNumKeys = 500;
    const static size_t mNumMouseButtons = 30;

#pragma endregion

#pragma region time stuff

  private:
    Scene* mSceneP;
    using mytime_t = std::chrono::high_resolution_clock::time_point;
    std::unique_ptr<mytime_t> mLastUpdateTimeP;

    static mytime_t clockTime();
    float timeSinceUpdate();

#pragma endregion

  };
}