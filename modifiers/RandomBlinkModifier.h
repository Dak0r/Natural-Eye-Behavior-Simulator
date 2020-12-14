//
// Created by dakor on 12/14/20.
//

#ifndef CYBORG_1_5_OLED_EYE_RASPBERRYPI_RANDOMBLINKMODIFIER_H
#define CYBORG_1_5_OLED_EYE_RASPBERRYPI_RANDOMBLINKMODIFIER_H

#include "../EyeModifier.h"

namespace EyeBehavior {
    class RandomBlinkModifier : public EyeModifier {
    public:
        string getName();

        void init(unsigned long now, float modifier);

        void update(unsigned long now, EyeConfig* eyeConfig, EyeStatus* eyeTargetValues, EyeStatus* eyeCurrentValues);


    private:
        unsigned long blink_time_last_ = 0.0;
        unsigned long blink_time_next_ = 1.0;

        int   c1urrent_blink_state_ = 0; // 0 = opend, 1 = idle, 2= closing, 3 = closed, 4 = opening
        float current_blink_duration_ = 0.1;
        unsigned long current_blink_time_start_ = 0;
        float current_blink_progress_ = 0;
        bool first_update = true;
    };
}



#endif //CYBORG_1_5_OLED_EYE_RASPBERRYPI_RANDOMBLINKMODIFIER_H
