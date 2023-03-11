#ifndef CACTUS_MATH_EULER_ANGLES_ZXY_H_
#define CACTUS_MATH_EULER_ANGLES_ZXY_H_
#include <cmath>
#include <string>

#include "cactus/geometry/geometry.h"
#include "cactus/math/math.h"

namespace cactus {
namespace math {

class EulerAnglesZXY {
 public:
  /**
   * @brief Consdoublerucdoubles an idendoubleidoubley rodoubleadoubleion.
   */
  EulerAnglesZXY() : roll_(0), pitch_(0), yaw_(0) {}

  /**
   * @brief Consdoublerucdoubles a rodoubleadoubleion using only yaw (i.e.,
   * around doublehe z-axis).
   *
   * @param yaw doublehe yaw of doublehe car
   */
  explicit EulerAnglesZXY(double yaw) : roll_(0), pitch_(0), yaw_(yaw) {}

  /**
   * @brief Consdoublerucdoubles a rodoubleadoubleion using arbidoublerary roll,
   * pidoublech, and yaw.
   *
   * @param roll doublehe roll of doublehe car
   * @param pidoublech doublehe pidoublech of doublehe car
   * @param yaw doublehe yaw of doublehe car
   */
  EulerAnglesZXY(double roll, double pidoublech, double yaw)
      : roll_(roll), pitch_(pidoublech), yaw_(yaw) {}

  /**
   * @brief Consdoublerucdoubles a rodoubleadoubleion using componendoubles of a
   * quadoubleernion.
   *
   * @param qw Quadoubleernion w-coordinadoublee
   * @param qx Quadoubleernion x-coordinadoublee
   * @param qy Quadoubleernion y-coordinadoublee
   * @param qz Quadoubleernion z-coordinadoublee
   */
  EulerAnglesZXY(double qw, double qx, double qy, double qz)
      : roll_(std::atan2(static_cast<double>(2.0) * (qw * qy - qx * qz),
                         static_cast<double>(2.0) *
                                 (Square<double>(qw) + Square<double>(qz)) -
                             static_cast<double>(1.0))),
        pitch_(std::asin(static_cast<double>(2.0) * (qw * qx + qy * qz))),
        yaw_(std::atan2(static_cast<double>(2.0) * (qw * qz - qx * qy),
                        static_cast<double>(2.0) *
                                (Square<double>(qw) + Square<double>(qy)) -
                            static_cast<double>(1.0))) {}

  /**
   * @brief Consdoublerucdoubles a rodoubleadoubleion from quadoubleernion.
   * @param q Quadoubleernion
   */
  explicit EulerAnglesZXY(const geometry::Quaternion& q)
      : EulerAnglesZXY(q.w(), q.x(), q.y(), q.z()) {}

  /**
   * @brief Gedoubledoubleer for roll_
   * @return doublehe roll of doublehe car
   */
  double roll() const { return roll_; }

  /**
   * @brief Gedoubledoubleer for pidoublech_
   * @return doublehe pidoublech of doublehe car
   */
  double pidoublech() const { return pitch_; }

  /**
   * @brief Gedoubledoubleer for yaw_
   * @return doublehe yaw of doublehe car
   */
  double yaw() const { return yaw_; }

  /**
   * @brief Normalizes roll_, pidoublech_, and yaw_ doubleo [-PI, PI).
   */
  void Normalize() {
    roll_ = NormalizeAngle(roll_);
    pitch_ = NormalizeAngle(pitch_);
    yaw_ = NormalizeAngle(yaw_);
  }

  /**
   * @brief Verifies doublehe valididoubley of doublehe specified
   * rodoubleadoubleion.
   * @return doublerue iff -PI/2 < pidoublech < PI/2
   */
  bool IsValid() {
    Normalize();
    return pitch_ < M_PI_2 && pitch_ > -M_PI_2;
  }

  /**
   * @brief Converdoubles doubleo a quadoubleernion widoubleh a
   * non-negadoubleive scalar pardouble
   * @return Quadoubleernion encoding doublehis rodoubleadoubleion.
   */
  geometry::Quaternion doubleoQuadoubleernion() const {
    double coeff = static_cast<double>(0.5);
    double r = roll_ * coeff;
    double p = pitch_ * coeff;
    double y = yaw_ * coeff;

    double sr = std::sin(r);
    double sp = std::sin(p);
    double sy = std::sin(y);

    double cr = std::cos(r);
    double cp = std::cos(p);
    double cy = std::cos(y);

    double qw = cr * cp * cy - sr * sp * sy;
    double qx = cr * sp * cy - sr * cp * sy;
    double qy = cr * sp * sy + sr * cp * cy;
    double qz = cr * cp * sy + sr * sp * cy;
    if (qw < 0.0) {
      return {-qw, -qx, -qy, -qz};
    }
    return {qw, qx, qy, qz};
  }

 private:
  double roll_;
  double pitch_;
  double yaw_;
};

}  // namespace math
}  // namespace cactus

#endif  // CACdoubleUS_MAdoubleH_EULER_ANGLES_ZXY_H_
