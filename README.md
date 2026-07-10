# CSA-West-Robotics-WRO-FE-2026
Our repository for WRO future engineers category for this 2026 season

## 📂 Repo's Folder Structure/Overview

```mermaid
flowchart TD
    A["📦 Repository"]

    A --> B["🧊 Models"]
    A --> C["📁 Other"]
    A --> D["🗺️ Schemes"]
    A --> E["💻 Source Code"]
    A --> F["📸 Team Photos"]
    A --> G["📹 Performance Videos"]
    A --> H["🤖🚗 Vehicle Pictures"]
    A --> I["⚙️ Electromechanical Components"]
    A --> J["🚗 Mobility"]

    B --> B1["3D models"]
    C --> C1["Miscellaneous files"]
    D --> D1["Wiring diagrams"]
    E --> E1["Arduino code"]
    F --> F1["Official team photos"]
    G --> G1["Challenge videos"]
    H --> H1["Robot images"]
    I --> I1["Robot components"]
    J --> J1["Robot mobility sistems"]
```

### 🚀 Quick Access

- 🧊 **Models** → [Open Folder](models/)
- 📁 **Other** → [Open Folder](others/)
- 🗺️ **Schemes** → [Open Folder](schemes/)
- 💻 **Source Code** → [Open Folder](src/)
- 📸 **Team Photos** → [Open Folder](t-photos/)
- 📹 **Performance Videos** → [Open Folder](p-videos/)
- 🤖🚗 **Vehicle Pictures** → [Open Folder](v-photos/)
- ⚙️ **Electromechanical Components** → [Open Folder](electromechanical-components/)
- 🚗 **Mobility** → [Open Section](mobility/)

## 🧰 Engineering Materiales
All the materials used to create pur rpbot
- 1 [Arduino Mega 2560 R3](https://docs.arduino.cc/resources/datasheets/A000067-datasheet.pdf) 
- 1 [Pixy2 Cam](https://pixycam-com.translate.goog/pixy2/?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=tc)
- 1 [L298n Motor Driver Board Module](https://naylampmechatronics.com/blog/11_tutorial-de-uso-del-modulo-l298n.html)
- 3 [Ultrasonic Sensors HC-SR04](https://www.amazon.com/-/es/ultrasónico-HC-SR04-detector-distancia-Arduino/dp/B09PBJ4ZY1)
- 1 Small on/off switch
- 1 Push Botton
- 1 Red LED for power indicator
- 1 Resistor ( Ohms) for the power indicator LED
- 32 Proto Wires
- 1 Power Supply (More of this could be seen on Power Management)
    - 1 Case of 1 18650 Batterie connected in series
    - 1 Case of 3 18650 Batteries connected in series
    - 4 18650 3.7V 2800mAh Battery 
- 1 Chasis
    - 4 Wheels
    - 1 [Greartisan DC 12V 300RPM Motor](https://honestforwarder.com/product/greartisan-dc-12v-300rpm-geared-motor-high-torque-electric-micro-speed-reduction-gear-motor-eccentric-output-shaft-37-mm-diameter-gear-D4DQXkS1zP)
    - 1 [MG 996r Servo](https://www.amazon.com/dp/B09BZ5955Z?psc=1&ref_=cm_sw_r_cp_ud_ct_M9EZM05VN4JMKBB2R17X)
    - [Multiply 3d pieces that can be found in the following directory](models/)

## 🛠️ Building instructions
- Most of the chasis was printed in 3D, but there are some supports from the [YFROBOT Kit Chassis](https://yfrobot.com/products/steering-gear-robot).
- Electronics (Circuit and battery): [The circuit diagram can be found in the schemes directory](schemes/)
- Code (For the arduino): [The source code can be found in the src directory](src/)

## 👋 Introduction
Brief intro to our solution

For our robotics competition, we developed an innovative autonomous navigation solution that combines computer vision, distance sensing, and precise motion control. Our robot leverages Arduino's vision capabilities through a Pixy2 camera module to detect and interpret color signals placed along the competition field. These signals serve as navigation markers that determine the robot's next movement: a green signal instructs the robot to perform a left turn, while a red signal indicates a right turn. This vision-based approach allows the robot to make accurate decisions in real time while navigating the course.

To improve its environmental awareness and overall maneuverability, the robot is equipped with three ultrasonic sensors, all strategically positioned on the front side. These sensors continuously measure the distance to nearby objects, enabling the robot to detect obstacles, maintain safe navigation, and react quickly to changes in its surroundings. By combining information from the camera and ultrasonic sensors, the robot can simultaneously follow the competition's navigation rules while avoiding collisions.

Our solution demonstrates the effective integration of computer vision, sensor-based perception, and autonomous control algorithms to achieve reliable, accurate, and efficient navigation. This combination of technologies allows the robot to perform consistently in dynamic environments, making it a robust solution for robotics competitions that require both precision and adaptability.

## WRO 2026 Future Engineer Challenge
The WRO 2025 Future Engineers category invites teams to develop a fully autonomous vehicle capable of completing a dynamic driving course. Throughout the competition, the robot must rely on a combination of sensors, computer vision, and intelligent control algorithms to navigate the track, react to randomized elements, and execute precise driving maneuvers without human intervention.

### 📌 Competition Overview
#### 🏁 Open Challenge:

During this stage, the robot is required to complete three full laps around the track. Since the layout includes randomly placed obstacles and changing conditions, the robot must continuously analyze its environment and adapt its navigation strategy in real time.

#### 🚦 Obstacle Challenge:
In addition to navigating the course, the robot must recognize colored traffic markers placed at random positions along the track and react according to the competition rules:

🟥 Red marker: The robot must pass on the right side.

🟩 Green marker: The robot must pass on the left side.

Once the three laps are completed, the robot must locate the designated parking area and successfully perform a parallel parking maneuver inside the marked space, demonstrating a high level of positioning accuracy and vehicle control.

### 📑 Engineering Documentation
Every participating team must maintain a public GitHub repository containing detailed documentation of the project. This includes the robot's mechanical and electronic design, software implementation, engineering decisions, development process, and source code. The purpose of this requirement is to encourage knowledge sharing, transparency, and collaboration within the robotics community.

### 🏆 Evaluation Criteria
Robots are assessed based on several factors, including navigation accuracy, completion time, and the quality of the technical documentation provided by the team. Additional emphasis is placed on the robot's ability to adapt to randomized scenarios while maintaining consistent performance and demonstrating innovative engineering solutions. Beyond technical excellence, the challenge also promotes teamwork, creativity, and effective problem-solving skills.

## 🚗 Mobility
Our robot uses an Ackermann steering system, a steering geometry commonly found in real automobiles. This configuration allows the robot to perform smooth and controlled turns by steering only the front wheels, while the rear wheels are responsible for propulsion through a rigid rear axle.

The steering mechanism is actuated by an MG996R high-torque servo motor, which is directly connected to the custom-designed Ackermann linkage. Based on the navigation decisions made by the Arduino Mega 2560 R3, the servo adjusts the steering angle, allowing the robot to accurately follow the track, avoid obstacles, and execute the required maneuvers during the competition.

Propulsion is provided by a Geartisan 12V 300 RPM DC gear motor, which transmits power to the rigid rear axle. This configuration separates the steering and driving systems, resulting in smoother motion and more predictable vehicle behavior.

One of the main advantages of the Ackermann steering geometry is that it reduces wheel slip while turning. Since the front wheels follow different turning radii, the robot can navigate curves more efficiently and maintain better traction throughout the course. This improves stability, minimizes unnecessary tire wear, and allows for more precise obstacle avoidance and parking maneuvers.

The entire chassis was designed around this steering architecture, with most structural components manufactured using 3D printing. This allowed us to optimize the placement of the steering system, electronics, and drive components while keeping the robot lightweight, modular, and easy to maintain.

Overall, the combination of a dedicated steering servo, a rear-wheel drive system, and an Ackermann steering mechanism provides reliable handling, accurate trajectory tracking, and consistent performance throughout the WRO Future Engineers challenge.

### RWD System
- [RWD Robot System](mobility/rwd-system/)

### Ackerman Steering Mechanism
- [Ackerman Robot Steering](mobility/steering-mechanism/)

## 🎯 Strategy
Strategy Explanation
### Color Detection with Pixy2 Cam:
We integrated a Pixy2 Cam with the Arduino Mega 2560 R3 to accurately detect colors. This system allows the robot to recognize green and red colors, which serve as signals to turn left or right, respectively. By using a camera module and appropriate color detection algorithms, the robot can continuously monitor its environment and respond in real time.

### Directional Decision Making:
Upon detecting the color green, the robot is programmed to turn left. Conversely, when red is detected, the robot turns right. This color-based decision-making process ensures that the robot navigates efficiently and avoids obstacles or follows a designated path based on the predefined color signals.

### Border Detection and Turning:
In addition to color detection, our robot is equipped with ultrasonic sensors to identify the moment when it should turn. It uses an "umbral" which is a certain distance which if the robot pases, it will start to turn to a certain direction. That direction is decided by the other two ultrasonic sensors to the left and to the right.

### Implementation Details Code and Integration:
Our code, available here, outlines the specific algorithms and logic used for color detection, decision-making, and obstacle avoidance. The integration of the vision system with Arduino's control mechanisms is crucial for the robot's functionality.

### Color Detection Algorithm:
The color detection system will be developed and documented in the second phase of the challenge.  
This section will later describe how the robot reads, processes, and classifies color data, as well as how those detections are integrated into its navigation or task logic.

### Obstacle Avoidance Routine:
The obstacle avoidance routine will also be addressed in the second phase of the challenge.  
At that stage, this section will explain how the robot detects obstacles, decides on avoidance maneuvers, and integrates those actions with the rest of the navigation system.

## 💻 Code Explanation
The robot follows this sequence:

1. **Waits for the start button**
2. **Drives forward while staying centered**
3. **Uses the left and right ultrasonic sensors with a PD controller**
4. **Checks the front sensor to detect when it is approaching a corner**
5. **Compares the side distances to decide whether to turn left or right**
6. **Executes a 90° turn using the servo and a timed forward motion**
7. **Counts the completed turns**
8. **Repeats the process until the required number of turns is reached**
9. **Performs a small final forward movement and stops**

---

### Code Structure
#### 1. Libraries and Servo Object
The code starts by including the Servo library and creating a servo object:

```cpp
#include <Servo.h>
Servo miServo;
```
The servo is used to control the Ackermann steering system of the robot.

#### 2. Pin Definitions
The next section defines all hardware connections:

- HC-SR04 pins
Front ultrasonic sensor
Left ultrasonic sensor
Right ultrasonic sensor
- L298N pins
PWM speed pin (ENA)
Direction pins (IN1, IN2)
- Servo pin
Start button pin

These definitions are grouped at the top of the code so that hardware changes can be made easily without modifying the rest of the program.

#### 3. Steering Constants
The servo uses three main steering positions:
- SERVO_CENTER → wheels pointing straight
- SERVO_MAX_LEFT → maximum left steering angle
- SERVO_MAX_RIGHT → maximum right steering angle

These values are based on the robot’s Ackermann steering geometry and can be adjusted if the steering range changes.

#### 4. Track and Robot Geometry
The code includes constants that describe the robot and the track:
- ROBOT_WIDTH_MM
- LANE_WIDTH_MM
- TARGET_SIDE_DISTANCE_MM
- SIDE_TOLERANCE_MM
These values represent the width of the robot, the width of the lane, and the ideal side distance when the robot is centered.

For a 1000 mm lane and an 85 mm robot width, the ideal distance to each side wall is:
- (1000 - 85) / 2 = 457.5 mm
Although this target value is useful for reference, the centering logic mainly relies on comparing the left and right sensor readings directly.

#### 5. Turn Detection and Decision Thresholds
The code uses two key parameters to detect and classify turns:
- FRONT_TURN_TRIGGER_MM
- TURN_RATIO

##### FRONT_TURN_TRIGGER_MM
This is the front distance threshold that tells the robot it is approaching the end of a straight corridor.
##### TURN_RATIO
This is used to determine whether one side is open enough to justify a turn.

Example logic:

Turn right if the right distance is at least 2× the left distance
Turn left if the left distance is at least 2× the right distance

This helps prevent false turns caused by small measurement differences or sensor noise.

### PD Centering Control
#### Goal
The robot should stay approximately in the center of the lane while driving forward.

To do this, the code compares the left and right ultrasonic readings and computes an error:
```cpp
error = leftDistance - rightDistance;
```
#### Interpretation of the error
- error = 0 → the robot is centered
- error > 0 → the left side is more open than the right side, so the robot is too close to the right wall
- error < 0 → the right side is more open than the left side, so the robot is too close to the left wall
#### PD Formula
The steering correction is calculated with a PD controller:
```cpp
correction = KP * error + KD * derivative;
```
where:
```cpp
derivative = error - previousError;
```
#### Meaning of each term
- P (Proportional): reacts to how far the robot is from the center
- D (Derivative): reacts to how quickly the error is changing and helps reduce oscillation
The resulting correction is converted into a servo angle around the center position.

### State Machine
The program uses a simple state machine to keep the logic organized.
#### States
- STATE_DRIVE_CENTER
In this state, the robot:
    - drives forward
    - applies PD steering correction
    - monitors the front sensor
    - checks whether a turn should begin
- STATE_TURNING_LEFT
In this state, the robot:
    - sets the steering to maximum left
    - drives forward at turning speed
    - keeps turning until the turn timer is completed
- STATE_TURNING_RIGHT
This works exactly like the left turn state, but mirrored to the right side.
- STATE_FINISHED
This is the final state. The robot stops the motor, centers the servo, and does not continue moving.
### Important Functions
```cpp
percentToPWM(int percent)
```
Converts a speed value from 0–100% into 0–255 PWM, which is required by analogWrite().
```cpp
setMotorForward(int speedPercent)
```
Makes the rear motor move forward at the requested speed.

Internally, it:
- Converts the speed percentage to PWM
- Sets the L298N direction pins for forward motion
- Sends the PWM signal to the motor driver
```cpp
stopMotor()
```
Stops the rear drive motor.
```cpp
readDistanceMM(int trigPin, int echoPin)
```
Reads a single HC-SR04 sensor and returns the measured distance in millimeters.

If no valid echo is received within the timeout, it returns -1.
```cpp
readAllSensors(float &frontMM, float &leftMM, float &rightMM)
```
Reads all three ultrasonic sensors and stores the values in the provided variables.
```cpp
applyPDCentering(float leftMM, float rightMM)
```
Uses the left and right side distances to compute the steering correction and keep the robot centered.

This function:
- checks whether both side readings are valid
- computes the centering error
- computes the derivative term
- applies the PD formula
- converts the result into a servo angle
- constrains the angle to the allowed steering range
- sends the final angle to the servo
```cpp
beginLeftTurn()
```
and
```cpp
beginRightTurn()
```
These functions start a turn by:
- changing the robot state
- storing the turn start time
- steering fully left or fully right
- driving forward at turn speed
```cpp
finishTurnAndReturnToDrive()
```
This function is called when the programmed turn time has elapsed.

It:
- increments the turn counter
- centers the steering
- checks whether the robot already completed the required number of turns
- either returns to STATE_DRIVE_CENTER or performs the final forward movement and stops

### Setup Phase
Inside setup(), the code:
- Starts Serial communication
- Configures the start button with INPUT_PULLUP
- Configures the L298N pins as outputs
- Attaches the servo and centers it
- Configures the ultrasonic sensor pins
- Ensures the motor is stopped at startup
This guarantees that the robot starts in a safe and predictable state.

### Main Loop Behavior
The loop() function is divided into several logical stages.
1. Wait for the Start Button
If the robot has not started yet, it remains stopped and waits for the button to be pressed.
2. Stop if the Mission is Finished
If the robot already completed all required turns, it stays stopped.
3. Run the Control Loop at a Fixed Interval
The program only updates the main control logic every controlIntervalMs milliseconds. This helps keep the PD behavior more stable.
4. Read All Sensors
The robot reads the front, left, and right ultrasonic sensors.
5. Print Debug Information
The code prints the sensor values and the current turn count to the Serial Monitor.
6. Execute the Current State
Depending on the current state, the robot will either:
- drive centered,
- turn left,
- turn right,
- or remain stopped.
### Turn Counting and Final Stop
The robot counts how many 90° turns it has completed using completedTurns.

Once completedTurns reaches totalTurnsNeeded:
- the steering is centered
- the robot moves forward a short extra distance
- the motor stops
- the program enters STATE_FINISHED
This final forward movement helps the robot stop closer to its original starting position instead of stopping immediately at the end of the last turn.
### Parameters That Will Likely Need Calibration
The following values are the most important to tune during real-world testing:
#### Steering / Centering
- KP
- KD
- SERVO_CENTER
- SERVO_MAX_LEFT
- SERVO_MAX_RIGHT
#### Straight Motion
- baseSpeedPercent
#### Turning
- turnSpeedPercent
- turn90TimeMs
#### Corner Detection
- FRONT_TURN_TRIGGER_MM
- TURN_RATIO
#### Final Stop Position
- finalForwardTimeMs
- finalForwardSpeedPercent
### Notes About the Current Turning Method
At the moment, the 90° turn is estimated using time only.
This is a practical solution, but it is not the most precise one because the actual turn angle can vary depending on:
- battery level
- wheel traction
- floor surface
- motor speed consistency
- robot weight distribution
For higher accuracy, a future version of the project could use:
- wheel encoders
- an IMU / gyroscope
- or a more advanced corner-detection strategy based on sensor geometry
### Summary
In short, the robot combines:
- ultrasonic sensing
- PD steering correction
- Ackermann steering
- corner detection
- timed turning
- turn counting
- manual button start
to complete a multi-lap rectangular path while staying centered and performing repeated 90° turns.

## ⚙️ Electromechanical Components
The robot was designed with a modular electromechanical architecture that combines reliable hardware, custom 3D-printed parts, and efficient power distribution. Every component was selected to provide stability, ease of maintenance, and consistent performance throughout the competition.

### 🔋 Power System
The robot is powered by a 4-cell (4S) 18650 lithium battery pack, which supplies the energy required for all electronic and mechanical components. The battery holder includes an integrated power switch, allowing the entire robot to be turned on safely before each run.

The battery pack is connected directly to the L298N motor driver through its +12V and GND terminals. The onboard 5V regulator of the L298N is then used to power a breadboard, which distributes power to the Arduino, sensors, and the remaining electronic devices.

To improve usability during competitions, the robot also includes a push button that starts the autonomous program after the robot has been powered on.

[📷 Power System Image](electromechanical-components/battery/)

### 🧠 Main Controller

The main controller of the robot is an Arduino Mega 2560 R3, which acts as the central processing unit of the entire system. It receives information from the vision system and ultrasonic sensors, processes all navigation decisions, and controls the motors accordingly.

Its compact size, processing capability, and reliable I/O communication make it an excellent choice for autonomous robotics applications.

[📷 Arduino Mega 2560 R3 Image](electromechanical-components/arduino/)

### 👁️ Vision System

The robot uses a Pixy2 Camera to detect the colored obstacle markers placed around the track.

A custom vision algorithm allows the camera to distinguish between red and green objects. Once a color is identified, the corresponding information is transmitted to the Arduino Nano 33 IoT, which decides whether the robot should turn left or right according to the competition rules.

#### Communication Protocol:
The communication protocol will be developed and documented in the second phase of the challenge.  
This section will later describe how the robot exchanges information between the arduino and the Pixy2 Camera, the structure of the transmitted data, and how that communication supports the overall project workflow.

#### Detection Algorithm:
The detection algorithm will also be addressed in the second phase of the challenge.  
At that stage, this section will explain how camera data is processed to identify relevant conditions, events, or targets, and how those detections are integrated into the robot’s navigation and decision-making logic.

[📷 Pixy2 Camera Image](electromechanical-components/pixy2/)

### 📏 Ultrasonic Sensors

Three HC-SR04 ultrasonic sensors are mounted across the front of the robot.

These sensors continuously measure the distance between the robot and nearby walls or obstacles, allowing the robot to navigate safely through the track.

Each HC-SR04 sensor provides non-contact distance measurements from approximately 2 cm to 400 cm, with an accuracy of up to 3 mm.

The sensor arrangement consists of:
- Left ultrasonic sensor
- Center ultrasonic sensor
- Right ultrasonic sensor

Together, these sensors provide the robot with a wider field of view, enabling more accurate obstacle avoidance and wall-following behavior.

[📷 Ultrasonic Sensors](electromechanical-components/ultrasonic-sensors/)

### ⚙️ Drive System
#### DC Motor
The robot is driven by Geartisan 12V 300 RPM DC gear motors.

These motors provide a good balance between speed and torque, allowing smooth movement while maintaining enough power for acceleration, turning, and obstacle avoidance during the competition.

Specifications
- Voltage: 12 V
- Speed: 300 RPM
- Encoder: No

[📷 DC Motor](electromechanical-components/motors/dc-motor/)

#### Servo Motor
The robot uses an MG996R high-torque servo motor to control the steering mechanism of the front wheels. Unlike differential-drive robots, our vehicle follows an Ackermann-inspired steering configuration, allowing it to perform smoother and more realistic turns while maintaining stability throughout the course.

The Arduino Mega 2560 R3 continuously calculates the desired steering angle using data from the Pixy2 camera and the ultrasonic sensors. Based on this information, the servo precisely adjusts the front wheels, enabling the robot to navigate around obstacles, follow the track, and execute accurate parking maneuvers.

The MG996R was selected because of its high torque, fast response, and reliable performance, making it well suited for the steering demands of the WRO Future Engineers challenge.

Specifications:
- Model: MG996R
- Operating Voltage: 4.8–7.2 V
- Control Signal: PWM
- Type: High-Torque Digital Servo

[📷 Servo Motor](electromechanical-components/motors/servo-motor/)

### 🎮 Motor Driver

Motor control is performed using an L298N Dual H-Bridge Motor Driver.

The driver receives movement commands from the Arduino Mega 2560 R3 and regulates the motors accordingly. Besides driving the motors, the L298N also provides a regulated 5V output, which is used to power the breadboard and the robot's low-voltage electronics.

The L298N was selected because it is reliable, easy to integrate, and widely used in educational and robotics projects.

[📷 Motor Driver](electromechanical-components/motor-driver/)

### 🏗️ Mechanical Structure

The chassis was entirely designed by our team and manufactured primarily using 3D printing.

Almost every structural component of the robot is custom-made, allowing us to optimize the placement of electronics, reduce weight, simplify maintenance, and adapt the robot specifically for the WRO Future Engineers challenge.

Only the structural supports and steering mechanism were not 3D printed.

The robot includes:
- 4 wheels
- 8 structural supports
- Structural mounting screws
- Custom 3D-printed chassis

This modular design allows individual components to be replaced quickly without rebuilding the entire robot.

### 🔌 Wiring Diagram

The electrical connections between all components are summarized in the wiring diagram below.

(Insert wiring diagram here.)

### 📸 Component Gallery
The following folder shows images of all the main electromechanical components used in the robot.
- [Electromechanical Components](elechtromechanical-components/)

## ⚡ Power Management
A reliable power distribution system is essential to ensure stable operation of both the electronic and mechanical components during the competition.

The robot is powered by a **4S 18650 lithium battery pack**, which supplies the main power source for the entire system. The battery output is connected directly to the **L298N motor driver** through its **+12V** and **GND** terminals. This allows the driver to power the DC motors while simultaneously providing a regulated **5V output**.

The regulated **5V** and **GND** outputs from the L298N are connected to a **breadboard**, which acts as the central power distribution point for the low-voltage electronics. From there, power is supplied to the **Arduino Mega 2560 R3**, the **Pixy2 camera**, the **MG996R steering servo**, and the **HC-SR04 ultrasonic sensors**.

To improve safety and usability, the robot includes a **main power switch** that disconnects the battery from the entire electrical system when not in use. Additionally, a dedicated **start button** allows the robot to remain powered while delaying the execution of the autonomous program until the official start signal is given.

This power management architecture simplifies wiring, centralizes power distribution, and ensures that all electronic components receive a stable supply voltage throughout the robot's operation.

### ⚡ Power Management Diagram
```mermaid
flowchart TD
    A["🔋 4S 18650 Battery Pack"] --> B["🔘 Power Switch"]
    B --> C["🎮 L298N Motor Driver"]

    C --> D["⚙️ Geartisan 12V DC Motor"]
    C --> E["🔌 5V Regulated Output"]

    E --> F["🍞 Breadboard"]

    F --> G["🧠 Arduino Mega 2560 R3"]
    F --> H["👁️ Pixy2 Camera"]
    F --> I["🚗 MG996R Steering Servo"]
    F --> J["📏 Left HC-SR04"]
    F --> K["📏 Center HC-SR04"]
    F --> L["📏 Right HC-SR04"]
```

### 🫶🏽 Acknowledgements
This project would not have been the same without the support of several people who contributed their time, ideas, feedback, and encouragement throughout its development.

We would especially like to thank:
- **Colegio San Agustín La Chorrera** - for support, their guidance and for providing us with a space to work during the development of the project.
- **Gabriel Rodríguez from Banistmo** — for technical guidance, programming support and feedback.
- **TekBot Lab** — for help with robot design and feedback.

We are grateful for their help and for the role they played in making this project possible.

