#include <karel.h>

void turn_right();
void step_with_beeper_checking();
void pass_square_left();
void pass_square_right();

int main()
{
    turn_on("stairs4.kw");
    set_step_delay(200);
    step();
    turn_right();
    step_with_beeper_checking(2);
    turn_right();
    pass_square_left();
    step();
    turn_left();
    step_with_beeper_checking(5);
    pass_square_right();
    step_with_beeper_checking(4);
    pass_square_left();
    step_with_beeper_checking(4);
    pass_square_right();
    step_with_beeper_checking(5);
    turn_left();
    step_with_beeper_checking(1);
    turn_left();
    step_with_beeper_checking(4);
    pass_square_right();
    step();
    while(beepers_in_bag())
    {
        put_beeper();
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

void pass_square_left()
{
    step_with_beeper_checking(1);
    turn_left();
    step_with_beeper_checking(2);
    turn_left();
    step_with_beeper_checking(1);
}

void pass_square_right()
{
    step_with_beeper_checking(1);
    turn_right();
    step_with_beeper_checking(2);
    turn_right();
    step_with_beeper_checking(1);
}
