#ifndef CAMERA_TRACKBALL_H_
#define CAMERA_TRACKBALL_H_

#include <Eigen/Dense>

/// Implements a 3D trackball around the Z axis.
class CameraTrackball {
 public:
  static const float DEFAULT_EULER_YAW;
  static const float DEFAULT_EULER_PITCH;

 public:
  CameraTrackball();
  /// Init the camera to look at cen at a distance r0.
  void init(Eigen::Vector3f center, float r0);
  void lookAt();
  /// Rotate the camera around the center.
  void rotate(float right_input, float up_input);
  /// Translate the camera in the tangent directions.
  void pan(float right_input, float up_input, float front_input);
  /// Zoom towards the camera center.
  void zoom(int zoom_input);

 private:
  Eigen::Vector3f position_;
  Eigen::Vector3f center_;
  Eigen::Vector3f front_;
  Eigen::Vector3f left_;
  Eigen::Vector3f up_;
  /// Original radius
  float r0_;
  float r_;
  float yaw_;
  float pitch_;
  int zoom_;
};

inline
CameraTrackball::CameraTrackball()
    : position_{0.0f, 0.0f, 0.0f},
      center_{0.0f, 0.0f, 0.0f},
      front_{0.0f, 0.0f, 1.0f},
      left_{0.0f, 0.0f, 1.0f},
      up_{0.0f, 0.0f, 1.0f},
      r0_{1.0f},
      r_{1.0f},
      yaw_{static_cast<float>(M_PI)},
      pitch_{1.0f},
      zoom_{0} {}

#endif  // CAMERA_TRACKBALL_H_
