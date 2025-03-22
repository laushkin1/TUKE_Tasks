#include <superkarel.h>
#define SPEED 300

void turn_right();
void turn_back();
void put_beeper_in_pit();

int main() {
//    turn_on("road.kw"); // 25
    turn_on("road2.kw"); // 49
    set_step_delay(SPEED);
    while (true) {
        if(front_is_blocked()){
            break;
        }
        while (right_is_blocked() && front_is_clear()){
            step();
        }
        put_beeper_in_pit();
    }
    turn_off();
    return 0;
}

void turn_right(){
    set_step_delay(0);
    turn_left();
    turn_left();
    turn_left();
    set_step_delay(SPEED);
}
void turn_back(){
    set_step_delay(0);
    turn_left();
    turn_left();
    set_step_delay(SPEED);
}

void put_beeper_in_pit(){
    turn_right();
    do{
        step();
    } while (front_is_clear());
    if(no_beepers_present()){
        put_beeper();
    }
    turn_back();
    do{
        step();
    } while (right_is_blocked() && front_is_clear());
    turn_right();
    if(front_is_clear()){
        step();
    }
}