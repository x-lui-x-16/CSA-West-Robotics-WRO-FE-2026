# 🧠 Arduino Mega 2560 R3
The Arduino Mega 2560 R3 is the main controller of the robot. It reads data from the Pixy2 camera and the three HC-SR04 ultrasonic sensors, runs the navigation logic, and sends commands to the steering servo and the drive motor through the L298N driver.

It was chosen for its large number of I/O pins, enough to handle all sensors, the servo, the motor driver, and the start button at the same time.
