
#include "pwm.h"
#include "hal_lcd.h"
#include "OSAL_Timers.h"


//#define SHOW_VAL(string, value)  {HalLcdWriteStringValue(string, value, 10,  HAL_LCD_LINE_8 );  P0SEL |= 0x0c; osal_start_timerEx( simpleBLEPeripheral_TaskID, SBP_UART_EVT, 500 );}
     

#define MY_ABS(x, y)   (x > y ? x-y : y-x)     // 求两数差值

/******************************************************************************/

                  

#define DEFAULT_FREQ    100

static uint16 g_freq = DEFAULT_FREQ;       // 默认频率
static uint8 g_freq_div = 128;
static uint16 g_freq_period = 5000;

static uint16 g_PERIOD[PWM_MAX]  = {0}; 
static uint16 g_PERIOD_new[PWM_MAX]  = {0}; 
static uint16 g_PERIOD_step[PWM_MAX]  = {1}; 
static uint16 g_PERIOD_skip[PWM_MAX]  = {1}; // 跳过的不调整占空比的中断数
static uint16 g_PERIOD_skip_new[PWM_MAX]  = {0}; // 跳过的不调整占空比的中断数
//static uint8  g_gpio_status[PWM_MAX]  = {0};     // 设置为1时表示使用gpio输出模式

void CalPara(uint16 freq, uint8 pwm_p11, uint8 pwm_p10, uint8 pwm_p07, uint8 pwm_p06)
{
    if(g_freq <= 100)
    {
        g_freq = freq;
        g_freq_div = 128;
        g_freq_period = 32000000L / g_freq_div / g_freq;
    }
    else if(g_freq <= 300)
    {
        g_freq = freq;
        g_freq_div = 32;
        g_freq_period = 32000000L / g_freq_div / g_freq;
    }
    else        
    {
        g_freq = freq;
        g_freq_div = 1;
        g_freq_period = 32000000L / g_freq_div / g_freq;
    }

    {        
        uint32 freq_period = g_freq_period;
//        g_PERIOD_new[PWM0_COMM] = g_PERIOD[PWM0_COMM] = g_freq_period;
        g_PERIOD_new[PWM1_P11] = g_PERIOD[PWM1_P11] = freq_period*(255-pwm_p11)/255;
        g_PERIOD_new[PWM2_P10] = g_PERIOD[PWM2_P10] = freq_period*(255-pwm_p10)/255;
        g_PERIOD_new[PWM3_P07] = g_PERIOD[PWM3_P07] = freq_period*(255-pwm_p07)/255;
        g_PERIOD_new[PWM4_P06] = g_PERIOD[PWM4_P06] = freq_period*(255-pwm_p06)/255; 


//        g_PERIOD_skip_new[PWM0_COMM] = g_PERIOD_skip[PWM0_COMM] = 0;
        g_PERIOD_skip_new[PWM1_P11] = g_PERIOD_skip[PWM1_P11] = 0;
        g_PERIOD_skip_new[PWM2_P10] = g_PERIOD_skip[PWM2_P10] = 0;
        g_PERIOD_skip_new[PWM3_P07] = g_PERIOD_skip[PWM3_P07] = 0;
        g_PERIOD_skip_new[PWM4_P06] = g_PERIOD_skip[PWM4_P06] = 0;
    }
}

// 该函数初始化但不会有pwm输出， 当执行 ti_pwm_set_period 指定端口后 后才有输出
void ti_pwm_init(uint16 freq, uint8 pwm_p11, uint8 pwm_p10, uint8 pwm_p07, uint8 pwm_p06)
{
    T1IE = 0;

    //设置pwm端口为输出
    P1DIR|= BV(0)|BV(1);
//    //设置pwm端口为外设端口，非gpio
    P1SEL|= BV(0)|BV(1);

//    //设置pwm端口为输出
    P0DIR|= BV(6)|BV(7);
//    //设置pwm端口为外设端口，非gpio
    P0SEL|= BV(6)|BV(7);

    PERCFG |= 0x40;// Select Timer 1 Alternative 2 location   , p88

    // 取反
//    pwm_p11 = 255 - pwm_p11;
//    pwm_p10 = 255 - pwm_p10;
//    pwm_p07 = 255 - pwm_p07;
//    pwm_p06 = 255 - pwm_p06;


    CalPara(freq, pwm_p11, pwm_p10, pwm_p07, pwm_p06);
    
/*
    00: Tick frequency/1
    01: Tick frequency/8
    10: Tick frequency/32
    11: Tick frequency/128
    mode: modulo bit[1:0]=10, div: tick/128 bit[3:2]=11 
*/

    T1CTL &= ~0x0f; 
    if(g_freq_div == 1)         T1CTL |= ((0x00 << 2) | 0x02);            // Timer1 modulo mode, tick div 1
    else if(g_freq_div == 8)    T1CTL |= ((0x01 << 2) | 0x02);            // Timer1 modulo mode, tick div 8
    else if(g_freq_div == 32)   T1CTL |= ((0x02 << 2) | 0x02);            // Timer1 modulo mode, tick div 32
    else if(g_freq_div == 128)  T1CTL |= ((0x03 << 2) | 0x02);            // Timer1 modulo mode, tick div 128    

    T1CC0H = g_freq_period/0xFF;
    T1CC0L = g_freq_period%0xFF;
    
    T1CC1H = g_PERIOD[PWM1_P11]/0xFF;
    T1CC1L = g_PERIOD[PWM1_P11]%0xFF;
    T1CCTL1 = 0x6C; 
//    T1CCTL1 = 0x00; 
    
    T1CC2H = g_PERIOD[PWM2_P10]/0xFF;
    T1CC2L = g_PERIOD[PWM2_P10]%0xFF;
    T1CCTL2 = 0x6C; 
//    T1CCTL2 = 0x00; 
    
    T1CC3H = g_PERIOD[PWM3_P07]/0xFF;
    T1CC3L = g_PERIOD[PWM3_P07]%0xFF;
    T1CCTL3 = 0x6C; 
//    T1CCTL3 = 0x00; 
    
    T1CC4H = g_PERIOD[PWM4_P06]/0xFF;
    T1CC4L = g_PERIOD[PWM4_P06]%0xFF;
    T1CCTL4 = 0x6C; 
//    T1CCTL4 = 0x00; 

//必须设置以下两句，否则定时器不工作， 但是我们这里只用pwm， 因此可以直接用pwm的中断， 不用t1的定时器中断， 因此不用设置
//    T1CCTL0 = 0x4C;            // IM = 1, CMP = Clear output on compare; Mode = Compare
//    IEN1 |= 0x02;               // Enable T1 cpu interrupt    


    T1IE = 1;
    EA = 1;
}
void ti_pwm_deinit()  //关闭pwm
{
#if 1// 关闭pwm    
    T1IE = 0;

    T1CCTL1 = 0; 
    T1CCTL2 = 0; 
    T1CCTL3 = 0; 
    T1CCTL4 = 0;   
    
    P1SEL &= ~(BV(1)); P1_1 = 0;
    P1SEL &= ~(BV(0)); P1_0 = 0;
    P0SEL &= ~(BV(7)); P0_7 = 0;
    P0SEL &= ~(BV(6)); P0_6 = 0;    
#else
    T1CCTL1 = 0x6C; 
    T1CCTL2 = 0x6C; 
    T1CCTL3 = 0x6C; 
    T1CCTL4 = 0x6C; 
#endif

}
/*
index :         pwm 通道号   
                PWM1_P11,
                PWM2_P10,
                PWM3_P07,
                PWM4_P06,
pwm_period:     占空比， 输出pwm信号占空比， 注意这个占空比是相对于  0xff的占空比, 0为全低，1为全高
changeTime_ms:  表示从当前的占空比转到目标占空比(pwm_period) 所需要的时间(ms)
*/

void ti_pwm_set_period(PWM_INDEX index, uint8 pwm_period, uint16 changeTime_ms)
{  
    uint32 freq_period = g_freq_period;    
    uint16 PERIOD = freq_period*(255-pwm_period)/255;
//    SHOW_VAL(">>>index ", index);
//    SHOW_VAL(">>>period ", pwm_period);
//    SHOW_VAL(">>>Time_ms ", changeTime_ms);
//    SHOW_VAL("g_freq_period ", g_freq_period);
//    SHOW_VAL("PERIOD ", PERIOD);

    if(index < PWM_MAX)
    {
        //设置pwm端口为输出
        if(PWM1_P11 == index)
        {                
            P1SEL |= BV(1);
            T1CCTL1 = 0x6C; 
        }
        else if(PWM2_P10 == index)
        {
            P1SEL |= BV(0); 
            T1CCTL2 = 0x6C; 
        }
        else if(PWM3_P07 == index) 
        {
            P0SEL |= BV(7); 
            T1CCTL3 = 0x6C; 
        }            
        else if(PWM4_P06 == index) 
        {
            P0SEL |= BV(6); 
            T1CCTL3 = 0x6C; 
        }           
        
        if(g_PERIOD[index] == g_freq_period)
        {    
            g_PERIOD[index] = g_freq_period-1;     
        }
        else if(g_PERIOD[index] == 0)
        {
            g_PERIOD[index] = 1;   
        }
        
        g_PERIOD_new[index] = PERIOD;
//        SHOW_VAL("index ", index);
//        SHOW_VAL("g_PERIOD_new[index] ", g_PERIOD_new[index]);
//        SHOW_VAL("g_PERIOD[index] ", g_PERIOD[index]);

        if(g_PERIOD_new[index] != g_PERIOD[index])
        {
           uint16 step = MY_ABS(g_PERIOD[index], g_PERIOD_new[index]); // 该段时间内需要走的总步长

#if 0
           //uint32 interrupt_num = ((uint32)g_freq*changeTime_ms)/1000;   //该段时间内的总共中断个数
#else
           //该段时间内的总共中断个数 
           uint32 interrupt_num = g_freq;
           interrupt_num *= changeTime_ms;
           interrupt_num /= 1000;
#endif
           
//           SHOW_VAL("g_freq ", g_freq);
//           SHOW_VAL("step ", step);
//           SHOW_VAL("num ", (uint16)interrupt_num);
           
           if(step == 0)
                step = 1;
           if(interrupt_num == 0)
                interrupt_num = 1;

           if(step >= interrupt_num)
           {
//count :  0
//index  0
//g_PERIOD_new[index]  0
//g_PERIOD[index]  4999
//g_freq  50
//step  4999
//interrupt_num  1000
                g_PERIOD_step[index] = step/interrupt_num;
                // 加上以下一句是避免调整的过慢
                if(step%interrupt_num > 0)
                    g_PERIOD_step[index]++;
                
                g_PERIOD_skip[index] = 0;
           }
           else
           {
//key :  1
//count :  1
//index  0
//g_PERIOD_new[index]  5000
//g_PERIOD[index]  4805
//g_freq  50
//step  195
//interrupt_num  200
//key :  0            
                g_PERIOD_step[index] = 1;
                g_PERIOD_skip[index] = interrupt_num/step;
                // 加上以下一句是避免调整的过慢
                if(g_PERIOD_skip[index] > 0)
                    g_PERIOD_skip[index]--;
           }
           
           g_PERIOD_skip_new[index] = 0;

//           g_PERIOD_step[PWM3_P07] = 10;
            
//           SHOW_VAL("indexA ", index);
//           SHOW_VAL("step1 ", g_PERIOD_step[index]);
//           SHOW_VAL("skip1 ", g_PERIOD_skip[index]);
//           SHOW_VAL("skip2 ", g_PERIOD_skip_new[index]);

        }
    }
}

uint16 pwm_int_count = 0;
//uint16 pwm0_int_count = 0;
//uint16 pwm1_int_count = 0;
//uint16 pwm2_int_count = 0;
//uint16 pwm3_int_count = 0;
//uint16 pwm4_int_count = 0;
#pragma vector = T1_VECTOR
__interrupt void Timer1_ISR(void)
{
    uint8 flags = T1STAT;
    
//    if (flags & 0x01)
    {      
        //if (flags & 0x01)
//        pwm0_int_count++;
        
        pwm_int_count++;
        
        for(PWM_INDEX i = PWM1_P11; i<PWM_MAX ; i++)
        {            
            if((i == PWM1_P11))
            {
                if(!(flags & 0x02))  
                    continue;
            }
            else if((i == PWM2_P10))
            {
                if(!(flags & 0x04))  
                    continue;
            }
            else if((i == PWM3_P07))
            {
                if(!(flags & 0x08))  
                    continue;
            }
            else if((i == PWM4_P06))
            {
                if(!(flags & 0x10))  
                    continue;
            }
            else
            {
                continue;
            }

//              g_PERIOD_new[i]+= 10*(i+1);
//              if(g_PERIOD_new[i] > 5000)
//                g_PERIOD_new[i] = 0;
//              g_PERIOD[i] = g_PERIOD_new[i];
              
            if(g_PERIOD_new[i] != g_PERIOD[i])
            {
                if(g_PERIOD_skip_new[i]++ >= g_PERIOD_skip[i])
                {
                    g_PERIOD_skip_new[i] = 0;
                    
                    if(g_PERIOD_new[i] + g_PERIOD_step[i] < g_PERIOD[i])
                    {
                        g_PERIOD[i] -= g_PERIOD_step[i];  
                        if(g_PERIOD[i] < g_PERIOD_new[i])
                            g_PERIOD[i] = g_PERIOD_new[i];
                    }
                    else 
                    {
                        g_PERIOD[i] += g_PERIOD_step[i];  
                        if(g_PERIOD[i] > g_PERIOD_new[i])
                            g_PERIOD[i] = g_PERIOD_new[i];
                    }
                }
            }

            if(g_PERIOD[i] == g_freq_period)// 全低输出
            {
                //设置pwm端口为输出
                if(PWM1_P11 == i) {  P1SEL &= ~(BV(1)); P1_1 = 0; }
                else if(PWM2_P10 == i) {  P1SEL &= ~(BV(0)); P1_0 = 0; }
                else if(PWM3_P07 == i) {  P0SEL &= ~(BV(7)); P0_7 = 0; }
                else if(PWM4_P06 == i) {  P0SEL &= ~(BV(6)); P0_6 = 0; }
            }
            else if(g_PERIOD[i] == 0)// 全高输出
            {
                //设置pwm端口为输出
                if(PWM1_P11 == i) {  P1SEL &= ~(BV(1)); P1_1 = 1; }
                else if(PWM2_P10 == i) {  P1SEL &= ~(BV(0)); P1_0 = 1; }
                else if(PWM3_P07 == i) {  P0SEL &= ~(BV(7)); P0_7 = 1; }
                else if(PWM4_P06 == i) {  P0SEL &= ~(BV(6)); P0_6 = 1; }
            }
            else
            {
                if(PWM1_P11 == i) 
                { 
                    T1CC1H = g_PERIOD[i]/0xFF;
                    T1CC1L = g_PERIOD[i]%0xFF;
                }
                else if(PWM2_P10 == i)
                { 
                    T1CC2H = g_PERIOD[i]/0xFF;
                    T1CC2L = g_PERIOD[i]%0xFF;
                }
                else if(PWM3_P07 == i)
                { 
                    T1CC3H = g_PERIOD[i]/0xFF;
                    T1CC3L = g_PERIOD[i]%0xFF;
                }                        
                else if(PWM4_P06 == i)
                { 
                    T1CC4H = g_PERIOD[i]/0xFF;
                    T1CC4L = g_PERIOD[i]%0xFF;
                }
            }
        }        

//        T1CC0H = g_PERIOD[0]/0xFF;
//        T1CC0L = g_PERIOD[0]%0xFF;

//        T1CC1H = g_PERIOD[0]/0xFF;
//        T1CC1L = g_PERIOD[0]%0xFF;
//        
//        T1CC2H = g_PERIOD[1]/0xFF;
//        T1CC2L = g_PERIOD[1]%0xFF;
//        
//        T1CC3H = g_PERIOD[2]/0xFF;
//        T1CC3L = g_PERIOD[2]%0xFF;
//        
//        T1CC4H = g_PERIOD[3]/0xFF;
//        T1CC4L = g_PERIOD[3]%0xFF;   

//        T1STAT &= ~0x02;

        // Reset timer
//        T1CNTL = 0;


        // Start timer in modulo mode.
        //T1CTL |= 0x02;   

        T1STAT = ~flags;
    }
}

