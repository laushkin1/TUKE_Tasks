#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int redpin1 = A0, redpin2 = A1, redpin3 = A2, redpin4 = A3;
const int bluepin1 = 4, bluepin2 = 5, bluepin3 = 13, bluepin4 = 1;
const int on = 255, off = 0;

const int button1 = 9;
const int button2 = 8;
const int button3 = 7;
const int button4 = 6;
bool is_button1_press = false;
bool is_button2_press = false;
bool is_button3_press = false;
bool is_button4_press = false;

const int enter_button = 10;
bool is_enter_button_press = false;

bool show_num;

int num1, num2, num3, num4;
int num1p, num2p, num3p, num4p;

int attempt_count;

int match_number_a, match_number_b;

int secret_num;

int generate_code(bool repeat){
  // return 1234;
  	if(repeat == true)
    	return random(1000, 9999);
  	else{
      	while(1){
      		int num1, num2, num3, num4, res;
      		num1 = random(0, 10);
        	num2 = random(0, 10);
        	num3 = random(0, 10);
      		num4 = random(0, 10);
      	
      		if(num1 != num2 &&
           	   num1 != num3 &&
           	   num1 != num4 &&
           	   num2 != num3 &&
               num2 != num4 &&
               num3 != num4 &&
               num1 != 0 && num2 != 0 &&
               num3 != 0 && num4 != 0){
        		res = (num1*1000) + (num2*100) + (num3*10) + num4;
        		return res;
        	}
        }
	}
}



void setup(){
    lcd.begin();
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    pinMode(button3, INPUT_PULLUP);
    pinMode(button4, INPUT_PULLUP);
    pinMode(enter_button, INPUT_PULLUP);

    lcd.setCursor(0, 0);
    lcd.print("Welcome to");
    lcd.setCursor(0, 1);
    lcd.print("MasterMind");
    delay(1500);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Your goal is...");
    delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Guess my secret");
    lcd.setCursor(0, 1);
    lcd.print("combination!");
    delay(5000);
    lcd.clear();

    attempt_count = 0;
    num1 = 0;
    num2 = 0;
    num3 = 0;
    num4 = 0;

    show_num = true;

    match_number_a = 0;
    match_number_b = 0;

    generate_code(false);

    secret_num = generate_code(false);
    
    analogWrite(redpin1, off);
    analogWrite(redpin2, off);
    analogWrite(redpin3, off);
    analogWrite(redpin4, off);
    analogWrite(bluepin1, off);
    analogWrite(bluepin2, off);
    analogWrite(bluepin3, off);
    analogWrite(bluepin4, off);

}

void loop(){
    if (digitalRead(enter_button) == LOW && is_enter_button_press == false){
      
        lcd.clear();
        show_num = false;
        attempt_count++;
        if (attempt_count <= 9){
            num1p = num1;
            num2p = num2;
            num3p = num3;
            num4p = num4;
            if (String(num1)[0] == String(secret_num)[0]){
                match_number_a++;
                if (num1 == num2) num2 = 0;
                if (num1 == num3) num3 = 0;
                if (num1 == num4) num4 = 0;
                if (num2 == num3) num3 = 0;
                if (num2 == num4) num4 = 0;
                if (num3 == num4) num4 = 0;
            }
            if (String(num2)[0] == String(secret_num)[1]){
                match_number_a++;
                if (num2 == num1) num1 = 0;
                if (num2 == num3) num3 = 0;
                if (num2 == num4) num4 = 0;
                if (num1 == num3) num3 = 0;
                if (num1 == num4) num4 = 0;
                if (num3 == num4) num4 = 0;
            }
            if (String(num3)[0] == String(secret_num)[2]){
                match_number_a++;
                if (num3 == num1) num1 = 0;
                if (num3 == num2) num2 = 0;
                if (num3 == num4) num4 = 0;
                if (num2 == num1) num1 = 0;
                if (num2 == num4) num4 = 0;
            }
            if (String(num4)[0] == String(secret_num)[3]){
                match_number_a++;
                if (num4 == num1) num1 = 0;
                if (num4 == num2) num2 = 0;
                if (num4 == num3) num3 = 0;
                if (num1 == num2) num2 = 0;
                if (num1 == num3) num3 = 0;
                if (num2 == num3) num3 = 0;
            }

            if (String(num1)[0] == String(secret_num)[1] ||
                String(num1)[0] == String(secret_num)[2] ||
                String(num1)[0] == String(secret_num)[3]) match_number_b++;
            if (String(num2)[0] == String(secret_num)[0] ||
                String(num2)[0] == String(secret_num)[2] ||
                String(num2)[0] == String(secret_num)[3]) match_number_b++;
            if (String(num3)[0] == String(secret_num)[1] ||
                String(num3)[0] == String(secret_num)[0] ||
                String(num3)[0] == String(secret_num)[3]) match_number_b++;
            if (String(num4)[0] == String(secret_num)[1] ||
                String(num4)[0] == String(secret_num)[2] ||
                String(num4)[0] == String(secret_num)[0]) match_number_b++;

            if (match_number_b == 4 && match_number_a == 0){
                analogWrite(bluepin1, on);
                analogWrite(bluepin2, on);
                analogWrite(bluepin3, on);
                analogWrite(bluepin4, on);
            }
            else if (match_number_b == 3){
                if (match_number_a == 1){
                    analogWrite(redpin1, on);
                    analogWrite(bluepin2, on);
                    analogWrite(bluepin3, on);
                    analogWrite(bluepin4, on);
                }
                else if (match_number_a == 0){
                    analogWrite(bluepin1, on);
                    analogWrite(bluepin2, on);
                    analogWrite(bluepin3, on);
                    analogWrite(bluepin4, off);
                }
            }
            else if (match_number_b == 2){
                if (match_number_a == 1){
                    analogWrite(redpin1, on);
                    analogWrite(bluepin2, on);
                    analogWrite(bluepin3, on);
                    analogWrite(bluepin4, off);
                }
                else if (match_number_a == 2){
                    analogWrite(redpin1, on);
                    analogWrite(redpin2, on);
                    analogWrite(bluepin3, on);
                    analogWrite(bluepin4, on);
                }
                else if (match_number_a == 0){
                    analogWrite(bluepin1, on);
                    analogWrite(bluepin2, on);
                    analogWrite(bluepin3, off);
                    analogWrite(bluepin4, off);
                }
            }
            else if (match_number_b == 1){
                if (match_number_a == 1){
                    analogWrite(redpin1, on);
                    analogWrite(bluepin2, on);
                    analogWrite(bluepin3, off);
                    analogWrite(bluepin4, off);
                }
                else if (match_number_a == 2){
                    analogWrite(redpin1, on);
                    analogWrite(redpin2, on);
                    analogWrite(bluepin3, on);
                    analogWrite(bluepin4, off);
                }
                else if (match_number_a == 3){
                    analogWrite(redpin1, on);
                    analogWrite(redpin2, on);
                    analogWrite(redpin3, on);
                    analogWrite(bluepin4, on);
                }
                else if (match_number_a == 0){
                    analogWrite(bluepin1, on);
                    analogWrite(bluepin2, off);
                    analogWrite(bluepin3, off);
                    analogWrite(bluepin4, off);
                }
            }
            else if (match_number_b == 0){
                analogWrite(bluepin1, off);
                analogWrite(bluepin2, off);
                analogWrite(bluepin3, off);
                analogWrite(bluepin4, off);
                if (match_number_a == 0){
                    analogWrite(redpin1, off);
                    analogWrite(redpin2, off);
                    analogWrite(redpin3, off);
                    analogWrite(redpin4, off);
                }
                else if (match_number_a == 1){
                    analogWrite(redpin1, on);
                    analogWrite(redpin2, off);
                    analogWrite(redpin3, off);
                    analogWrite(redpin4, off);
                }
                else if (match_number_a == 2){
                    analogWrite(redpin1, on);
                    analogWrite(redpin2, on);
                    analogWrite(redpin3, off);
                    analogWrite(redpin4, off);
                }
                else if (match_number_a == 3){
                    analogWrite(redpin1, on);
                    analogWrite(redpin2, on);
                    analogWrite(redpin3, on);
                    analogWrite(redpin4, off);
                }
                else if (match_number_a == 4){
                    analogWrite(redpin1, on);
                    analogWrite(redpin2, on);
                    analogWrite(redpin3, on);
                    analogWrite(redpin4, on);
                }
            }

            if (match_number_a == 0){
                analogWrite(redpin1, off);
                analogWrite(redpin2, off);
                analogWrite(redpin3, off);
                analogWrite(redpin4, off);
            }

            lcd.setCursor(0, 0);
            lcd.print("0");
            lcd.print(attempt_count);
            lcd.print(": ");
            lcd.print(num1p);
            lcd.print(num2p);
            lcd.print(num3p);
            lcd.print(num4p);
            lcd.print(" ");
            lcd.print(match_number_a);
            lcd.print("A");
            lcd.print(match_number_b);
            lcd.print("B");

            if (match_number_a == 4){
                analogWrite(redpin1, off);
                analogWrite(redpin2, off);
                analogWrite(redpin3, off);
                analogWrite(redpin4, off);
                analogWrite(bluepin1, off);
                analogWrite(bluepin2, off);
                analogWrite(bluepin3, off);
                analogWrite(bluepin4, off);

                analogWrite(redpin1, on);
                analogWrite(redpin2, on);
                analogWrite(redpin3, on);
                analogWrite(redpin4, on);
                delay(1000);
                analogWrite(redpin1, off);
                analogWrite(redpin2, off);
                analogWrite(redpin3, off);
                analogWrite(redpin4, off);

                lcd.clear();
                lcd.print("Congratulations!");
                lcd.setCursor(0, 1);
                lcd.print("You win in ");
                lcd.print(attempt_count);
                lcd.print("step");
                delay(5000);
                setup();
            }
        }

        num1 = 0;
        num2 = 0;
        num3 = 0;
        num4 = 0;
        match_number_a = 0;
        match_number_b = 0;
        lcd.setCursor(0, 1);
        is_enter_button_press = true;
    }
    else if (digitalRead(enter_button) == HIGH)
        is_enter_button_press = false;

    if (digitalRead(button1) == LOW && is_button1_press == false){
        num1++;
        is_button1_press = true;
    }
    else if (digitalRead(button1) == HIGH)
        is_button1_press = false;

    if (digitalRead(button2) == LOW && is_button2_press == false){
        num2++;
        is_button2_press = true;
    }
    else if (digitalRead(button2) == HIGH)
        is_button2_press = false;

    if (digitalRead(button3) == LOW && is_button3_press == false){
        num3++;
        is_button3_press = true;
    }
    else if (digitalRead(button3) == HIGH)
        is_button3_press = false;

    if (digitalRead(button4) == LOW && is_button4_press == false){
        // analogWrite(redpin1, off);
        // analogWrite(redpin2, off);
        // analogWrite(redpin3, off);
        // analogWrite(redpin4, on);
        // analogWrite(bluepin1, off);
        // analogWrite(bluepin2, off);
        // analogWrite(bluepin3, off);
        // analogWrite(bluepin4, off);
        num4++;
        is_button4_press = true;
    }
    else if (digitalRead(button4) == HIGH)
        is_button4_press = false;

    if (num1 > 9) num1 = 0;
    if (num2 > 9) num2 = 0;
    if (num3 > 9) num3 = 0;
    if (num4 > 9) num4 = 0;
    if (attempt_count > 9){
        analogWrite(redpin1, off);
        analogWrite(redpin2, off);
        analogWrite(redpin3, off);
        analogWrite(redpin4, off);
        analogWrite(bluepin1, off);
        analogWrite(bluepin2, off);
        analogWrite(bluepin3, off);
        analogWrite(bluepin4, off);
        lcd.clear();
        lcd.print("You lose!");
        lcd.setCursor(0, 1);
        lcd.print("My number: ");
        lcd.print(secret_num);
        delay(5000);
        setup();
    }

    if (show_num){
        lcd.setCursor(0, 0);
        lcd.print("My number: ****");
    }

    lcd.setCursor(0, 1);
    lcd.print("Your guess: ");
    lcd.print(num1);
    lcd.print(num2);
    lcd.print(num3);
    lcd.print(num4);

}