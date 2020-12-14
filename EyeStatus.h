//
// Created by dakor on 5/2/19.
//

#ifndef EYE_STATUS_H
#define EYE_STATUS_H

#include "EyeMathUtils.h"

namespace EyeBehavior {

class EyeStatus {
  public:
  Vector2 eye_pos;
  float eye_roll = 0;
  float upper_eyelid_value = 0;
  float lower_eyelid_value = 1;
  float pupil_size_factor = 0.9;
  
};

} // namespace EyeBehavior

#endif // EYE_STATUS_H