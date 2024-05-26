#include "CameraTrackball.h"

#include <GLUT/glut.h>
#include <Eigen/Dense>

static const float HALFPI_F = static_cast<float>(0.5*M_PI);

const float CameraTrackball::DEFAULT_EULER_YAW = 0;
const float CameraTrackball::DEFAULT_EULER_PITCH = HALFPI_F - 0.001f;

void CameraTrackball::init(Eigen::Vector3f center, float r0) {
  center_ = center;
  r0_ = r0;
  r_ = r0_;
  yaw_ = DEFAULT_EULER_YAW;
  pitch_ = DEFAULT_EULER_PITCH;
  zoom_ = 0;
}

void CameraTrackball::lookAt() {
  front_ = (- (cos(pitch_) * cos(yaw_) * Eigen::Vector3f::UnitX() + 
      cos(pitch_) * sin(yaw_) * Eigen::Vector3f::UnitY() + 
      sin(pitch_) * Eigen::Vector3f::UnitZ())).normalized();
  left_ = (Eigen::Vector3f::UnitZ().cross(front_)).normalized();
  up_ = (front_.cross(left_)).normalized();

  position_ = center_ - r_ * front_;
  
  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position_[0], position_[1], position_[2],
	    center_[0], center_[1], center_[2],
	    0.0, 0.0, 1.0);
}

void CameraTrackball::rotate(float right_input, float up_input) {

  yaw_ += HALFPI_F * right_input;
  pitch_ += HALFPI_F * up_input;

  // Normalize yaw to [-pi, pi[
  //yaw_ = normalizeAngleMinusPiPi(yaw_);

  // Clamp pitch to ]-pi/2, pi/2[
  static const float PITCH_MIN = -HALFPI_F + 0.001f;
  static const float PITCH_MAX = HALFPI_F - 0.001f;
  pitch_ = std::min(std::max(pitch_, PITCH_MIN), PITCH_MAX);
}

void CameraTrackball::pan(float right_input, float up_input, float front_input) {
  center_ +=
      -right_input * r_ * left_ +
      up_input * r_ * up_ +
      front_input * r_ * front_;
}

void CameraTrackball::zoom(int zoom_input) {
  zoom_ += zoom_input;
  r_ = r0_ * pow(1.1f, zoom_);
}

