#include<p18f4520.h>
#include"header.h"
#include <timers.h>
//--------------------------------------------------------------------------------------------
//variabili globali
int Time_Open_Closed_Gate =0;
int Time_Wait_Gait_To_Close=0:
//prototipi
void InterruptHandlerHigh (void);
//--------------------------------------------------------------------------------------------
//main
void main (void)
{
    int state = CLOSED;
    //configura porte utilizzate (A,B)
    TRISA = PORTA_TRIS;
    PORTA = PORTA_DEFAULT;

    
    //supponiamo un oscillatore a 4Mzh
    //4.000.000 / 4= 1.000.000 /16 prescaler = 62.500
    //configura TIMER0 (16 bit, interrupt enabled)
    Opentimer0 (TIMER_INT_ON & T0_16BIT & T0_SOURCE_INT & T0_DEGE_FALL & T0_PS_1_2); //da cambiare
    WriteTimer0 (TIMER0_VALUE_100ms);
    while (1)
    {
        switch (state)
        {
        case CLOSED:
            if (OPEN_COMMAND == true) {

                state = OPENING;
                MOTOR_OPEN = true;
                LIGHT= true;
            }
            break;

        case OPENING:
            if (OBSTACLE_DETECTED == true) {
                state = WAIT;
                LIGHT= true;
                MOTOR_OPEN = false;
                break; //CHIEDERE AL PROF
            }
            Time_Open_Closed_Gate++;
            if (Time_Open_Closed_Gate = Max_Time_Open_Closed_Gate) {
                Time_Open_Closed_Gate = 0;
                state=OPEN_GATE;
            }
            break;

        case OPEN_GATE:
            LIGHT= false;
            MOTOR_OPEN = false;
            Time_Wait_Gait_To_Close++;
            if (Time_Wait_Gait_To_Close = MAX_TIME_WAIT_GATE_TO_CLOSE) {
                Time_Wait_Gait_To_Close = 0;
                state=CLOSING;
            }
            break;
        case OPENING:
            if (OBSTACLE_DETECTED == true) {
                state = WAIT;
                LIGHT= true;
                MOTOR_OPEN = false;
                break; //CHIEDERE AL PROF
             }
            Time_Open_Closed_Gate++;
            if (Time_Open_Closed_Gate = Max_Time_Open_Closed_Gate) {
                Time_Open_Closed_Gate = 0;
                state=OPEN_GATE;
            }
            break;
    }
}

#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh (void)
{
    _asm
    goto InterruptVectorHigh
    _endasm
}

#pragma code
#pragma interrupt InterruptVectorHigh

void InterruptVectorHigh ()
{
    if (INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF=0;
        WriteTimer0(TIMER0_VALUE_100ms);
        if (ContaTempo_ds > 0)
        {
            Check_action=true;
        }
    }
}
