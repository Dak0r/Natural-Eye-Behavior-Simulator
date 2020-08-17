#ifndef EYECONFIG_H
#define EYECONFIG_H

#include "utils/Geometry.h"

namespace EyeBehavior {
class EyeConfig {
private:
public:
  EyeConfig(){

  };
  ~EyeConfig(){

  };

 
  float eye_movement_speed = 0.5;
  float eyelid_movement_speed = 0.2;
  float pupil_size_speed = 0.5;
  float eye_roll_speed = 0.5;

  Range eye_x_range;  // 0 = sceen LEFT, 1 = screen RIGHT
  Range eye_y_range;  // 0 = screen TOP, 1 = screen BOTTOM

  bool eye_roll_enabled = false;
  Range eye_roll_range;  // 0 = sceen LEFT, 1 = screen RIGHT

  Range eyelid_upper_y_range;  // 0 = screen TOP, 1 = screen BOTTOM
  Range eyelid_lower_y_range;  // 0 = screen TOP, 1 = screen BOTTOM

  Range pupil_size;  // 0 = min Size, 1 = max Size

  bool  blink_enabled = true;
  Range blink_timing_duration; // in ms
  Range blink_timing_in_between; // in ms

  Range eye_focus_time; // in ms 250 - 2000

};
} // namespace EyeBehavior

#endif