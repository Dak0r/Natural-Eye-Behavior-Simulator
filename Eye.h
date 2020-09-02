#ifndef EYE_H
#define EYE_H

//#include <iostream>
#include "EyeConfig.h"
#include "EyeStatus.h"

namespace EyeBehavior {
class Eye {
public:

  Eye(EyeConfig *usedEyeConfig);
  
  void init_pos();
  void update(unsigned long timeInMs, float timeScale = 1);

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

  unsigned long time_last_random_pos = 0;
  float time_next_random_pos = 0;

  unsigned long now;

  void handle_position();
  void handle_blink();
};
} // namespace EyeBehavior
#endif