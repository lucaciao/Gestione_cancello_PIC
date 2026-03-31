#ifndef __TIMER_INTERRUPT
#define __TIMER_INTERRUPT

//input line
#define OPEN_COMMAND PORTAbits.RA1
#define OBSTACLE_DETECTED PORTAbits.RA2

//output line
#define LIGHT PORTAbits.RA3
#define MOTOR_OPEN PORTAbits.RA4
#define MOTOR_CLOSE PORTAbits.RA5

#define PORTA_TRIS 0b11000000
#define PORTA_DEFAULT 0b00000000

#define CLOSED 0
#define OPENING 1
#define OPEN_GATE 2
#define CLOSING 3
#define CLOSED_GATE 4
#define WAIT 5

#define Max_Time_Open_Closed_Gate 10
#define MAX_TIME_WAIT_GATE_TO_CLOSE 30

#define START_VALUE_TIMER 3.035


#endif
