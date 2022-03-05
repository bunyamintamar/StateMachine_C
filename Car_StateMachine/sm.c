#include "sm.h"
#include <stdio.h>

/**************************** Global Variables ********************************/
enum states current_state = ST_LOW_SPEED;
/******************************************************************************/

/**************************** Actions *****************************************/
void ACT_low_speed_press_break(void)
{
    enum states old_state = current_state;
    current_state = ST_LOW_SPEED;

    printTransition(old_state, current_state);
}

void ACT_low_speed_nothing(void)
{
    enum states old_state = current_state;
    current_state = ST_LOW_SPEED;

    printTransition(old_state, current_state);
}

void ACT_low_speed_press_gas(void)
{
    enum states old_state = current_state;
    current_state = ST_MIDDLE_SPEED;

    printTransition(old_state, current_state);
}

void ACT_middle_speed_press_break(void)
{
    enum states old_state = current_state;
    current_state = ST_LOW_SPEED;

    printTransition(old_state, current_state);
}

void ACT_middle_speed_nothing(void)
{
    enum states old_state = current_state;
    current_state = ST_MIDDLE_SPEED;

    printTransition(old_state, current_state);
}

void ACT_middle_speed_press_gas(void)
{
    enum states old_state = current_state;
    current_state = ST_HIGH_SPEED;

    printTransition(old_state, current_state);
}

void ACT_high_speed_press_break(void)
{
    enum states old_state = current_state;
    current_state = ST_MIDDLE_SPEED;

    printTransition(old_state, current_state);
}

void ACT_high_speed_nothing(void)
{
    enum states old_state = current_state;
    current_state = ST_HIGH_SPEED;

    printTransition(old_state, current_state);
}

void ACT_high_speed_press_gas(void)
{
    enum states old_state = current_state;
    current_state = ST_HIGH_SPEED;

    printTransition(old_state, current_state);
}

/******************************************************************************/

/**************************** State/Event Table *******************************/
void (*StateTable[MAX_STATES][MAX_EVENTS])(void) =
{
    {ACT_low_speed_press_break,     ACT_low_speed_nothing,     ACT_low_speed_press_gas},
    {ACT_middle_speed_press_break,  ACT_middle_speed_nothing,  ACT_middle_speed_press_gas},
    {ACT_high_speed_press_break,    ACT_high_speed_nothing,    ACT_high_speed_press_gas}
};
/******************************************************************************/

/**************************** Event Handler ***********************************/
void EventHandler(enum events ev)
{
    printf("\n\n%s", (ev == 0 ? "BREAK !!!" : (ev == 1 ? "NOT PRESSING !!!" : "GAS !!!")));
    (*StateTable[current_state][ev])();
}
/******************************************************************************/

/**************************** Others ******************************************/
void printTransition(enum states old_state, enum states new_state)
{
    printf("\n%s -> %s\n", (old_state == 0 ? "ST_LOW_SPEED" : (old_state == 1 ? "ST_MIDDLE_SPEED" : "ST_HIGH_SPEED")),
                           (new_state == 0 ? "ST_LOW_SPEED" : (new_state == 1 ? "ST_MIDDLE_SPEED" : "ST_HIGH_SPEED")));
}
/******************************************************************************/