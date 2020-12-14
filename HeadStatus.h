//
// Created by dakor on 12/14/20.
//

#ifndef CYBORG_1_5_OLED_EYE_RASPBERRYPI_HEADSTATUS_H
#define CYBORG_1_5_OLED_EYE_RASPBERRYPI_HEADSTATUS_H


namespace EyeBehavior {

    class HeadStatus {
    public:
        enum HeadMode {HEAD_MODE_NONE, HEAD_MODE_ABSOLUTE, HEAD_MODE_GYRO};
        HeadMode head_mode;
        float head_rotation[3];
        float head_rotation_reference[3];
        float head_gyro[3];

    };

} // namespace EyeBehavior


#endif //CYBORG_1_5_OLED_EYE_RASPBERRYPI_HEADSTATUS_H
