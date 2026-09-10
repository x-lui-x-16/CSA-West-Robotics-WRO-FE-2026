## 👋 Introduction
For the WRO Future Engineers challenge, we built an autonomous robot that combines computer vision, distance sensing, and precise motion control. A **Pixy2 camera** detects colored markers along the track: green means turn left, red means turn right. Three **HC-SR04 ultrasonic sensors** on the front give the robot environmental awareness, letting it detect the front wall and nearby obstacles. Together, vision and ultrasonic sensing let the robot follow navigation rules while avoiding collisions, reliably and adaptively.

## 👥 Our Team
<center><img width="1280" height="960" alt="27fb941c-3ae1-49fe-bac8-5fe324d17b53" src="https://github.com/user-attachments/assets/5fb33422-ca9d-4371-9d21-e53eff33bb84" /></center>

| Photo | Name | Role - Decription |
|:---:|---|---|
| <img width="350" height="480" alt="WhatsApp Image 2026-09-08 at 9 08 41 AM" src="https://github.com/user-attachments/assets/acb792e6-c1ff-4cbe-a9d1-d59af59a60fb" /> | Ernesto Victoria | Coach - 	Guides the team's strategy, training and overall project direction. |
| <img width="350" height="480" alt="WhatsApp Image 2026-08-29 at 6 13 13 PM" src="https://github.com/user-attachments/assets/aab28335-3634-47e3-a587-9c07428ec54b" /> | Zaory Puga | Programmer - 	Develops and refines the robot's navigation and control code. |
| <img width="350" height="480" alt="WhatsApp Image 2026-08-29 at 6 13 14 PM" src="https://github.com/user-attachments/assets/9e392e01-efd8-45e2-b740-1e15d8458a9f" /> | Dereck Cisneros | Mechanic - 	Designs and builds the robot's chassis and mechanical systems. |
| <img width="350" height="480" alt="WhatsApp Image 2026-08-29 at 6 13 13 PM (1)" src="https://github.com/user-attachments/assets/dce56369-6b37-4db8-a421-50e227d17b17" /> | Luis Hidalgo | Mechanic & Programmer — Team Captain - Leads the team, combining mechanical design with programming to integrate the robot's systems. |

## 🛠️ Building Instructions
- Chassis: mostly 3D-printed, with some supports from the [YFROBOT Kit Chassis](https://yfrobot.com/products/steering-gear-robot).
- 3D Models: [printable STL files](models/)
- Electronics: [circuit diagrams](schemes/)
- Code: [Arduino source code](src/)

## 🚗 Mobility
Our robot uses **Ackermann steering**, the same geometry found in real cars, steering only the front wheels while the rear wheels drive. An **MG996R servo** actuates the steering linkage based on decisions from the **Arduino Mega 2560 R3**. Propulsion comes from a **LEGO EV3 Large Motor** on a rigid rear axle. This separation of steering and driving reduces wheel slip, improves traction, and gives smoother, more predictable handling — important for accurate obstacle avoidance and parking.
- [RWD System](mobility/rwd-system/) · [Steering Mechanism](mobility/steering-mechanism/)

## 🎯 Strategy
- **Color detection:** the Pixy2 cam identifies green/red markers; green → turn left, right → turn right.
- **Turn triggering:** the robot drives straight until the front sensor detects the wall is close; side sensors then decide turn direction.
- **Color algorithm & obstacle-avoidance routine:** to be documented in phase 2.

## 💻 Code Overview
The robot: waits for a start button → drives forward with the steering servo held straight (90°), with no wall-following correction → watches the front sensor to detect the front wall → checks side distances to decide turn direction → executes a timed 90° turn via the servo → counts turns → repeats until the required laps are done → makes a final short move and stops.

**Key logic:**
- A simple **state machine** (`DRIVE_STRAIGHT`, `TURNING_LEFT`, `TURNING_RIGHT`, `FINISHED`) organizes behavior.
- The robot drives straight until the front sensor reads a distance below `FRONT_TURN_TRIGGER_MM`, signaling that the front wall is close.
- Turns are currently **time-based** (`turn90TimeMs`), which is simple but can vary with battery level, traction, and surface — a future version could add wheel encoders or an IMU for more precise turning.
- Tunable parameters: servo angles, `baseSpeedPercent`, `turnSpeedPercent`, `turn90TimeMs`, `FRONT_TURN_TRIGGER_MM`, `TURN_RATIO`, final-stop timing.

## ⚙️ Electromechanical Components
- **Power:** 3S 18650 Li-ion battery pack (three 3.7V, 2800 mAh 18650 cells in series) → L298N (+12V/GND) → onboard 5V regulator powers a breadboard distributing to Arduino, sensors, etc. Includes a power switch and a start button.
- **Controller:** Arduino Mega 2560 R3 — processes sensor data and controls the motors.
- **Vision:** Pixy2 Camera detects red/green markers and reports to the Arduino for turn decisions. *(Communication protocol & detection algorithm to be documented in phase 2.)*
- **Ultrasonic sensors:** 3× HC-SR04 (left, center, right), ~2–400 cm range, ~3 mm accuracy — used for obstacle detection and front-wall detection.
- **Drive:** LEGO EV3 Large Motor, with a built-in rotation sensor.
- **Steering:** MG996R digital servo (4.8–7.2V, PWM control).
- **Motor driver:** L298N Dual H-Bridge — also supplies regulated 5V.
- **Chassis:** custom-designed, mostly 3D-printed (4 wheels, 8 supports, mounting screws), optimizing component placement and easy maintenance.

### 🔋 Power System
The robot is powered by a 3-cell (3S) 18650 lithium battery pack, which supplies the energy required for all electronic and mechanical components. The battery holder includes an integrated power switch, allowing the entire robot to be turned on safely before each run.

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
- 
Together, these sensors provide the robot with a wider field of view, enabling more accurate obstacle avoidance and wall-following behavior.

[📷 Ultrasonic Sensors](electromechanical-components/ultrasonic-sensors/)

### ⚙️ Drive System

#### DC Motor

The robot is driven by the EV3 Large Motor.

These motors provide a good balance between speed and torque, allowing smooth movement while maintaining enough power for acceleration, turning, and obstacle avoidance during the competition.

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
<img width="1095" height="541" alt="FE-2026 V3 Wiring Diagram" src="https://github.com/user-attachments/assets/d20d9c9b-f83a-463c-869e-265c230413a5" />
### 📸 Component Gallery

The following folder shows images of all the main electromechanical components used in the robot.
- [Electromechanical Components](elechtromechanical-components/)
📸 [Component gallery](electromechanical-components/)

## ⚡ Power Management

The robot is powered by a **3S 18650 lithium battery pack** pack (three 3.7V, 2800 mAh cells in series), which supplies the main power source for the entire system. The battery output is connected directly to the **L298N motor driver** through its **+12V** and **GND** terminals. This allows the driver to power the DC motors while simultaneously providing a regulated **5V output**.

The regulated **5V** and **GND** outputs from the L298N are connected to a **breadboard**, which acts as the central power distribution point for the low-voltage electronics. From there, power is supplied to the **Arduino Mega 2560 R3**, the **Pixy2 camera**, the **MG996R steering servo**, and the **HC-SR04 ultrasonic sensors**.

To improve safety and usability, the robot includes a **main power switch** that disconnects the battery from the entire electrical system when not in use. Additionally, a dedicated **start button** allows the robot to remain powered while delaying the execution of the autonomous program until the official start signal is given.

This power management architecture simplifies wiring, centralizes power distribution, and ensures that all electronic components receive a stable supply voltage throughout the robot's operation.

## 🫶🏽 Acknowledgements
- **Colegio San Agustín La Chorrera** — guidance and workspace.
- **Gabriel Rodríguez (Banistmo)** — technical guidance, programming support and feedback.
- **TekBot Lab** — help with robot design and technical feedback.
