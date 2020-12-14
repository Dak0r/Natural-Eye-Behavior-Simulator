//
// Created by dakor on 12/14/20.
//

#ifndef CYBORG_1_5_OLED_EYE_RASPBERRYPI_GYROAFFECTEDLOOKMODIFIER_H
#define CYBORG_1_5_OLED_EYE_RASPBERRYPI_GYROAFFECTEDLOOKMODIFIER_H

#include "../EyeModifier.h"

namespace EyeBehavior {
    class GyroAffectedLookModifier : public EyeModifier {
    public:
        string getName();

        void init(unsigned long now, float modifier);

        void update(unsigned long now, EyeConfig* current_eye_config, HeadStatus* headStatus, EyeStatus* eyeTargetValues, EyeStatus* eyeCurrentValues);


    private:
        float panTrackIndicator = 0;
        float tiltTrackIndicator = 0;
        float panPowerValue = 0;
        float tiltPowerValue = 0;
        float threshshold = 10;
        float limit = 35;
        float returnSpeed = 0.05f;
    };
}


#endif //CYBORG_1_5_OLED_EYE_RASPBERRYPI_GYROAFFECTEDLOOKMODIFIER_H
