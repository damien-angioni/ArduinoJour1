void setup() {
  // put your setup code here, to run once:
  pinMode(A2, INPUT);
  pinMode(9, OUTPUT);
}

const int OFF = 0;
const int LIGHTED = 1;
const int SWITCH = 3;

const int MAX_TICKS = 1000;
const int MAX_PRESSED_TICKS = 2000;

int state = 0;

int ticks = 0;
bool lit = true;

bool button_pressed = false;
int button_ticks = 0;
bool pending_reset = false;

void loop() {
  // put your main code here, to run repeatedly:


  // button control
  if (digitalRead(A2) == HIGH) {
      
    button_ticks++;

    if (pending_reset == false) {

      // if not already pressed
      if (button_pressed == false) {

        button_pressed = true;
        // update state
        if (state < SWITCH) {
          state++;
        }

      }

      if (button_ticks > MAX_PRESSED_TICKS) {

        state = OFF;
        button_ticks = 0;
        pending_reset = true;

      }

    }

  } else {

    if (pending_reset == true) {

      pending_reset = false;
      ticks = 0;
      lit = true;

    }

    button_pressed = false;
    button_ticks = 0;

  }


  // control LED
  if (state == OFF) {
    digitalWrite(9, LOW);
  } else {
    if (state == LIGHTED or state == LIGHTED+1) {
      
      digitalWrite(9, HIGH);

    } else if (state == SWITCH) {
      ticks++;
      if (ticks > MAX_TICKS) {
        if (lit == true) {
          lit = false;
        } else {
          lit = true;
        }
        ticks = 0;
      }

      if (lit == true) {
        digitalWrite(9, HIGH);
      } else {
        digitalWrite(9, LOW);
      }
    }
  }

  delay(1);
}
