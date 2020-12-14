#ifndef EYE_H
#define EYE_H

//#include <iostream>
#include <vector>
#include "EyeConfig.h"
#include "EyeStatus.h"
#include "HeadStatus.h"
#include "EyeModifier.h"

namespace EyeBehavior {
class Eye {
public:

  Eye();
  ~Eye();

  // Main Init call, call this before anything else on Eye
  void init(unsigned long now, EyeConfig *usedEyeConfig, std::vector<EyeModifier*>* eyeModifiers);

  // Call for every frame
  void update(unsigned long timeInMs, float timeScale = 1);


  // used to init rotation, to calculate deltas
  // must be called once, before first call of update_head_rotation
  void init_head_rotation(float pan, float tilt, float roll);

  // used to apply effects by absolute rotations
  // should be called before every update
  // no effects implemented, yet
  void update_head_rotation(float pan, float tilt, float roll);

  // used to enable gyro data usage
  // must be called once, before first call of update_head_gyro
  void init_head_gyro();

  //  used to apply effects by force instead of absolute numbers
  //  should be called before every update
  // no effects implemented, yet
  void update_head_gyro(float pan, float tilt, float roll);

  float get_position_x();
  float get_position_y();

  float get_upper_eyelid();
  float get_lower_eyelid();

  float get_pupil_size();

private:
  EyeConfig *current_eye_config_;

  EyeStatus current_values_;
  EyeStatus target_values_;

  HeadStatus head_status_;

  std::vector<EyeModifier*>* active_modifiers;




  float display_degree = 45;


  unsigned long now;

  void init_pos(unsigned long now);
  void handle_modifiers();
};
} // namespace EyeBehavior
#endif