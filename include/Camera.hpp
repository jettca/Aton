#pragma once

#include "GameObject.hpp"

#include <glm/glm.hpp>

namespace cinder
{
  class CameraPersp;
}
namespace ci = cinder;

namespace Aton
{
  class Engine;
  class Transform2d;

  class Camera : public GameObject
  {
  public:
    Camera(Engine* e, glm::vec3 direction = glm::vec3{ 0, 0, 1 },
      Transform2d* toTrack = nullptr);

    void update(float deltaTime) override;

    ci::CameraPersp& getCameraPersp() const;

    void setPosition(glm::vec3 position);
    void setDirection(glm::vec3 direction);

    const glm::vec3& getPosition() const;
    const glm::vec3& getDirection() const;

  private:
    glm::vec3 mPosition;
    glm::vec3 mDirection;

    Transform2d* mToTrack;

    std::unique_ptr<ci::CameraPersp> mCam;
  };
}