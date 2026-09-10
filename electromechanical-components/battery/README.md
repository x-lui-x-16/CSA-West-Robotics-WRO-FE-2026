# 🔋 Battery Pack
The robot is powered by a 3S 18650 Li-ion battery pack: three 3.7V, 2800 mAh cells connected in series, giving a nominal voltage of ~11.1V.

The pack connects directly to the L298N motor driver (+12V/GND), which also provides the regulated 5V used by the Arduino, sensors, and servo. A main power switch allows the robot to be safely turned on and off before and after each run.
