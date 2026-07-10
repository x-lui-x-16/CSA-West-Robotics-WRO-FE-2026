#include <Servo.h>
Servo miServo;

/* =========================================================
   ULTRASONIC SENSOR PINS (HC-SR04)
   ---------------------------------------------------------
   TRIG = pin that sends the ultrasonic pulse
   ECHO = pin that receives the reflected pulse
   ---------------------------------------------------------
   Sensor layout used in this program:
   - TRIG1 / ECHO1 -> Front sensor
   - TRIG2 / ECHO2 -> Left sensor
   - TRIG3 / ECHO3 -> Right sensor
   ========================================================= */
#define TRIG1 8   // Front ultrasonic sensor trigger pin
#define ECHO1 9   // Front ultrasonic sensor echo pin

#define TRIG2 10  // Left ultrasonic sensor trigger pin
#define ECHO2 11  // Left ultrasonic sensor echo pin

#define TRIG3 12  // Right ultrasonic sensor trigger pin
#define ECHO3 13  // Right ultrasonic sensor echo pin


/* =========================================================
   L298N MOTOR DRIVER PINS
   ---------------------------------------------------------
   This code assumes ONE drive motor connected to channel A
   of the L298N module.

   ENA -> PWM speed control pin
   IN1 and IN2 -> direction control pins

   If later change the wiring, only modify these values.
   ========================================================= */
const int ENA = 5;   // PWM pin used to control motor speed
const int IN1 = 4;   // Motor direction pin 1
const int IN2 = 3;   // Motor direction pin 2


/* =========================================================
   SERVO PIN
   ---------------------------------------------------------
   The servo controls the steering system.
   ========================================================= */
const int servoPin = 2;

/* =========================================================
   START BUTTON PIN
   ---------------------------------------------------------
   This push button is used to start the robot manually.

   Wiring used in this code:
   - one side of the button goes to the Arduino pin below
   - the other side of the button goes to GND

   The pin will be configured with INPUT_PULLUP in setup(),
   so the reading works like this:
   - HIGH = button not pressed
   - LOW  = button pressed
   ========================================================= */
const int startButtonPin = 7;

/* =========================================================
   SERVO ANGLES FOR ACKERMANN STEERING
   ---------------------------------------------------------
   These are the steering positions that the robot uses.
   ========================================================= */
const int SERVO_CENTER      = 90;   // Straight ahead
const int SERVO_MAX_LEFT    = 35;   // Max left steering
const int SERVO_MAX_RIGHT   = 155;  // Max right steering


/* =========================================================
   ROBOT / TRACK DIMENSIONS
   ---------------------------------------------------------
   All values are in millimeters unless stated otherwise.

   ROBOT_WIDTH_MM:
   Distance between the left and right ultrasonic sensors.
   The robot width at the sensor line is 85 mm.

   LANE_WIDTH_MM:
   Width of the path the robot must travel through.

   TARGET_SIDE_DISTANCE_MM:
   If the robot is centered, each side sensor should read
   approximately this distance:
      (lane width - robot width) / 2

   SIDE_TOLERANCE_MM:
   Allowed error. The robot does not need to be perfectly centered
   to the millimeter. Around 50-60 mm tolerance.
   ========================================================= */
const float ROBOT_WIDTH_MM = 85.0;
const float LANE_WIDTH_MM  = 1000.0;
const float TARGET_SIDE_DISTANCE_MM = (LANE_WIDTH_MM - ROBOT_WIDTH_MM) / 2.0;  // 457.5 mm
const float SIDE_TOLERANCE_MM = 60.0;  // Allowed centering error


/* =========================================================
   FRONT DETECTION DISTANCE
   ---------------------------------------------------------
   When the front sensor reads a distance lower than or equal to
   this value, the robot will consider that it is approaching the
   end of the current straight corridor and will start evaluating
   a turn.

   980 mm = 98 cm
   ========================================================= */
const float FRONT_TURN_TRIGGER_MM = 980.0;


/* =========================================================
   TURN DECISION LOGIC
   ---------------------------------------------------------
   To decide the turning side, we compare left and right distances.

   Example:
   - turn right if right distance >= left distance * TURN_RATIO
   - turn left  if left distance  >= right distance * TURN_RATIO

   A condition similar to "one side must be at least
   double the other side", so TURN_RATIO = 2.0

   If this condition is not met, the robot will keep moving forward
   a little and keep checking until a clearer turn opening appears.
   ========================================================= */
const float TURN_RATIO = 2.0;


/* =========================================================
   PD CONTROLLER CONSTANTS
   ---------------------------------------------------------
   The robot will try to stay centered by comparing the left and
   right distances.

   Error definition used here:
      error = leftDistance - rightDistance

   Meaning:
   - error > 0  -> left side is more open than right side
                   so the robot is closer to the right wall
   - error < 0  -> right side is more open than left side
                   so the robot is closer to the left wall

   The PD controller converts that error into a steering correction.

   KP controls how strongly the robot reacts to the current error.
   KD controls how strongly the robot reacts to sudden error changes.

   Start with these values, then tune if needed:
   - If the robot reacts too weakly and drifts, increase KP a little.
   - If it oscillates too much left/right, reduce KP or increase KD.
   ========================================================= */
float KP = 0.10;   // Proportional gain
float KD = 0.35;   // Derivative gain


/* =========================================================
   MOTOR SPEED SETTINGS
   ---------------------------------------------------------
   baseSpeedPercent:
   Main forward speed while the robot is driving straight.

   turnSpeedPercent:
   Speed used during the 90-degree turning maneuver.
   It is often safer to turn a bit slower than driving straight.
   ========================================================= */
int baseSpeedPercent = 45;   // 0 to 100
int turnSpeedPercent = 35;   // 0 to 100


/* =========================================================
   TURN TIMING
   ---------------------------------------------------------
   Since there is no encoder or IMU in this code, the 90-degree turn
   is approximated using time while the steering is fully left/right.

   IMPORTANT:
   This value WILL need real-world calibration.
   Example:
   - If the robot turns less than 90°, increase the time.
   - If it turns more than 90°, decrease the time.
   ========================================================= */
unsigned long turn90TimeMs = 1050;   // Adjust after testing


/* =========================================================
   LOOP TIMING / SENSOR UPDATE
   ---------------------------------------------------------
   controlIntervalMs:
   Time between each control update.
   Using a fixed control period helps the PD controller behave
   more consistently.
   ========================================================= */
const unsigned long controlIntervalMs = 50;

/* =========================================================
   TURN COUNTER / LAP COUNTER
   ---------------------------------------------------------
   The track requires 12 turns to complete 3 full laps
   (4 turns per lap x 3 laps = 12 turns).

   totalTurnsNeeded:
   How many 90-degree turns must be completed before stopping.

   completedTurns:
   Counts how many turns the robot has already finished.
   ========================================================= */
const int totalTurnsNeeded = 12;
int completedTurns = 0;

/* =========================================================
   FINAL FORWARD MOVEMENT AFTER THE LAST TURN
   ---------------------------------------------------------
   After completing the 12th turn, the robot will move straight
   for a short extra time so it can stop closer to the same
   position where it originally started.

   finalForwardSpeedPercent:
   Speed used for that final straight movement.

   finalForwardTimeMs:
   How long the robot should keep moving after the 12th turn
   before stopping completely.

   IMPORTANT:
   This value must be calibrated on the real track.
   If the robot stops too early, increase finalForwardTimeMs.
   If it goes too far, decrease finalForwardTimeMs.
   ========================================================= */
int finalForwardSpeedPercent = 35;
unsigned long finalForwardTimeMs = 500;

/* =========================================================
   STATE MACHINE
   ---------------------------------------------------------
   Instead of putting all robot behavior mixed together,
   we use "states". This makes the code easier to understand.

   STATE_DRIVE_CENTER:
      Robot drives forward and uses PD to stay centered.

   STATE_TURNING_LEFT:
      Robot is executing a 90-degree left turn.

   STATE_TURNING_RIGHT:
      Robot is executing a 90-degree right turn.

   STATE_FINISHED:
      Robot stops after completing all required turns.
   ========================================================= */
enum RobotState {
  STATE_DRIVE_CENTER,
  STATE_TURNING_LEFT,
  STATE_TURNING_RIGHT,
  STATE_FINISHED
};

RobotState currentState = STATE_DRIVE_CENTER;

/* =========================================================
   START STATE FLAG
   ---------------------------------------------------------
   This variable tells the program whether the robot is still
   waiting for the start button or if it has already started.

   false -> robot is stopped and waiting for the button
   true  -> robot has already started and can run the normal loop
   ========================================================= */
bool robotStarted = false;

/* =========================================================
   VARIABLES USED BY THE PD CONTROLLER
   ---------------------------------------------------------
   previousError:
   Stores the last error value to compute the derivative term.

   lastControlTime:
   Stores the last time the control loop was executed.
   ========================================================= */
float previousError = 0.0;
unsigned long lastControlTime = 0;


/* =========================================================
   VARIABLES USED BY THE TURNING STATE
   ---------------------------------------------------------
   turnStartTime:
   Stores the exact moment when a turn started.
   Used to know when the programmed 90-degree turn time is over.
   ========================================================= */
unsigned long turnStartTime = 0;


/* =========================================================
   FUNCTION: percentToPWM
   ---------------------------------------------------------
   Converts a speed value from 0-100 (%) into 0-255 (PWM),
   which is what analogWrite() uses on Arduino.
   ========================================================= */
int percentToPWM(int percent) {
  percent = constrain(percent, 0, 100);
  return map(percent, 0, 100, 0, 255);
}


/* =========================================================
   FUNCTION: setMotorForward
   ---------------------------------------------------------
   Drives the motor forward using a speed in percentage.
   ========================================================= */
void setMotorForward(int speedPercent) {
  int pwmValue = percentToPWM(speedPercent);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, pwmValue);
}


/* =========================================================
   FUNCTION: stopMotor
   ---------------------------------------------------------
   Stops the drive motor.
   ========================================================= */
void stopMotor() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}


/* =========================================================
   FUNCTION: readDistanceMM
   ---------------------------------------------------------
   Reads distance from one HC-SR04 sensor and returns the value
   in millimeters.

   How it works:
   1) Send a 10 microsecond pulse to TRIG.
   2) The sensor emits ultrasound.
   3) pulseIn() measures how long the echo pin stays HIGH.
   4) That time is converted into distance.

   Return value:
   - distance in millimeters if a valid echo is received
   - -1 if no echo is received within the timeout

   The timeout is set to 30000 us (~5 meters max theoretical range),
   but practical HC-SR04 range is lower.
   ========================================================= */
float readDistanceMM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return -1;  // No valid reading
  }

  // Distance in cm = duration * 0.0343 / 2
  // Distance in mm = distance in cm * 10
  float distanceMM = (duration * 0.343) / 2.0;

  return distanceMM;
}


/* =========================================================
   FUNCTION: readAllSensors
   ---------------------------------------------------------
   Reads the front, left and right ultrasonic sensors.

   We pass the variables by reference so the function can fill them
   directly and keep the main loop cleaner and easier to read.
   ========================================================= */
void readAllSensors(float &frontMM, float &leftMM, float &rightMM) {
  frontMM = readDistanceMM(TRIG1, ECHO1);
  delay(5);  // small separation between ultrasonic reads to reduce interference

  leftMM = readDistanceMM(TRIG2, ECHO2);
  delay(5);

  rightMM = readDistanceMM(TRIG3, ECHO3);
  delay(5);
}


/* =========================================================
   FUNCTION: applyPDCentering
   ---------------------------------------------------------
   This function steers the robot so it stays approximately
   centered between the left and right walls.

   Core idea:
   - If left distance and right distance are equal, robot is centered.
   - If one side is larger than the other, the robot is drifting.

   Error used:
      error = leftMM - rightMM

   Steering correction:
      correction = KP*error + KD*(error - previousError)

   Then we convert that correction into a servo angle around center.
   ========================================================= */
void applyPDCentering(float leftMM, float rightMM) {
  // If one of the side sensors failed, keep steering centered
  if (leftMM < 0 || rightMM < 0) {
    miServo.write(SERVO_CENTER);
    return;
  }

  // Positive error means left side is more open than right side
  // so the robot is too close to the right wall and should steer left.
  float error = leftMM - rightMM;

  // Derivative term: how fast the error changed since the last loop
  float derivative = error - previousError;

  // PD controller output
  float correction = KP * error + KD * derivative;

  previousError = error;

  /* ---------------------------------------------------------
     Convert PD correction into servo angle.

     IMPORTANT:
     The correction value can be large because distances are in mm.
     To keep the servo in a safe range, we divide correction by a
     scale factor before adding it to the center angle.

     If the steering reacts too aggressively:
       - increase the divisor (for example 12 or 15)
       - or reduce KP/KD
     If the steering reacts too weakly:
       - decrease the divisor (for example 8)
       - or increase KP/KD
     --------------------------------------------------------- */
  float steeringScale = 10.0;
  int servoAngle = SERVO_CENTER + (int)(correction / steeringScale);

  // Safety limits so the servo never exceeds the steering range
  servoAngle = constrain(servoAngle, SERVO_MAX_LEFT, SERVO_MAX_RIGHT);

  miServo.write(servoAngle);
}


/* =========================================================
   FUNCTION: beginLeftTurn
   ---------------------------------------------------------
   Starts a 90-degree left turn:
   - changes state
   - stores the start time
   - moves steering fully left
   - keeps the motor moving forward slowly during the turn
   ========================================================= */
void beginLeftTurn() {
  currentState = STATE_TURNING_LEFT;
  turnStartTime = millis();

  miServo.write(SERVO_MAX_LEFT);
  setMotorForward(turnSpeedPercent);

  Serial.println("TURN START -> LEFT");
}


/* =========================================================
   FUNCTION: beginRightTurn
   ---------------------------------------------------------
   Starts a 90-degree right turn.
   ========================================================= */
void beginRightTurn() {
  currentState = STATE_TURNING_RIGHT;
  turnStartTime = millis();

  miServo.write(SERVO_MAX_RIGHT);
  setMotorForward(turnSpeedPercent);

  Serial.println("TURN START -> RIGHT");
}


/* =========================================================
   FUNCTION: finishTurnAndReturnToDrive
   ---------------------------------------------------------
   Called when the programmed turning time has elapsed.

   What it does:
   - increments the completed turn counter
   - re-centers the servo
   - if all turns are done, stop the robot
   - otherwise return to straight driving mode
   ========================================================= */
void finishTurnAndReturnToDrive() {
  completedTurns++;

  // Put the steering back to the straight position after finishing the turn
  miServo.write(SERVO_CENTER);
  delay(150);  // Small pause to let the steering settle

  Serial.print("TURN COMPLETED -> total turns = ");
  Serial.println(completedTurns);

  // If the robot has already completed all required turns,
  // do one final straight movement before stopping.
  if (completedTurns >= totalTurnsNeeded) {
    Serial.println("LAST TURN COMPLETED -> moving forward a little before stopping.");

    // Keep steering centered and move forward for a short final distance
    miServo.write(SERVO_CENTER);
    setMotorForward(finalForwardSpeedPercent);
    delay(finalForwardTimeMs);

    // Now stop completely
    stopMotor();
    miServo.write(SERVO_CENTER);
    currentState = STATE_FINISHED;

    Serial.println("ROBOT FINISHED: final forward movement completed.");
  } 
  else {
    // If the robot still has turns left to do, return to normal centered driving
    currentState = STATE_DRIVE_CENTER;
  }
}

/* =========================================================
   ARDUINO SETUP
   ========================================================= */
void setup() {
  Serial.begin(9600);

  /* =========================================================
   START BUTTON CONFIGURATION
   ---------------------------------------------------------
   INPUT_PULLUP enables the Arduino's internal pull-up resistor,
   so no external resistor is needed for the button.

   With this mode:
   - the pin reads HIGH when the button is not pressed
   - the pin reads LOW when the button is pressed because
     the button connects the pin directly to GND
   ========================================================= */
  pinMode(startButtonPin, INPUT_PULLUP);

  // ---------------- Motor driver pins ----------------
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // ---------------- Servo setup ----------------
  miServo.attach(servoPin);
  miServo.write(SERVO_CENTER);

  // ---------------- Ultrasonic sensor pins ----------------
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);

  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT);

  // Make sure the motor starts stopped
  stopMotor();

  Serial.println("Robot ready.");
}


/* =========================================================
   MAIN LOOP
   ---------------------------------------------------------
   This loop uses a state machine:
   1) Drive centered with PD
   2) Detect an upcoming corner
   3) Decide left or right turn based on side openings
   4) Execute the 90-degree turn
   5) Count turns until 12 are completed
   ========================================================= */
void loop() {
  /* =====================================================
     START BUTTON LOGIC
     -----------------------------------------------------
     The robot will remain stopped until the user presses
     the start button.

     Because the button uses INPUT_PULLUP:
     - button NOT pressed = HIGH
     - button pressed     = LOW
     ===================================================== */
  if (!robotStarted) {
    stopMotor();
    miServo.write(SERVO_CENTER);

    // If the button is pressed, allow the robot to start
    if (digitalRead(startButtonPin) == LOW) {
      delay(30);  // small debounce delay

      // Check again to reduce false triggers from button bounce
      if (digitalRead(startButtonPin) == LOW) {
        robotStarted = true;
        lastControlTime = millis();  // reset control timing reference
        previousError = 0;           // reset PD memory

        Serial.println("START BUTTON PRESSED -> Robot started.");

        // Wait until the button is released so one press does not
        // accidentally trigger extra unwanted behavior
        while (digitalRead(startButtonPin) == LOW) {
          delay(5);
        }
      }
    }

    // While waiting for the button, do nothing else
    return;
  }

  /* =====================================================
     FINISHED STATE
     -----------------------------------------------------
     If the robot already completed all required turns,
     keep it stopped and do nothing else.
     ===================================================== */
  if (currentState == STATE_FINISHED) {
    stopMotor();
    miServo.write(SERVO_CENTER);
    return;
  }

  /* =====================================================
     FIXED CONTROL PERIOD
     -----------------------------------------------------
     The control logic is executed only every
     "controlIntervalMs" milliseconds.
     This helps keep the PD behavior more stable.
     ===================================================== */
  if (millis() - lastControlTime < controlIntervalMs) {
    return;
  }
  lastControlTime = millis();

  /* =====================================================
     SENSOR READING
     -----------------------------------------------------
     Read all three ultrasonic sensors:
     - front
     - left
     - right
     ===================================================== */
  float frontMM, leftMM, rightMM;
  readAllSensors(frontMM, leftMM, rightMM);

  /* =====================================================
     DEBUG PRINTS
     -----------------------------------------------------
     These values are very useful while tuning the robot:
     - front distance
     - left distance
     - right distance
     - number of completed turns
     ===================================================== */
  Serial.print("Front: ");
  Serial.print(frontMM);
  Serial.print(" mm | Left: ");
  Serial.print(leftMM);
  Serial.print(" mm | Right: ");
  Serial.print(rightMM);
  Serial.print(" mm | Turns: ");
  Serial.println(completedTurns);

  switch (currentState) {

    /* ===================================================
       STATE 1: DRIVE CENTERED
       ---------------------------------------------------
       In this state the robot:
       1) moves forward
       2) uses PD to stay centered
       3) checks if it is approaching a corner
       =================================================== */
    case STATE_DRIVE_CENTER: {

      // Drive forward at the normal straight speed
      setMotorForward(baseSpeedPercent);

      // Use left and right sensors to stay centered
      applyPDCentering(leftMM, rightMM);

      /* -------------------------------------------------
         TURN DETECTION
         -------------------------------------------------
         If the front sensor detects the next wall/corner
         at or below the configured trigger distance,
         compare the side distances to decide the turn
         direction.

         Turn right if:
           right side is at least TURN_RATIO times left side

         Turn left if:
           left side is at least TURN_RATIO times right side
         ------------------------------------------------- */
      if (frontMM > 0 && frontMM <= FRONT_TURN_TRIGGER_MM) {

        bool canTurnRight = (rightMM > 0 && leftMM > 0 && rightMM >= leftMM * TURN_RATIO);
        bool canTurnLeft  = (rightMM > 0 && leftMM > 0 && leftMM >= rightMM * TURN_RATIO);

        if (canTurnRight) {
          beginRightTurn();
        }
        else if (canTurnLeft) {
          beginLeftTurn();
        }
        else {
          // No clear turn direction yet.
          // Keep moving centered and continue checking.
          Serial.println("Front trigger detected, but turn side is not clear yet.");
        }
      }

      break;
    }

    /* ===================================================
       STATE 2: TURNING LEFT
       ---------------------------------------------------
       Keep steering fully left and moving forward until
       the programmed turning time is completed.
       =================================================== */
    case STATE_TURNING_LEFT: {
      setMotorForward(turnSpeedPercent);
      miServo.write(SERVO_MAX_LEFT);

      if (millis() - turnStartTime >= turn90TimeMs) {
        finishTurnAndReturnToDrive();
      }

      break;
    }

    /* ===================================================
       STATE 3: TURNING RIGHT
       ---------------------------------------------------
       Keep steering fully right and moving forward until
       the programmed turning time is completed.
       =================================================== */
    case STATE_TURNING_RIGHT: {
      setMotorForward(turnSpeedPercent);
      miServo.write(SERVO_MAX_RIGHT);

      if (millis() - turnStartTime >= turn90TimeMs) {
        finishTurnAndReturnToDrive();
      }

      break;
    }

    /* ===================================================
       STATE 4: FINISHED
       ---------------------------------------------------
       Safety state: keep the robot stopped.
       =================================================== */
    case STATE_FINISHED: {
      stopMotor();
      miServo.write(SERVO_CENTER);
      break;
    }
  }
}
