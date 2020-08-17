//
// Created by dakor on 5/2/19.
//

#ifndef EYE_STATUS_H
#define EYE_STATUS_H

#include "utils/Geometry.h"

namespace EyeBehavior {

class EyeStatus {
  public:
  Vector2 eye_pos;
  float eye_roll = 0;
  float upper_eyelid_value = 0;
  float lower_eyelid_value = 0;
  float pupil_size_factor = 1;
  
};

} // namespace EyeBehavior

#endif // EYE_STATUS_H