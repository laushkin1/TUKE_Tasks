#include <karel.h>

void turn_right();

void move()
{
    while(beepers_present()){
        pick_beeper();
    }
    turn_left();
    step();
    turn_right();
    if(front_is_clear()){
        step();
    }
    else{
        move();
    }
}

int main()
{
    turn_on("stairs.kw");
    // turn_on("stairs2.kw");
    // turn_on("stairs3.kw"); 
    set_step_delay(200);

    step();
    move();
    while(true){
        if (!front_is_clear()){
        move();
        }
        else{
            while(beepers_in_bag())
            {
                put_beeper();
            }
            break;
        }
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

