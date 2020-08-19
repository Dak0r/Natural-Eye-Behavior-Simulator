#ifndef EYECONFIG_H
#define EYECONFIG_H

#include "EyeMathUtils.h"

namespace EyeBehavior {
class EyeConfig {
private:
public:
  EyeConfig(){
    eye_x_range.min = 0;
    eye_x_range.max = 1;

    eye_y_range.min = 0;
    eye_y_range.max = 1;

    eye_roll_range.min = -33;
    eye_roll_range.max = 33;

    eyelid_upper_y_range.min = 0;
    eyelid_upper_y_range.max = 0.5;    
    eyelid_lower_y_range.min = 1;
    eyelid_lower_y_range.max = 0.5; 

    pupil_size.min = 0.2f;
    pupil_size.max = 1;

    blink_timing_duration.min = 35;
    blink_timing_duration.max = 65;

    blink_timing_in_between.min = 0;
    blink_timing_in_between.max = 4000;

    eye_focus_time.min = 250;
    eye_focus_time.max = 2000;

  };
  ~EyeConfig(){

  };

 
  float eye_movement_speed = 0.35;
  float eyelid_movement_speed = 0.15;
  float pupil_size_speed = 0.1;
  float eye_roll_speed = 0.05;
  bool eye_roll_enabled = false;
  bool  blink_enabled = true;


  Range eye_x_range;  // 0 = sceen LEFT, 1 = screen RIGHT
  Range eye_y_range;  // 0 = screen TOP, 1 = screen BOTTOM

  
  Range eye_roll_range;  // 0 = sceen LEFT, 1 = screen RIGHT

  Range eyelid_upper_y_range;  // 0 = screen TOP, 1 = screen BOTTOM
  Range eyelid_lower_y_range;  // 0 = screen TOP, 1 = screen BOTTOM

  Range pupil_size;  // 0 = min Size, 1 = max Size

  
  Range blink_timing_duration; // in ms
  Range blink_timing_in_between; // in ms

  Range eye_focus_time; // in ms 250 - 2000

};
} // namespace EyeBehavior

#endif