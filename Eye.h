#ifndef EYE_H
#define EYE_H

#include <iostream>
#include <math.h>

#include "EyeConfig.h"
#include "EyeStatus.h"

namespace EyeBehavior {
class Eye {
public:

  Eye(EyeConfig *usedEyeConfig);
  
  void init_pos();
  void update(ulong timeInMs);

  // controller calls

  void set_position_pixels(int pos_x, int pos_y);
  void set_position(float pos_x, float pos_y);
  void set_pupil_size(float pupilSize);
  float get_position_x();
  float get_position_y();

private:
  EyeConfig *currentEyeConfig;

  EyeStatus *current_values_;
  EyeStatus *target_values_;

  ulong blink_time_last_ = 0.0;
  float blink_time_next_ = 1.0;
  int current_blink_state_ = 0;
  float current_blink_duration_ = 0.1;
  ulong current_blink_time_start_ = 0;
  float current_blink_progress = 0;

  ulong now;

  void set_eyelid_upper_open_absolute(float upper_eyelid, bool instant = false);
  void set_eyelid_lower_open_absolute(float lower_eyelid, bool instant = false);
  void set_eyelid_upper_open(float upper_eyelid, bool instant = false);
  void set_eyelid_lower_open(float lower_eyelid, bool instant = false);

  void handle_blink();
};
} // namespace EyeBehavior
#endif