#ifndef __PWM_H_
#define __PWM_H_


#include "main.h"

/**
 * @brief 所用hz
 * 
 */
#define lcd_bl 1000
#define pwm_max 100
#define clock_max 50000000
class pwm_dev {
private:
    TIM_TypeDef *tim;
    uint32_t channel;
    uint32_t frequent;
    TIM_HandleTypeDef *tim_handle;
public:
    pwm_dev(TIM_TypeDef *tim,uint32_t channel,uint32_t frequent,TIM_HandleTypeDef *tim_handle)
    : tim(tim),channel(channel),frequent(frequent), tim_handle(tim_handle) {}
    void init();
    void set_duty(uint8_t duty);
};

extern pwm_dev lcd_bl_pwm;
#endif // !__PWM_H_
