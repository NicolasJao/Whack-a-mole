// Arduino Whack-a-mole by Nicolas Jao

/*
  Wiring Steps:
  1. Connect 3 LEDs in series with resistors, the resistors connect to GND
  2. Connect 3 buttons to GND
  3. Connect the 3 LEDs to Arduino pins 12, 8, 2
  4. Connect the 3 buttons to Arduino pins 10, 5, 4. Make sure you are 
  connecting these diagonally opposite to the wires connecting the 
  buttons to GND.
  5. Connect all things connected to GND to the Arduino GND pin.
*/

// initializing the LED pins
int redLED = 12;
int greenLED = 8;
int blueLED = 2;

//initializing the button pins
int redButton = 10;
int greenButton = 5;
int blueButton = 4;

// setting up the random number LED variable
int randomLED;

// setting up the random time length variable
int randomTime;

// setting up the points counter
int points;

/* 
  Setting up a variable that reads the state of our buttons below.
  We will read the button states with digitalRead().
  digitalRead() returns a logic state of HIGH or LOW.
  We also set our button pins to INPUT_PULLUP in setup().
  INPUT_PULLUP sets the default state of the pin to HIGH
  if the button (which is essentially just a switch) it is 
  connected to is open (not pressed), and when it is closed (pressed),
  it connects the pin to GND, causing the pin to read LOW.
  So if we read the state of a button to be HIGH, or, 1, the button is
  currently not being pressed. If we read the state of a button to
  be LOW, or, 0, the button is being pressed.
*/
int redCurrentButtonState;
int greenCurrentButtonState;
int blueCurrentButtonState;

// setting up variables for what the button states used to be for the toggle
int redPreviousButtonState;
int greenPreviousButtonState;
int bluePreviousButtonState;

/*
  Setting up the variable for the elapsed time window. We use long 
  because the time in milliseconds can get huge and long has 
  more storage than int.
*/
long endTime;

void setup() {
  // setting up the LED pins to declare how we want to use them
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  // setting up the button pins to declare how we want to use them
  pinMode(redButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);

  // setting up the points counter to be 0 at the start of the game
  points = 0;

  // setting up our current button state variables to read what they currently are
  redCurrentButtonState = digitalRead(redButton);
  greenCurrentButtonState = digitalRead(greenButton);
  blueCurrentButtonState = digitalRead(blueButton);

  // setting up our serial monitor
  Serial.begin(9600);
  Serial.println("Serial monitor is active!");
}

void loop() {
  // this ensures they're all turned off at the start if they weren't whacked
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

  // initializing our random variables
  randomLED = random(1, 4);
  randomTime = random(100, 4000);

  // this creates a random delay between the last light turned on and the next one
  delay(randomTime);

  // turns on an LED based on the random number
  if (randomLED == 1) {
    digitalWrite(redLED, HIGH);
  }
  else if (randomLED == 2) {
    digitalWrite(greenLED, HIGH);
  }
  else if (randomLED == 3) {
    digitalWrite(blueLED, HIGH);
  }

  // This creates our time window. The current time plus the randomly-generated time interval is our end time.
  endTime = millis() + randomTime;

  // this entire loop happens inside that time window interval that we created above. It runs until the time reaches our end time.
  while (millis() < endTime) {
    // sets our previous button states as our current button states to save them
    redPreviousButtonState = redCurrentButtonState;
    greenPreviousButtonState = greenCurrentButtonState;
    bluePreviousButtonState = blueCurrentButtonState;

    // read the red button state
    redCurrentButtonState = digitalRead(redButton);
    // this condition only runs if the last button state was off and the current button state is on (it's being pressed)
    if (redCurrentButtonState == LOW && redPreviousButtonState == HIGH) {
      // if the right LED is on, it will add points and immediately turn the LED off as the mole has been whacked. or else, say there's no mole.
      if (randomLED == 1) {
        points++;
        Serial.print("Points: ");
        Serial.println(points);
        digitalWrite(redLED, LOW);
      }
      else {
        Serial.println("No mole!");
      }
    }

    // read the green button state
    greenCurrentButtonState = digitalRead(greenButton);
    // this condition only runs if the last button state was off and the current button state is on (it's being pressed)
    if (greenCurrentButtonState == LOW && greenPreviousButtonState == HIGH) {
      // if the right LED is on, it will add points and immediately turn the LED off as the mole has been whacked. or else, say there's no mole.
      if (randomLED == 2) {
        points++;
        Serial.print("Points: ");
        Serial.println(points);
        digitalWrite(greenLED, LOW);
      }
      else {
        Serial.println("No mole!");
      }
    }
    
    // read the blue button state
    blueCurrentButtonState = digitalRead(blueButton);
    // this condition only runs if the last button state was off and the current button state is on (it's being pressed)
    if (blueCurrentButtonState == LOW && bluePreviousButtonState == HIGH) {
      // if the right LED is on, it will add points and immediately turn the LED off as the mole has been whacked. or else, say there's no mole.
      if (randomLED == 3) {
        points++;
        Serial.print("Points: ");
        Serial.println(points);
        digitalWrite(blueLED, LOW);
      }
      else {
        Serial.println("No mole!");
      }
    }
  }
}
