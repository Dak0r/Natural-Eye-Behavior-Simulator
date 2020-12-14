//
// Created by dakor on 12/14/20.
//

#include "RandomLookModifier.h"

string EyeBehavior::RandomLookModifier::getName() {
    return "random_look_modifier";
}

void EyeBehavior::RandomLookModifier::init(unsigned long now, float modifier) {
    this->now = now;
    setModifier(modifier);
}

void EyeBehavior::RandomLookModifier::update(unsigned long now, EyeConfig* current_eye_config, EyeStatus* eyeTargetValues, EyeStatus* eyeCurrentValues) {
    if(time_next_random_pos < now){
        time_last_random_pos = now;
        if(getModifier() > 0) { // skip actions if they would not be visible anyway
            float rndpos_x = randomFloat(0, 2) - 1;
            float rndpos_y = randomFloat(0, 2) - 1;
            float rndPupilSize = randomFloat(current_eye_config->pupil_size);
            eyeTargetValues->eye_pos.x = lerp(eyeTargetValues->eye_pos.x, rndpos_x, getModifier());
            eyeTargetValues->eye_pos.y = lerp(eyeTargetValues->eye_pos.y, rndpos_y, getModifier());
            eyeTargetValues->pupil_size_factor = lerp(eyeTargetValues->pupil_size_factor, rndPupilSize, getModifier());
            //std::cout << time << " - new Random Pos: " << rndpos_x << " : " << rndpos_y << " Next in: " << time_next_random_pos << std::endl;
        }
        time_next_random_pos = now + randomFloat(current_eye_config-> eye_focus_time);
    }
}