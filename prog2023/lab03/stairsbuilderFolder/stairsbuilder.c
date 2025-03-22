#include <superkarel.h>
#define SPEED 300

void turn_right();
void turn_back();
void make_stairs();

int main(){
    turn_on("stairsbuilder.kw"); // 36
//    turn_on("stairsbuilder2.kw"); // 91
    set_step_delay(SPEED);

    int count_beeper = 0;

    step();

    set_step_delay(0);
    while (beepers_present()){
        pick_beeper();
        count_beeper++;
    }
    set_step_delay(SPEED);

    turn_right();
    make_stairs(count_beeper);
    turn_back();

    while(front_is_clear()){
        step();
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

void make_stairs(int count_beeper){
    int i;
    while(count_beeper){

        set_step_delay(0);
        for (i = 0; i < count_beeper; i++){
            put_beeper();
        }
        set_step_delay(SPEED);

        count_beeper--;
        i = 0;

        step();
    }
}