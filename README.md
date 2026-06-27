# CSA-West-Robotics-WRO-FE-2026
Our repository for WRO future engineers category for this 2026 season

## Repo's Folder Structure/Overview
- [🧊 Models](models/) This directory contains all used 3d models.
- [📁 Other](other/) This directory is empty for now, as no miscellancious files have had to be added.
- [🗺️ Schemes](schemes/) All wiring diagrams can be found in this directory.
- [💻 Source Code](src/) This directory contains all the code used in this proyect.
- [📸 Team Photos](t-photos/) The official Team photos can be found here.
- [📹 Performance Videos](p-videos/) The robot Performance videos for each challenge.
- [🤖🚗 Vehicle Pictures](v-photos/) All vehicle photos can be found in this directory, including some individual components.

## Engineering Materiales
All the materials used to create pur rpbot
- [Arduino Nano 33 IoT](https://docs.arduino.cc/hardware/nano-33-iot) 
- 1 [Pixy2 Cam](https://pixycam-com.translate.goog/pixy2/?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=tc)
- 1 [L298n Motor Driver Board Module](https://naylampmechatronics.com/blog/11_tutorial-de-uso-del-modulo-l298n.html)
- 3 [Ultrasonic Sensors HC-SR04](https://www.amazon.com/-/es/ultrasónico-HC-SR04-detector-distancia-Arduino/dp/B09PBJ4ZY1)
- 1 Small on/off switch
- 1 Push Botton
- 1 Red LED for power indicator
- 1 Resistor ( Ohms) for the power indicator LED
- 26 Proto Wires
- 1 Fuse (1A)
- 1 Fuse Holder
- 1 Power Supply (More of this could be seen on Power Management)
    - 1 Case of 3 18650 Batteries in Series
    - 3 18650 3.7V Battery
- 1 Chasis
    - 4 Wheels
    - 1 [Greartisan DC 12V 300RPM Motor](https://honestforwarder.com/product/greartisan-dc-12v-300rpm-geared-motor-high-torque-electric-micro-speed-reduction-gear-motor-eccentric-output-shaft-37-mm-diameter-gear-D4DQXkS1zP)
    - 1 [MG 996r Servo](https://www.amazon.com/dp/B09BZ5955Z?psc=1&ref_=cm_sw_r_cp_ud_ct_M9EZM05VN4JMKBB2R17X)
    - [Multiply 3d pieces that can be found in the following directory](models/)

## Building instructions
- Most of the chasis was printed in 3D, but there are some supports from the [YFROBOT Kit Chassis](https://yfrobot.com/products/steering-gear-robot).
- Electronics (Circuit and battery): [The circuit diagram can be found in the schemes directory](schemes/)
- Code (For the arduino): [The source code can be found in the src directory](src/)

## Introduction
Brief intro to our solution

For our robotics competition, we developed an innovative autonomous navigation solution that combines computer vision, distance sensing, and precise motion control. Our robot leverages Arduino's vision capabilities through a Pixy2 camera module to detect and interpret color signals placed along the competition field. These signals serve as navigation markers that determine the robot's next movement: a green signal instructs the robot to perform a left turn, while a red signal indicates a right turn. This vision-based approach allows the robot to make accurate decisions in real time while navigating the course.

To improve its environmental awareness and overall maneuverability, the robot is equipped with three ultrasonic sensors, all strategically positioned on the front side. These sensors continuously measure the distance to nearby objects, enabling the robot to detect obstacles, maintain safe navigation, and react quickly to changes in its surroundings. By combining information from the camera and ultrasonic sensors, the robot can simultaneously follow the competition's navigation rules while avoiding collisions.

Our solution demonstrates the effective integration of computer vision, sensor-based perception, and autonomous control algorithms to achieve reliable, accurate, and efficient navigation. This combination of technologies allows the robot to perform consistently in dynamic environments, making it a robust solution for robotics competitions that require both precision and adaptability.

## WRO 2026 Future Engineer Challenge
The WRO 2025 Future Engineers category invites teams to develop a fully autonomous vehicle capable of completing a dynamic driving course. Throughout the competition, the robot must rely on a combination of sensors, computer vision, and intelligent control algorithms to navigate the track, react to randomized elements, and execute precise driving maneuvers without human intervention.

### 📌 Competition Overview
🏁 Open Challenge:
During this stage, the robot is required to complete three full laps around the track. Since the layout includes randomly placed obstacles and changing conditions, the robot must continuously analyze its environment and adapt its navigation strategy in real time.

🚦 Obstacle Challenge:
In addition to navigating the course, the robot must recognize colored traffic markers placed at random positions along the track and react according to the competition rules:

🟥 Red marker: The robot must pass on the right side.
🟩 Green marker: The robot must pass on the left side.

Once the three laps are completed, the robot must locate the designated parking area and successfully perform a parallel parking maneuver inside the marked space, demonstrating a high level of positioning accuracy and vehicle control.

### 📑 Engineering Documentation

Every participating team must maintain a public GitHub repository containing detailed documentation of the project. This includes the robot's mechanical and electronic design, software implementation, engineering decisions, development process, and source code. The purpose of this requirement is to encourage knowledge sharing, transparency, and collaboration within the robotics community.

### 🏆 Evaluation Criteria

Robots are assessed based on several factors, including navigation accuracy, completion time, and the quality of the technical documentation provided by the team. Additional emphasis is placed on the robot's ability to adapt to randomized scenarios while maintaining consistent performance and demonstrating innovative engineering solutions. Beyond technical excellence, the challenge also promotes teamwork, creativity, and effective problem-solving skills.

## Mobility
Our robot uses an Ackerman steering system, with this steering system we can make our robot do the turns that have to be done during the 3 rounds.

## Strategy
Strategy Explanation
Color Detection with Pixy2 Cam:
We integrated a Pixy2 Cam with the Arduino Nano 33 IoT to accurately detect colors. This system allows the robot to recognize green and red colors, which serve as signals to turn left or right, respectively. By using a camera module and appropriate color detection algorithms, the robot can continuously monitor its environment and respond in real time.

Directional Decision Making:
Upon detecting the color green, the robot is programmed to turn left. Conversely, when red is detected, the robot turns right. This color-based decision-making process ensures that the robot navigates efficiently and avoids obstacles or follows a designated path based on the predefined color signals.

Border Detection and Turning:
In addition to color detection, our robot is equipped with ultrasonic sensors to identify the moment when it should turn. It uses an "umbral" which is a certain distance which if the robot pases, it will start to turn to a certain direction. That direction is decided by the other two ultrasonic sensors to the left and to the right.

Implementation Details
Code and Integration:
Our code, available here, outlines the specific algorithms and logic used for color detection, decision-making, and obstacle avoidance. The integration of the vision system with Arduino's control mechanisms is crucial for the robot's functionality.

Color Detection Algorithm:
.......

Obstacle Avoidance Routine:
.......

## Code Explanation
........

## Electromechanical Components




