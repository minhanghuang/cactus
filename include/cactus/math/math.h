#ifndef CACTUS_MATH_H_
#define CACTUS_MATH_H_

#include <cmath>
#include <string>

namespace cactus {
namespace math {

template <typename T>
T Square(const T value) {
  return value * value;
}

double NormalizeAngle(const double angle);

template <typename T>
double EuclideanDistance(const T& p0, const T& p1) {
  return std::sqrt(std::pow(p0.x - p1.x, 2.0) + std::pow(p0.y - p1.y, 2.0));
}

template <typename T>
double ManhattanDistance(const T& p0, const T& p1) {
  return std::abs(p0.x - p1.x) + std::abs(p0.y - p1.y);
}

/**
 * @brief Clamp a value between two bounds.
 *        If the value goes beyond the bounds, return one of the bounds,
 *        otherwise, return the original value.
 * @param value The original value to be clamped.
 * @param bound1 One bound to clamp the value.
 * @param bound2 The other bound to clamp the value.
 * @return The clamped value.
 */
template <typename T>
T Clamp(const T value, T bound1, T bound2) {
  if (bound1 > bound2) {
    std::swap(bound1, bound2);
  }

  if (value < bound1) {
    return bound1;
  } else if (value > bound2) {
    return bound2;
  }
  return value;
}

}  // namespace math
}  // namespace cactus

#endif  // CACTUS_EULER_ANGLES_ZXY_H_
