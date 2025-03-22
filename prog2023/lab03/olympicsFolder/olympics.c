#include <superkarel.h>
#define SPEED 100

void jump_over();
void turn_right();

int main(){
//    turn_on("training.kw"); // 44
//    turn_on("olympics.kw"); // 46
//    turn_on("olympics2.kw"); // 45
//    turn_on("olympics3.kw"); // 76
//    turn_on("olympics4.kw"); // 54
    turn_on("olympics5.kw"); // 67
//    turn_on("olympics6.kw"); // 51
    set_step_delay(SPEED);

    while (no_beepers_present()){
        if(front_is_blocked()) {
            jump_over();
        } else{step();}
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

void jump_over(){
    if (facing_east()){
        turn_left();

        do{
            step();
        } while (right_is_blocked());

        turn_right();

        do {
            step();
        } while (right_is_blocked());

        turn_right();

        do{
            step();
        } while (front_is_clear());

        turn_left();
    }
    else{
        turn_right();

        do {
            step();
        } while (left_is_blocked());

        turn_left();

        do {
            step();
        } while (left_is_blocked());

        turn_left();

        do{
            step();
        } while (front_is_clear());

        turn_right();
    }
}
