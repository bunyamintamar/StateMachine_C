#ifndef sm_H
#define sm_H

/**************************** States ******************************************/
enum states
{
    ST_LOW_SPEED,
    ST_MIDDLE_SPEED,
    ST_HIGH_SPEED,
    MAX_STATES
};
/******************************************************************************/

/**************************** Events ******************************************/
enum events
{
    EV_PRESS_BREAK,
    EV_NOTHING,
    EV_PRESS_GAS,
    MAX_EVENTS
};
/******************************************************************************/

/**************************** Actions *****************************************/
void ACT_low_speed_press_break(void);
void ACT_low_speed_nothing(void);
void ACT_low_speed_press_gas(void);
void ACT_middle_speed_press_break(void);
void ACT_middle_speed_nothing(void);
void ACT_middle_speed_press_gas(void);
void ACT_high_speed_press_break(void);
void ACT_high_speed_nothing(void);
void ACT_high_speed_press_gas(void);
/******************************************************************************/

/**************************** Event Handler ***********************************/
void EventHandler(enum events ev);
/******************************************************************************/

/**************************** Others ******************************************/
void printTransition(enum states old_state, enum states new_state);
/******************************************************************************/
#endif /* sm_H */