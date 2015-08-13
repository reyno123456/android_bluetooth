#ifndef _PWM_H_
#define _PWM_H_

#include "hal_types.h"


// �в��ɸı�����ö�ٶ����Լ�λ�ã� ���ܸĶ�
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
pwm_p11 ��ʾp1.1 ���pwm�ź�ռ�ձȣ� ע�����ռ�ձ��������  0xff��ռ�ձ�
pwm_p10 ��ʾp1.0 ���pwm�ź�ռ�ձȣ� ע�����ռ�ձ��������  0xff��ռ�ձ�
pwm_p07 ��ʾp0.7 ���pwm�ź�ռ�ձȣ� ע�����ռ�ձ��������  0xff��ռ�ձ�
pwm_p06 ��ʾp0.6 ���pwm�ź�ռ�ձȣ� ע�����ռ�ձ��������  0xff��ռ�ձ�
*/
// �ú�����ʼ����������pwm����� ��ִ�� ti_pwm_set_period ָ���˿ں� ��������
void ti_pwm_init(uint16 freq, uint8 pwm_p11, uint8 pwm_p10, uint8 pwm_p07, uint8 pwm_p06);
void ti_pwm_deinit();  //�ر�pwm
void ti_pwm_set_period(PWM_INDEX index, uint8 pwm_period, uint16 changeTime_ms);

#endif
