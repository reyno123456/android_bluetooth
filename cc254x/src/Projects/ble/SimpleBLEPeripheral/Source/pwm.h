#ifndef _PWM_H_
#define _PWM_H_

#include "hal_types.h"


// 切不可改变以下枚举定义以及位置， 不能改动
typedef enum
{
    PWM1_P11 = 0,
    PWM2_P10 = 1,
    PWM3_P07 = 2,
    PWM4_P06 = 3,
//    PWM0_COMM = 4, 
    PWM_MAX,
}PWM_INDEX;


/*
pwm_p11 表示p1.1 输出pwm信号占空比， 注意这个占空比是相对于  0xff的占空比
pwm_p10 表示p1.0 输出pwm信号占空比， 注意这个占空比是相对于  0xff的占空比
pwm_p07 表示p0.7 输出pwm信号占空比， 注意这个占空比是相对于  0xff的占空比
pwm_p06 表示p0.6 输出pwm信号占空比， 注意这个占空比是相对于  0xff的占空比
*/
// 该函数初始化但不会有pwm输出， 当执行 ti_pwm_set_period 指定端口后 后才有输出
void ti_pwm_init(uint16 freq, uint8 pwm_p11, uint8 pwm_p10, uint8 pwm_p07, uint8 pwm_p06);
void ti_pwm_deinit();  //关闭pwm
void ti_pwm_set_period(PWM_INDEX index, uint8 pwm_period, uint16 changeTime_ms);

#endif
