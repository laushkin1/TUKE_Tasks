#include <karel.h>

void turn_right();
void step_with_beeper_checking();
int check_ballot();
void clear_ballot();

int main()
{
    turn_on("ballot.kw");
    set_step_delay(300);
    int i;
    for (i = 0; i < 3; i++)
    {
        check_ballot();
    }

    turn_off();
    return 0;
}

void turn_right()
{
    turn_left();
    turn_left();
    turn_left();
}

void step_with_beeper_checking(int s)
{
    int i;
    for (i = 0; i < s; i++)
    {
        step();
        while (beepers_present())
        {
            pick_beeper();
        }
    }
}

void clear_ballot()
{
    step_with_beeper_checking(1);
    if (front_is_clear())
    {
        step_with_beeper_checking(1);
        turn_left();
        turn_left();
        step();
        if (facing_north())
        {
            turn_right();
        }
        else
        {
            turn_left();
        }
        step();
    }
    else
    {
        turn_left();
        turn_left();
        step();
        step_with_beeper_checking(1);
        turn_left();
        turn_left();
        step();
        turn_right();
        step();
    }
}

int check_ballot()
{
    step();
    turn_left();
    if(!beepers_present())
    {
        clear_ballot();
        return 0;
    }
    step();
    turn_left();
    turn_left();
    if(!beepers_present())
    {
        clear_ballot();
        return 0;
    }
    step();
    step();
    turn_left();
    turn_left();
    if (!beepers_present())
    {
        clear_ballot();
        return 0;
    }
    step();
    turn_right();
    step();
    return 0;
}
