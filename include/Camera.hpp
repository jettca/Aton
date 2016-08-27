#pragma once

#include "GameObject.hpp"

#include <glm/glm.hpp>
#include <cinder/Camera.h>

namespace Aton
{
  class Transform2d;

  class Camera : public Component
  {
  public:
    Camera(glm::vec3 direction = glm::vec3{ 0, 0, 1 },
      Transform2d* toTrack = nullptr);

    void update(float deltaTime) override;

    ci::CameraPersp& getCameraPersp() const;

    void setPosition(glm::vec3 position);
    void setDirection(glm::vec3 direction);

    const glm::vec3& getPosition() const;
    const glm::vec3& getDirection() const;

  private:
    glm::vec3 mPosition, mDirection, mUp;

    Transform2d* mToTrack;

    std::unique_ptr<ci::CameraPersp> mCam;
  };
}