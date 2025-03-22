#include <superkarel.h>
#define SPEED 300

void turn_right();
void turn_back();
void mirror_beepers();

int main(){
//    turn_on("mirror.kw"); // 207
    turn_on("mirror2.kw");
    set_step_delay(SPEED);
    mirror_beepers();
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

void mirror_beepers(){
    while (1) {

        while (no_beepers_present()) {
            step();
        }

        do {
            pick_beeper();
        } while (beepers_present());

        turn_left();
        step();
        turn_right();

        while (front_is_clear()) {
            step();
        }

        if (no_beepers_present()) {
            do {
                put_beeper();
            } while (beepers_in_bag());
            turn_back();
        } else {
            turn_back();
            do {
                step();
            } while (beepers_present());
            do {
                put_beeper();
            } while (beepers_in_bag());
        }

        if (front_is_clear()) {
            while (front_is_clear()) {
                step();
            }
        } else { break; } // err

        turn_left();
        step();
        turn_left();
    }


}