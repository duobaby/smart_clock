#ifndef __DELAY_H_
#define __DELAY_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

class Delay {
private:

public:
    void init(void) {
        HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
        /* Configure the SysTick to have interrupt in 1ms time basis*/
        HAL_SYSTICK_Config(SystemCoreClock / (1000U / uwTickFreq));
    }
    void us(uint32_t nus);
    void ms(uint32_t nms);
};
extern Delay delay;
#ifdef __cplusplus
}
#endif


#endif // !__DELAY_H_
