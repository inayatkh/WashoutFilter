#include "MotionDriveAlgorithm.h"

#include "Filter.h"

class WashoutFilter : public MotionDriveAlgorithm {
public:
  WashoutFilter(Filter *TranslationHighPassFilter[3],
                Filter *TranslationLowPassFilter[2],
                Filter *RotationHighPassFilter[3], unsigned int t_ms);
  ~WashoutFilter();

  Position calculateSimulatorPosition(Motion &motion);
  void setTranslationScale(const double &scale);
  void setRotationScale(const double &scale);

private:
  Filter *tHPF[3];
  Filter *rLPF[2];
  Filter *rHPF[3];

  // 重力加速度gs
  const double GRAVITY_mm; // 重力加速度[mm/s2]
  double gravityX;
  double gravityY;
  double gravityZ;

  // 中間媒介変数、速度、角度
  double m_vx, m_vy, m_vz, phi_t, phi_r, sit_t, sit_r;
  double m_x, m_y, m_z, m_phi, m_sit, m_psi;

  unsigned int interval_ms; // 計算周期
  double transScale;        // 並進のスケール
  double rotateScale;       // 回転のスケール

  // パイロットの体感運動
  struct st6DOF {
    double ax, ay, az, wphi, wsit, wpsi;
  } stPilot;

  // 積分
  inline double timeInteg(const double &x, const double &v) {
    return (x + (v * interval_ms / 1000));
  }

  // class Integrator {
  // public:
  //   Integrator() : value(){};
  //   double getValue() { return value; }
  //   void add(double v) { value += v; }
  //
  // private:
  //   double value;
  // };
};
