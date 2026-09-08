## 👋 Introduction
For the WRO Future Engineers challenge, we built an autonomous robot that combines computer vision, distance sensing, and precise motion control. A **Pixy2 camera** detects colored markers along the track: green means turn left, red means turn right. Three **HC-SR04 ultrasonic sensors** on the front give the robot environmental awareness, letting it detect the front wall and nearby obstacles. Together, vision and ultrasonic sensing let the robot follow navigation rules while avoiding collisions, reliably and adaptively.

## 👥 Our Team
<center><img width="1280" height="960" alt="27fb941c-3ae1-49fe-bac8-5fe324d17b53" src="https://github.com/user-attachments/assets/5fb33422-ca9d-4371-9d21-e53eff33bb84" /></center>

| Photo | Name | Role - Decription |
|:---:|---|---|
| _(add photo)_ | Ernesto Victoria | Coach - 	Guides the team's strategy, training and overall project direction. |
| <img width="300" height="380" alt="WhatsApp Image 2026-08-29 at 6 13 13 PM" src="https://github.com/user-attachments/assets/aab28335-3634-47e3-a587-9c07428ec54b" /> | Saory Puga | Programmer - 	Develops and refines the robot's navigation and control code. |
| <img width="300" height="380" alt="WhatsApp Image 2026-08-29 at 6 13 14 PM" src="https://github.com/user-attachments/assets/9e392e01-efd8-45e2-b740-1e15d8458a9f" /> | Dereck Cisneros | Mechanic - 	Designs and builds the robot's chassis and mechanical systems. |
| <img width="300" height="380" alt="WhatsApp Image 2026-08-29 at 6 13 13 PM (1)" src="https://github.com/user-attachments/assets/dce56369-6b37-4db8-a421-50e227d17b17" /> | Luis Hidalgo | Mechanic & Programmer — Team Captain - Leads the team, combining mechanical design with programming to integrate the robot's systems. |

## 🛠️ Building Instructions
- Chassis: mostly 3D-printed, with some supports from the [YFROBOT Kit Chassis](https://yfrobot.com/products/steering-gear-robot).
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

📸 [Component gallery](electromechanical-components/)

## ⚡ Power Management
The 3S 18650 pack feeds the L298N (+12V/GND), whose regulated 5V output powers a central breadboard supplying the Arduino, Pixy2 camera, servo and ultrasonic sensors. A main power switch disconnects the battery when idle; a separate start button delays the autonomous program until the official start signal.
## 🫶🏽 Acknowledgements
- **Colegio San Agustín La Chorrera** — guidance and workspace.
- **Gabriel Rodríguez (Banistmo)** — technical guidance, programming support and feedback.
- **TekBot Lab** — help with robot design and technical feedback.
