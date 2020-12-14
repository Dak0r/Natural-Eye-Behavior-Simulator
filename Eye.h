#ifndef EYE_H
#define EYE_H

//#include <iostream>
#include "EyeConfig.h"
#include "EyeStatus.h"

namespace EyeBehavior {
class Eye {
public:

  Eye(EyeConfig *usedEyeConfig);
  
  void init_pos(unsigned long now);
  void update(unsigned long timeInMs, float timeScale = 1);


  // used to init rotation, to calculate deltas
  // must be called once, before first call of update_head_rotation
  void init_head_rotation(float pan, float tilt, float roll):

  // used to apply effects by absolute rotations
  // should be called before every update
  // no effects implemented, yet
  void update_head_rotation(float pan, float tilt, float roll);

  // used to enable gyro data usage
  // must be called once, before first call of update_head_gyro
  void init_head_rotation();

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

  unsigned long blink_time_last_ = 0.0;
  unsigned long blink_time_next_ = 1.0;

  int   c1urrent_blink_state_ = 0; // 0 = opend, 1 = idle, 2= closing, 3 = closed, 4 = opening
  float current_blink_duration_ = 0.1;
  unsigned long current_blink_time_start_ = 0;
  float current_blink_progress_ = 0;


  enum HeadMode {HEAD_MODE_NONE, HEAD_MODE_ABSOLUTE, HEAD_MODE_GYRO};
  HeadMode head_mode;
  float head_rotation[3];
  float head_rotation_reference[3];
  float head_gyro[3];

  float display_degree = 45;

  unsigned long time_last_random_pos = 0;
  float time_next_random_pos = 0;

  unsigned long now;

  void handle_position();
  void handle_blink();
};
} // namespace EyeBehavior
#endif