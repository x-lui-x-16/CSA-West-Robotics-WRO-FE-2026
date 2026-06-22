# CSA-West-Robotics-WRO-FE-2026
Our repository for WRO future engineers category for this 2026 season

## Engineering Materiales
All the materials used to create pur rpbot
- Arduino Nano RP2040 (https://docs.arduino.cc/tutorials/nano-rp2040-connect/rp2040-01-technical-reference/) 
- 1 Pixie 2.0 cam
- 3 Ultrasonic Sensors (1 at front and the other two in the left and right)
- 1 Small on/off switch
-
-
-
-
-
-
-
-
- 1 Chasis
    - 4 Wheels
    - 1 Motor
    - 1 Servo
-Multiply 3d pieces that can be found in the following directory
## Building instructions
- The chasis was printed in 3D
- Electronics (Circuit and battery): [The circuit diagram can be found in the schemes directory](schemes/)
- Code (For the arduino): [The source code can be found in the src directory](src/)
- ## Contents
-[Models](models/) This directory contains all used 3d models
- [Other](other/) This directory is empty for now, as no miscellancious files have had to be added
- [Process](process/) This directory will be completed for the national as it will contain the process that it took for us to get there
- [Schemes](schemes/) All wiring diagrams can be found in this directory
- [Source Code](src/) This directory contains all the code used in this proyect
- [Team Photos](t-photos/) The official Team photos can be found here
- [Performance Videos](p-videos/) The robot Performance videos for each challenge
- [Vehicle Pictures](v-photos/) All vehicle photos can be found in this directory, including some individual components
This is just a test to see if content linking works

## Introduction
Brief intro on our solution

For our robotics competition, we developed an innovative navigation solution that leverages Arduino's vision capabilities to detect and respond to color signals.Our robot uses a camera module to identify red and green signals, which indicate the direction it should turn. A green signal represents a left turn, while a red signal represents a right turn..

To enhance our robot's awareness and maneuverability, in consecuence, the robot is equipped with three ultrasonic sensors all of them located at the front side of the robot. These sensors also provide real-time distance measurements, enabling the robot to detect and avoid obstacles from multiple directions. Our approach demonstrates the synergy of vision technology, sensor-based navigation, and precise control to create a reliable and efficient robotic solution.

## Mobility
Our robot uses an Ackerman steering system, with this steering system we can make our robot do the turns that have to be done during the 3 rounds.

Some of the problem we had was during the ensamble of the motor because of problem with the measure during the 3d printing
                (Especificaciones de giro y chasis faltantes)

## Strategy
Strategy Explanation
Color Detection with Arduino:
We integrated a Nicla vision with the arduino nano every to accurately detect colors. This system allows the robot to recognize green and red colors, which serve as signals to turn left or right, respectively. By using a camera module and appropriate color detection algorithms, the robot can continuously monitor its environment and respond in real time.

Directional Decision Making:
Upon detecting the color green, the robot is programmed to turn left. Conversely, when red is detected, the robot turns right. This color-based decision-making process ensures that the robot navigates efficiently and avoids obstacles or follows a designated path based on the predefined color signals.

Border Detection and Turning:
In addition to color detection, our robot is equipped with ultrasonic sensors to identify the moment when it should turn. It uses an "umbral" which is a certain distance which if the robot pases, it will start to turn to a certain direction. That direction is decided by the other two ultrasonic sensors to the left and to the right.

Implementation Details
Code and Integration:
Our code, available here, outlines the specific algorithms and logic used for color detection, decision-making, and obstacle avoidance. The integration of the vision system with Arduino's control mechanisms is crucial for the robot's functionality.

Color Detection Algorithm:
The algorithm processes the camera feed to identify the presence of green or red. This involves filtering the image to isolate these colors and then using thresholding techniques to determine the direction.

![image](https://github.com/user-attachments/assets/7844fdab-804c-47e1-aa19-511a60d0ce33)   (antigua)


Obstacle Avoidance Routine:
When the sensors detect an obstacle, the robot executes a series of steps to navigate around it. This includes stopping, scanning the surroundings, calculating an alternate path, and resuming its movement while continuing to rely on the color signals for direction.








