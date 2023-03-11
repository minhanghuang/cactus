#ifndef CACTUS_GEOMETRY_H_
#define CACTUS_GEOMETRY_H_

#include <cmath>
#include <string>
#include <vector>

namespace cactus {
namespace geometry {

class Point2D {
 public:
  Point2D() : x_(0), y_(0) {}
  Point2D(double x, double y) : x_(x), y_(y) {}
  void set_x(double d) { x_ = d; }
  void set_y(double d) { y_ = d; }
  double& mutable_x() { return x_; }
  double& mutable_y() { return y_; }
  double x() const { return x_; }
  double y() const { return y_; }

 protected:
  double x_;
  double y_;
};

class Point3D : public Point2D {
 public:
  Point3D() : Point2D(), z_(0) {}
  Point3D(double x, double y) : Point2D(x, y), z_(0) {}
  Point3D(double x, double y, double z) : Point2D(x, y), z_(z) {}
  void set_z(double d) { z_ = d; }
  double& mutable_z() { return z_; }
  double z() const { return z_; }

 protected:
  double z_;
};

typedef std::vector<Point3D> Polygon;

class Point4D : public Point3D {
 public:
  Point4D() : Point3D(), heading_(0) {}
  Point4D(double x, double y) : Point3D(x, y), heading_(0) {}
  Point4D(double x, double y, double z) : Point3D(x, y, z), heading_(0) {}
  Point4D(double x, double y, double z, double heading)
      : Point3D(x, y, z), heading_(heading) {}
  void set_heading(double d) { heading_ = d; }
  double& mutable_heading() { return heading_; }
  double heading() const { return heading_; }

 protected:
  double heading_;
};

class Quaternion {
 public:
  Quaternion() : x_(0), y_(0), z_(0), w_(0) {}
  Quaternion(double x, double y, double z, double w)
      : x_(x), y_(y), z_(z), w_(w) {}

  void set_x(double d) { x_ = d; }
  void set_y(double d) { y_ = d; }
  void set_z(double d) { z_ = d; }
  void set_w(double d) { w_ = d; }
  double& mutable_x() { return x_; }
  double& mutable_y() { return y_; }
  double& mutable_z() { return z_; }
  double& mutable_w() { return w_; }
  double x() const { return x_; }
  double y() const { return y_; }
  double z() const { return z_; }
  double w() const { return w_; }

 private:
  double x_;
  double y_;
  double z_;
  double w_;
};

}  // namespace geometry
}  // namespace cactus

#endif  // CACTUS_GEOMETRY_H_
