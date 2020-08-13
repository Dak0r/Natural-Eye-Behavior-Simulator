//
// Created by dakor on 5/2/19.
//

#ifndef EYE_STATUS_H
#define EYE_STATUS_H

#include "utils/Geometry.h"

namespace EyeBehavior {

class EyeStatus {
  Vector2 eye_pos;
  float upper_eyelid_pos;
  float lower_eyelid_pos;
  float pupilSize = 1;
};

} // namespace EyeBehavior

#endif // EYE_STATUS_H