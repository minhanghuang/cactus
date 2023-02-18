#ifndef CACTUS_GEOMETRY_H_
#define CACTUS_GEOMETRY_H_

#include <cmath>
#include <string>

namespace cactus {
namespace geometry {

template <typename T>
struct Quaternion {
  T x;
  T y;
  T z;
  T w;
};

}  // namespace geometry
}  // namespace cactus

#endif  // CACTUS_GEOMETRY_H_
