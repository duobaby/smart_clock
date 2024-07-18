#include "pwm.h"


TIM_HandleTypeDef htim2;
pwm_dev lcd_bl_pwm(TIM2, TIM_CHANNEL_1, lcd_bl, &htim2);
void pwm_dev::init() {

    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    tim_handle->Instance = tim;
    tim_handle->Init.Prescaler = (clock_max/frequent);
    tim_handle->Init.CounterMode = TIM_COUNTERMODE_UP;
    tim_handle->Init.Period = pwm_max - 1;
    tim_handle->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    tim_handle->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(tim_handle) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(tim_handle, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(tim_handle, &sConfigOC, channel) != HAL_OK)
    {
        Error_Handler();
    }
}

void pwm_dev::set_duty(uint8_t duty) {
    __HAL_TIM_SET_COMPARE(tim_handle, channel, duty);
}

