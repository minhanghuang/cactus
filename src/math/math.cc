#include "cactus/math/math.h"

namespace cactus {
namespace math {

double NormalizeAngle(const double angle) {
  double a = std::fmod(angle + M_PI, 2.0 * M_PI);
  if (a < 0.0) {
    a += (2.0 * M_PI);
  }
  return a - M_PI;
}

}  // namespace math
}  // namespace cactus
