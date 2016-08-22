#include "Camera.hpp"
#include "Transform2d.hpp"

#include <cinder/Camera.h>
#include <cinder/gl/gl.h>

using namespace Aton;

Camera::Camera(Engine* e, glm::vec3 direction, Transform2d* toTrack)
  : GameObject{ e }
  , mDirection{ direction }
  , mCam{ std::make_unique<ci::CameraPersp>() }
  , mToTrack{ toTrack }
{}

void Camera::update(float deltaTime)
{
  if (mToTrack)
  {
    mPosition.x = mToTrack->position.x;
    mPosition.y = mToTrack->position.y;
    mCam->lookAt(mPosition, mDirection);
    ci::gl::setMatrices(*mCam);
  }
}

ci::CameraPersp& Camera::getCameraPersp() const
{
  return *mCam;
}

void Camera::setPosition(glm::vec3 position)
{
  mPosition = std::move(position);
  mCam->lookAt(mPosition, mDirection);
}

void Camera::setDirection(glm::vec3 direction)
{
  mDirection = std::move(direction);
  mCam->lookAt(mPosition, mDirection);
}

const glm::vec3& Camera::getPosition() const
{
  return mPosition;
}

const glm::vec3& Camera::getDirection() const
{
  return mDirection;
}
