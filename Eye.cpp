#include "Eye.h"

#include "Geometry.h"

EyeBehavior::Eye::Eye(EyeConfig *usedEyeConfig){
    current_eye_config_ = usedEyeConfig;
    
    current_values_ = &EyeStatus();
    target_values_ = &EyeStatus();


}

void EyeBehavior::Eye::update(ulong timeInMs){
    now = timeInMs;

}

void EyeBehavior::Eye::handle_blink(){
    if(c1urrent_blink_state_ == 0){
        blink_time_next_ = now + random(current_eye_config_->blink_time_in_between);
    }
}