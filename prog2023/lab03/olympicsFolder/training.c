#include <superkarel.h>

void jump_over();
void go_forward();
void turn_right();

int main(){
    turn_on("training.kw");
    while (no_beepers_present()){
        go_forward();
        jump_over();
    }
    turn_off();
    return 0;
}

void turn_right(){
    turn_left();
    turn_left();
    turn_left();
}

void jump_over(){
    turn_left();
    while (right_is_blocked()){
        step();
    }
    turn_right();
    step();
    turn_right();
    while (front_is_clear()){
        step();
    }
    turn_left();
}

void go_forward(){
    while (front_is_clear()){
        step();
    }
}