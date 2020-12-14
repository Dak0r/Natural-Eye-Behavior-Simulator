//
// Created by dakor on 12/14/20.
//

#ifndef CYBORG_1_5_OLED_EYE_RASPBERRYPI_EYEMODIFIER_H
#define CYBORG_1_5_OLED_EYE_RASPBERRYPI_EYEMODIFIER_H

#include "EyeStatus.h"
#include "EyeConfig.h"
#include <string>
using namespace std;

namespace EyeBehavior {
    class EyeModifier {
    public:
        virtual string getName() = 0;

        virtual void init(unsigned long now, float modifier) = 0;

        virtual void update(unsigned long now, EyeConfig* current_eye_config, EyeStatus* eyeTargetValues, EyeStatus* eyeCurrentValues) = 0;

        void setModifier(float modifier) {
            this->modifier = modifier;
        }
        float getModifier() {
            return modifier;
        }

    protected:
        unsigned long now = 0;
    private:
        float modifier = 1;

    };
}

#endif //CYBORG_1_5_OLED_EYE_RASPBERRYPI_EYEMODIFIER_H
