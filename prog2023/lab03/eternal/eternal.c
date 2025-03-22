#include <superkarel.h>
#define SPEED 100
//void run_mile();
//void turn_around();

int main()
{
    turn_on("empty.kw");
    set_step_delay(SPEED);

    while (!facing_north()){
        turn_left();
    }
    while (front_is_clear()){
        step();
        if(!front_is_clear())
        {
            set_step_delay(0);
            turn_left();
            turn_left();
            set_step_delay(SPEED);
        }
    }
    turn_off();

    return 0;
}

