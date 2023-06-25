/*
 * Copyright (C) 2023 minhanghuang <job@minhang.me>. - All Rights Reserved
 */
#ifndef INCLUDE_CACTUS_GEOMETRY_GEOMETRY_H_
#define INCLUDE_CACTUS_GEOMETRY_GEOMETRY_H_

#include <cmath>
#include <string>
#include <vector>

#include "cactus/macros.h"

namespace cactus {
namespace geometry {

class Point2D {
  CACTUS_REGISTER_MEMBER_BASIC_TYPE(double, x, 0);
  CACTUS_REGISTER_MEMBER_BASIC_TYPE(double, y, 0);

 public:
  Point2D() : x_(0), y_(0) {}
  Point2D(double x, double y) : x_(x), y_(y) {}
};

class Point3D : public Point2D {
  CACTUS_REGISTER_MEMBER_BASIC_TYPE(double, z, 0);

 public:
  Point3D() : Point2D(), z_(0) {}
  Point3D(double x, double y) : Point2D(x, y), z_(0) {}
  Point3D(double x, double y, double z) : Point2D(x, y), z_(z) {}
};

typedef std::vector<Point3D> Polygon;

class Point4D : public Point3D {
  CACTUS_REGISTER_MEMBER_BASIC_TYPE(double, heading, 0);

 public:
  Point4D() : Point3D(), heading_(0) {}
  Point4D(double x, double y) : Point3D(x, y), heading_(0) {}
  Point4D(double x, double y, double z) : Point3D(x, y, z), heading_(0) {}
  Point4D(double x, double y, double z, double heading)
      : Point3D(x, y, z), heading_(heading) {}
};

}  // namespace geometry
}  // namespace cactus

#endif  // INCLUDE_CACTUS_GEOMETRY_GEOMETRY_H_
