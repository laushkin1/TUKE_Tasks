#include <karel.h>

void put_beeper_in_corner();

int main()
{
    turn_on("marker.kw");
    // turn_on("marker2.kw");
    set_step_delay(200);
    int i;
    for (i = 0; i < 4; i++)
    {
        put_beeper_in_corner();
    }
    step();
    turn_off();
    return 0;
}

void put_beeper_in_corner()
{
    while (front_is_clear())
    {
        step();
    }
    if(beepers_present())
    {
        turn_left();
    }
    else
    {
        put_beeper();
        turn_left();
    }
}
