#include <unistd.h>

#include "sm.h"

int main(int argc, char **argv)
{
    EventHandler(EV_PRESS_BREAK);
    sleep(1);
    EventHandler(EV_PRESS_GAS);
    sleep(1);
    EventHandler(EV_NOTHING);
    sleep(1);
    EventHandler(EV_PRESS_GAS);
    sleep(1);
    EventHandler(EV_PRESS_BREAK);
    sleep(1);
    EventHandler(EV_PRESS_GAS);
    sleep(1);
    EventHandler(EV_NOTHING);
    sleep(1);
    EventHandler(EV_PRESS_BREAK);
    sleep(1);
    EventHandler(EV_PRESS_BREAK);
    sleep(1);

    return 0;
}