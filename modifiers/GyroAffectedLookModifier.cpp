//
// Created by dakor on 12/14/20.
//

#include "GyroAffectedLookModifier.h"

string EyeBehavior::GyroAffectedLookModifier::getName() {
    return "gyro_affected_look_modifier";
}

void EyeBehavior::GyroAffectedLookModifier::init(unsigned long now, float modifier) {
    this->now = now;
    setModifier(modifier);
}

void EyeBehavior::GyroAffectedLookModifier::update(unsigned long now, EyeConfig *current_eye_config, HeadStatus* headStatus,
                                                   EyeStatus *eyeTargetValues, EyeStatus *eyeCurrentValues) {


    float panGyro = min(limit, max(-limit, headStatus->head_gyro[0]));
    float tiltGyro = min(limit, max(-limit, headStatus->head_gyro[1]));

    if(panTrackIndicator == 0 && abs(panGyro) > threshshold) {
        if (panGyro > 0) {
            panTrackIndicator = 1;
        } else {
            panTrackIndicator = -1;
        }
    }else if(panTrackIndicator != 0 && abs(panGyro) < threshshold) {
        panTrackIndicator = 0;
    }
    if ((panTrackIndicator > 0 && panGyro > panTrackIndicator) || (panTrackIndicator < 0 && panGyro < panTrackIndicator)) {
        //panTrackIndicator = panGyro;
        panTrackIndicator = limit * (panTrackIndicator > 0 ? 1 : -1);
        panPowerValue = limit * (panTrackIndicator > 0 ? 1 : -1);
        //panPowerValue = (panPowerValue < limit ? limit : (panPowerValue > limit ? limit : panPowerValue ));
        printf("new max pan: %f \n", panPowerValue);
    } else {
        panPowerValue = lerp(panPowerValue, 0, returnSpeed);
    }


    if(tiltTrackIndicator == 0 && abs(tiltGyro) > threshshold) {
        if (tiltGyro > 0) {
            tiltTrackIndicator = 1;
        } else {
            tiltTrackIndicator = -1;
        }
    }else if(tiltTrackIndicator != 0 && abs(tiltGyro) < threshshold) {
        tiltTrackIndicator = 0;
    }
    if ((tiltTrackIndicator > 0 && tiltGyro > tiltTrackIndicator) || (tiltTrackIndicator < 0 && tiltGyro < tiltTrackIndicator)) {
        tiltTrackIndicator = limit * (tiltTrackIndicator > 0 ? 1 : -1);
        tiltPowerValue = limit * (tiltTrackIndicator > 0 ? 1 : -1);
        //tiltPowerValue = (tiltPowerValue < limit ? limit : (tiltPowerValue > limit ? limit : tiltPowerValue ));
        printf("new max tilt: %f \n", tiltPowerValue);
    } else {
        tiltPowerValue = lerp(tiltPowerValue, 0, returnSpeed);
    }

    float targetXValue = panPowerValue / limit;
    float targetYValue = tiltPowerValue / limit;

    //printf("Target Values %f %f \n", panPowerValue, tiltPowerValue);

    if(targetYValue > 1){
        targetYValue = 1;
    }else if(targetYValue < -1){
        targetYValue = -1;
    }
    if(targetXValue > 1){
        targetXValue = 1;
    }else if(targetXValue < -1){
        targetXValue = -1;
    }
    //printf("Target Values %f %f \n", targetXValue, targetYValue);

    if(panTrackIndicator != 0) {
        eyeTargetValues->eye_pos.x = lerp(eyeTargetValues->eye_pos.x, targetXValue, getModifier());
    }
    if(tiltTrackIndicator != 0) {
        eyeTargetValues->eye_pos.y = lerp(eyeTargetValues->eye_pos.y, targetYValue, getModifier());
    }
//    eyeTargetValues->pupil_size_factor = lerp(eyeTargetValues->pupil_size_factor, rndPupilSize, getModifier());

}
