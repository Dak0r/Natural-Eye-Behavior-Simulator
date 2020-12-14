#include "Eye.h"

#include "utils/Debug.h"
#include "EyeMathUtils.h"
#include "EyeModifier.h"
#include "modifiers/RandomLookModifier.h"
#include "modifiers/RandomBlinkModifier.h"

#include <cstdio>


EyeBehavior::Eye::Eye(){
    current_values_ = EyeStatus();
    target_values_ = EyeStatus();
}

EyeBehavior::Eye::~Eye(){
}

void EyeBehavior::Eye::init(unsigned long now, EyeBehavior::EyeConfig *usedEyeConfig,
                            std::vector<EyeBehavior::EyeModifier *>* eyeModifiers) {

    current_eye_config_ = usedEyeConfig;

    // Default Modifier Setup if no setup provided
    if(eyeModifiers == nullptr) {
        active_modifiers = new std::vector<EyeModifier *>();
        EyeModifier* randomLookModifier = new RandomLookModifier();
        EyeModifier* randomBlinkModifier = new RandomBlinkModifier();

        randomLookModifier->init(now, 1);
        randomBlinkModifier->init(now, 1);

        active_modifiers->push_back(randomLookModifier);
        active_modifiers->push_back(randomBlinkModifier);
    }else{
        active_modifiers = eyeModifiers;
    }

    init_pos(now);
}

void EyeBehavior::Eye::init_pos(unsigned long now){
    current_values_.eye_pos.x = 0.5;
    current_values_.eye_pos.y = 0.5;
    target_values_.eye_pos = current_values_.eye_pos;
}


void EyeBehavior::Eye::init_head_rotation(float pan, float tilt, float roll) {
    head_mode = HEAD_MODE_ABSOLUTE;
    head_rotation_reference[0] = pan;
    head_rotation_reference[1] = tilt;
    head_rotation_reference[2] = roll;
}
void EyeBehavior::Eye::update_head_rotation(float pan, float tilt, float roll) {
    head_rotation[0] = pan;
    head_rotation[1] = tilt;
    head_rotation[2] = roll;
}
void EyeBehavior::Eye::init_head_gyro() {
    head_mode = HEAD_MODE_GYRO;
}
void EyeBehavior::Eye::update_head_gyro(float pan, float tilt, float roll) {
    head_gyro[0] = pan;
    head_gyro[1] = tilt;
    head_gyro[2] = roll;
}


float EyeBehavior::Eye::get_position_x(){
    return current_values_.eye_pos.x;
}

float EyeBehavior::Eye::get_position_y(){
    return current_values_.eye_pos.y;
}


float EyeBehavior::Eye::get_upper_eyelid(){
    return current_values_.upper_eyelid_value;
}

float EyeBehavior::Eye::get_lower_eyelid(){
    return current_values_.lower_eyelid_value;
}

float EyeBehavior::Eye::get_pupil_size(){
    return current_values_.pupil_size_factor;
}

void EyeBehavior::Eye::update(unsigned long timeInMs, float timeScale){
    now = timeInMs;

    handle_modifiers();

    if(target_values_.eye_pos != current_values_.eye_pos){
        current_values_.eye_pos = 
            lerp(current_values_.eye_pos, target_values_.eye_pos, current_eye_config_->eye_movement_speed * timeScale);
    }
    
    if(target_values_.pupil_size_factor != current_values_.pupil_size_factor){
        current_values_.pupil_size_factor = 
            lerp(current_values_.pupil_size_factor, target_values_.pupil_size_factor, current_eye_config_->pupil_size_speed * timeScale);
    }
    if(target_values_.upper_eyelid_value != current_values_.upper_eyelid_value){
        current_values_.upper_eyelid_value = 
            lerp(current_values_.upper_eyelid_value, target_values_.upper_eyelid_value, current_eye_config_->eyelid_movement_speed * timeScale);
    } 
    if(target_values_.lower_eyelid_value != current_values_.lower_eyelid_value){
        current_values_.lower_eyelid_value = 
            lerp(current_values_.lower_eyelid_value, target_values_.lower_eyelid_value, current_eye_config_->eyelid_movement_speed * timeScale);
    }
    if(current_eye_config_->eye_roll_enabled && target_values_.eye_roll != current_values_.eye_roll){
        current_values_.eye_roll = lerp(current_values_.eye_roll, target_values_.eye_roll, current_eye_config_->eye_roll_speed * timeScale);
    }

    

}

void EyeBehavior::Eye::handle_modifiers(){

    std::vector<EyeModifier*>::iterator modifier;
    for(modifier = active_modifiers->begin() ;
        modifier != active_modifiers->end() ;
        ++modifier)
    {
        (*modifier)->update(now, current_eye_config_, &target_values_, &current_values_);
    }

}