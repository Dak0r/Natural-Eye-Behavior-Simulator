#include "Eye.h"

#include "utils/Debug.h"

EyeBehavior::Eye::Eye(EyeConfig *usedEyeConfig){
    current_eye_config_ = usedEyeConfig;
    
    current_values_ = EyeStatus();
    target_values_ = EyeStatus();


}

void EyeBehavior::Eye::update(unsigned long timeInMs){
    now = timeInMs;

    handle_position();
    handle_blink();

    if(target_values_.eye_pos != current_values_.eye_pos){
        current_values_.eye_pos = 
            lerp(current_values_.eye_pos, target_values_.eye_pos, current_eye_config_->eye_movement_speed);
    }
    
    if(target_values_.pupil_size_factor != current_values_.pupil_size_factor){
        current_values_.pupil_size_factor = 
            lerp(current_values_.pupil_size_factor, target_values_.pupil_size_factor, current_eye_config_->pupil_size_speed);
    }
    if(target_values_.upper_eyelid_value != current_values_.upper_eyelid_value){
        current_values_.upper_eyelid_value = 
            lerp(current_values_.upper_eyelid_value, target_values_.upper_eyelid_value, current_eye_config_->eyelid_movement_speed);
    } 
    if(target_values_.lower_eyelid_value != current_values_.lower_eyelid_value){
        current_values_.lower_eyelid_value = 
            lerp(current_values_.lower_eyelid_value, target_values_.lower_eyelid_value, current_eye_config_->eyelid_movement_speed);
    }
    if(current_eye_config_->eye_roll_enabled && target_values_.eye_roll != current_values_.eye_roll){
        current_values_.eye_roll = lerp(current_values_.eye_roll, target_values_.eye_roll, current_eye_config_->eye_roll_speed);
    }

    

}

void EyeBehavior::Eye::handle_position(){
    time_last_random_pos = now;
    float rndpos_x = random(0,2)-1;
    float rndpos_y = random(0,2)-1;
    target_values_.eye_pos.x = rndpos_x;
    target_values_.eye_pos.y = rndpos_y;
    //std::cout << time << " - new Random Pos: " << rndpos_x << " : " << rndpos_y << " Next in: " << time_next_random_pos << std::endl;
    time_next_random_pos = random(current_eye_config_-> eye_focus_time);
}

void EyeBehavior::Eye::handle_blink(){

    if(!current_eye_config_->blink_enabled){
        if(c1urrent_blink_state_ != 0)
        {
            target_values_.upper_eyelid_value = current_eye_config_->eyelid_upper_y_range.min;
            target_values_.lower_eyelid_value = current_eye_config_->eyelid_lower_y_range.min;
            c1urrent_blink_state_ = 0;
        }
        return;
    }

    if(c1urrent_blink_state_ == 0){
        if(now - blink_time_last_ < blink_time_next_){
            return;
        }else{
            debug("waiting for blink time");
            c1urrent_blink_state_ = 1;
        }
    }
     if(c1urrent_blink_state_ == 1){
        debug("starting blink");
        float duration = random(current_eye_config_->blink_timing_duration);
        current_blink_duration_ = duration;
        current_blink_time_start_ = now;
        current_blink_progress_ = 0;
        c1urrent_blink_state_ = 2;
    }
    if(c1urrent_blink_state_ == 2){
        //printf("closing -> %f \n", current_blink_progress_);
        if(current_blink_progress_ < 1){
            
            target_values_.upper_eyelid_value = lerp(current_eye_config_->eyelid_upper_y_range, current_blink_progress_);
            target_values_.lower_eyelid_value = lerp(current_eye_config_->eyelid_lower_y_range, current_blink_progress_);
            current_values_.upper_eyelid_value = target_values_.upper_eyelid_value;
            current_values_.lower_eyelid_value = target_values_.lower_eyelid_value;

            current_blink_progress_ += current_eye_config_->eyelid_movement_speed;
            return;
        }else{
            target_values_.upper_eyelid_value = lerp(current_eye_config_->eyelid_upper_y_range, 1);
            target_values_.lower_eyelid_value = lerp(current_eye_config_->eyelid_lower_y_range, 1);
            current_values_.upper_eyelid_value = target_values_.upper_eyelid_value;
            current_values_.lower_eyelid_value = target_values_.lower_eyelid_value;
            c1urrent_blink_state_ = 3;
        }
    }
    if(c1urrent_blink_state_ == 3){
        debug("wait while eye closed");
        if(now - current_blink_time_start_ < current_blink_duration_){
            return;
        }else{
            current_blink_progress_ = 1;
            c1urrent_blink_state_= 4;
        }
    }
    if(c1urrent_blink_state_ == 4){
        //printf("opening -> %f \n", current_blink_progress_);
        current_values_.pupil_size_factor = target_values_.pupil_size_factor + 0.035;
            target_values_.upper_eyelid_value = lerp(current_eye_config_->eyelid_upper_y_range, 0);
            target_values_.lower_eyelid_value = lerp(current_eye_config_->eyelid_lower_y_range, 0);
            if(current_eye_config_->eye_roll_enabled){
                target_values_.eye_roll = random(current_eye_config_->eye_roll_range);
            }
            c1urrent_blink_state_ = 5;
    }
    if(c1urrent_blink_state_ == 5){
        debug("next blink");
        blink_time_last_ = now;
        blink_time_next_ = current_blink_progress_ * 3 + random(current_eye_config_->blink_timing_in_between);
        c1urrent_blink_state_ = 0;
    }

}