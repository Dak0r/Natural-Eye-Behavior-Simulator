//
// Created by dakor on 12/14/20.
//

#include "RandomBlinkModifier.h"

string EyeBehavior::RandomBlinkModifier::getName() {
    return "random_blink_modifier";
}

void EyeBehavior::RandomBlinkModifier::init(unsigned long now, float modifier) {
    this->now = now;
    setModifier(modifier);

    blink_time_last_ = now;
    blink_time_next_ = 1000; // delay first blink for start up animation
}

void EyeBehavior::RandomBlinkModifier::update(unsigned long now, EyeConfig* eyeConfig, HeadStatus* headStatus, EyeStatus* eyeTargetValues, EyeStatus* eyeCurrentValues) {
    if(getModifier() == 0){ // Blinking for now only supports basic on/off override
        if(c1urrent_blink_state_ != 0 || first_update)
        {
            eyeTargetValues->upper_eyelid_value = eyeConfig->eyelid_upper_y_range.min;
            eyeTargetValues->lower_eyelid_value = eyeConfig->eyelid_lower_y_range.min;
            c1urrent_blink_state_ = 0;
            first_update = false;
        }
        return;
    }

    if(first_update){
        eyeTargetValues->upper_eyelid_value = eyeConfig->eyelid_upper_y_range.max;
        eyeTargetValues->lower_eyelid_value = eyeConfig->eyelid_lower_y_range.max;
        eyeCurrentValues->upper_eyelid_value = eyeConfig->eyelid_upper_y_range.max;
        eyeCurrentValues->lower_eyelid_value = eyeConfig->eyelid_lower_y_range.max;
    }


    if(c1urrent_blink_state_ == 0){
        if(now - blink_time_last_ < blink_time_next_){
            return;
        }else{
            //debug("waiting for blink time");
            c1urrent_blink_state_ = 1;
        }
    }
    if(c1urrent_blink_state_ == 1){
        //debug("starting blink");
        float duration = randomFloat(eyeConfig->blink_timing_duration);
        current_blink_duration_ = duration;

        current_blink_progress_ = 0;
        c1urrent_blink_state_ = 2;
    }
    if(c1urrent_blink_state_ == 2){
        //printf("closing -> %f \n", current_blink_progress_);
        if(current_blink_progress_ < 1){

            eyeTargetValues->upper_eyelid_value = lerp(eyeConfig->eyelid_upper_y_range, current_blink_progress_);
            eyeTargetValues->lower_eyelid_value = lerp(eyeConfig->eyelid_lower_y_range, current_blink_progress_);
            eyeCurrentValues->upper_eyelid_value = eyeTargetValues->upper_eyelid_value;
            eyeCurrentValues->lower_eyelid_value = eyeTargetValues->lower_eyelid_value;

            current_blink_progress_ += eyeConfig->eyelid_movement_speed;
            return;
        }else{
            eyeTargetValues->upper_eyelid_value = lerp(eyeConfig->eyelid_upper_y_range, 1);
            eyeTargetValues->lower_eyelid_value = lerp(eyeConfig->eyelid_lower_y_range, 1);
            eyeCurrentValues->upper_eyelid_value = eyeTargetValues->upper_eyelid_value;
            eyeCurrentValues->lower_eyelid_value = eyeTargetValues->lower_eyelid_value;
            current_blink_time_start_ = now;
            eyeCurrentValues->pupil_size_factor = eyeTargetValues->pupil_size_factor + 0.2;
            c1urrent_blink_state_ = 3;
        }
    }
    if(c1urrent_blink_state_ == 3){
        //debug("wait while eye closed");
        if(now - current_blink_time_start_ < current_blink_duration_){
            return;
        }else{
            current_blink_progress_ = 1;
            c1urrent_blink_state_= 4;
        }
    }
    if(c1urrent_blink_state_ == 4){
        //printf("opening -> %f \n", current_blink_progress_);
        eyeTargetValues->upper_eyelid_value = lerp(eyeConfig->eyelid_upper_y_range, 0);
        eyeTargetValues->lower_eyelid_value = lerp(eyeConfig->eyelid_lower_y_range, 0);
        if(eyeConfig->eye_roll_enabled){
            eyeTargetValues->eye_roll = randomFloat(eyeConfig->eye_roll_range);
        }
        c1urrent_blink_state_ = 5;
    }
    if(c1urrent_blink_state_ == 5){
        //debug("next blink");
        blink_time_last_ = now;
        blink_time_next_ = current_blink_duration_ * 3 + randomFloat(eyeConfig->blink_timing_in_between);
        c1urrent_blink_state_ = 0;
    }
    first_update = false;
}