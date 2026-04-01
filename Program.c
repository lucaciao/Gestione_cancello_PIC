#include<p18f4520.h>
#include"header.h"
#include <timers.h>
//--------------------------------------------------------------------------------------------
//variabili globali
bool volatile Check_action=true;
int Time_Open_Closed_Gate =0;
int Time_Wait_Gate_To_Close=0;
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
    //4.000.000 / 4= 1.000.000 no prescaler = 50.000 50ms interrupt
    //configura TIMER0 (16 bit, interrupt enabled)
    OpenTimer0 (TIMER_INT_ON & T0_16BIT & T0_SOURCE_INT & T0_PS_1_16);
    WriteTimer0 (START_VALUE_TIMER);
    
    while (Check_action)
    {
        switch (state)
        {
        case CLOSED:
            LIGHT= false;
            MOTOR_CLOSE = false;
            if (OPEN_COMMAND == true) {
                state = OPENING;
            }
            break;

        case OPENING:
            LIGHT= true;
            MOTOR_OPEN = true;
            Time_Open_Closed_Gate++;
            if (Time_Open_Closed_Gate == MAX_TIME_OPEN_CLOSED_GATE) {
                Time_Open_Closed_Gate = 0;
                state=OPEN_GATE;
            }
            break;

        case OPEN_GATE:
            LIGHT= false;
            MOTOR_OPEN = false;
            Time_Wait_Gate_To_Close++;
            if (Time_Wait_Gate_To_Close == MAX_TIME_WAIT_GATE_TO_CLOSE) {
                Time_Wait_Gate_To_Close = 0;
                state=CLOSING;
            }
            break;
        case CLOSING:
            LIGHT= true;
            MOTOR_CLOSE = true;
            if (OBSTACLE_DETECTED == true) {
                state = OBSTACOLE;
                break; //CHIEDERE AL PROF
             }
            if (OPEN_COMMAND == true) {
                state = OPENING;
                break; //CHIEDERE AL PROF
            }
            Time_Open_Closed_Gate++;
            if (Time_Open_Closed_Gate == MAX_TIME_OPEN_CLOSED_GATE) {
                Time_Open_Closed_Gate = 0;
                state=CLOSED;
            }
            break;
        case OBSTACLE:
            LIGHT=true;
            MOTOR_CLOSE=false;
            if (OBSTACLE_DETECTED == false) {
                state = OPENING;
            }
        break;
    }
    Check_action=false;
}

#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh (void)
{
    _asm
        goto InterruptHandlerHigh
    _endasm
}

#pragma code
#pragma interrupt InterruptVectorHigh


void InterruptHandlerHigh ()
{
    if (INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF=0;
        WriteTimer0(START_VALUE_TIMER);
        Check_action=true;
    }
}
