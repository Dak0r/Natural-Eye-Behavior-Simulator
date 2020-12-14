//
// Created by dakor on 12/14/20.
//

#ifndef CYBORG_1_5_OLED_EYE_RASPBERRYPI_RANDOMLOOKMODIFIER_H
#define CYBORG_1_5_OLED_EYE_RASPBERRYPI_RANDOMLOOKMODIFIER_H


#include "../EyeModifier.h"

namespace EyeBehavior {
    class RandomLookModifier : public EyeModifier {
    public:
        string getName();

        void init(unsigned long now, float modifier);

        void update(unsigned long now, EyeConfig* current_eye_config, EyeStatus* eyeTargetValues, EyeStatus* eyeCurrentValues);


    private:
        unsigned long time_last_random_pos = 0;
        float time_next_random_pos = 0;
    };
}


#endif //CYBORG_1_5_OLED_EYE_RASPBERRYPI_RANDOMLOOKMODIFIER_H
