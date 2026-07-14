## Hardware Architecture
The robot is built around an **Arduino Mega 2560 R3** as the main controller and follows a **rear-wheel-drive configuration with Ackermann steering**.  
Forward motion is provided by a **12V DC rear motor** driven through an **L298N motor driver**, while steering is controlled by an **MG996R servo motor** mounted on the front axle.  
Three **HC-SR04 ultrasonic sensors** are used to measure distances to the front, left, and right sides of the robot, allowing it to navigate corridors and evaluate turns.  
The prototype also includes a **start push button**, a **power indicator LED**, and a **main on/off switch** integrated into the battery supply line.

At the current stage of development, the robot is powered by a **3-cell 18650 battery pack**, with the **L298N motor driver acting as the main power entry point**.  
Low-voltage devices such as the Arduino, ultrasonic sensors, servo, and LED are supplied through the **5V rail distributed from the L298N regulator to the breadboard**.

---

## Power Distribution
The robot uses **three 18650 lithium-ion cells** arranged as a **3-cell series battery pack**.  
This battery pack supplies the motor driver directly and, through the L298N’s onboard regulator, also powers the low-voltage electronics.

### Battery configuration
- **Battery type:** 18650 Li-ion
- **Number of cells:** 3
- **Nominal voltage per cell:** 3.7 V
- **Fully charged voltage per cell:** ~4.1 V
- **Total pack voltage:** approximately **11.1 V to 12.6 V**

### Main power path
```text
Battery Pack (+) → On/Off Switch → L298N +12V
Battery Pack (-) → L298N GND
```
### Low-voltage distribution
The 5V output of the L298N is routed to the breadboard power rail, which then powers the rest of the low-voltage components.
```text
L298N 5V → Breadboard 5V rail
L298N GND → Breadboard GND rail
```
From the breadboard rails, power is distributed to:
- Arduino Mega 2560
- MG996R steering servo
- Front HC-SR04 ultrasonic sensor
- Left HC-SR04 ultrasonic sensor
- Right HC-SR04 ultrasonic sensor
- Power indicator LED

## Wiring Overview
This section describes the robot’s wiring as a functional connection diagram in text form, showing how power and signals flow between the main components.
### Global power flow
```text
4x 18650 Battery Pack (+)
        ↓
     On/Off Switch
        ↓
   L298N +12V terminal

4x 18650 Battery Pack (-)
        ↓
    L298N GND
```
The L298N then performs two main tasks:
- Drives the rear DC motor through its output terminals.
- Supplies 5V to the breadboard rail, which powers the Arduino and the rest of the low-voltage electronics.

## Arduino Mega 2560 Connections
The Arduino Mega 2560 acts as the central controller of the robot.
It receives sensor data, reads the start button, controls the rear drive motor through the L298N, and commands the steering servo.
### Arduino pin usage
```text
Arduino Mega 2560
│
├── D2  → MG996R Servo signal
├── D3  → L298N IN2
├── D4  → L298N IN1
├── D5  → L298N ENA
├── D7  → Start Push Button
├── D8  → Front HC-SR04 TRIG
├── D9  → Front HC-SR04 ECHO
├── D10 → Left HC-SR04 TRIG
├── D11 → Left HC-SR04 ECHO
├── D12 → Right HC-SR04 TRIG
├── D13 → Right HC-SR04 ECHO
├── 5V  → Breadboard 5V rail
└── GND → Breadboard GND rail
```
## Rear Drive System
The robot uses a single rear DC motor for propulsion.
This motor is not connected directly to the Arduino. Instead, it is controlled through one channel of the L298N motor driver.

Control signal path
```text
Arduino D5  → L298N ENA
Arduino D4  → L298N IN1
Arduino D3  → L298N IN2
```
- ENA controls motor speed through PWM.
- IN1 and IN2 control the rotation direction of the motor.
Rear motor output path
```text
L298N OUT1 → Rear DC Motor terminal 1
L298N OUT2 → Rear DC Motor terminal 2
```
## Steering System
The front steering mechanism is controlled by an MG996R servo motor connected to the Arduino.
### Servo wiring
```text
Arduino D2         → Servo signal
Breadboard 5V rail → Servo VCC
Breadboard GND rail→ Servo GND
```
The servo is responsible for positioning the front wheels according to the Ackermann steering logic of the robot.

## Ultrasonic Sensing System
The robot uses three HC-SR04 ultrasonic sensors to measure distances in front of the robot and on both sides of the chassis.
### Front ultrasonic sensor
```text
Front HC-SR04 VCC  → Breadboard 5V rail
Front HC-SR04 GND  → Breadboard GND rail
Front HC-SR04 TRIG → Arduino D8
Front HC-SR04 ECHO → Arduino D9
```
The front sensor is used to detect the end of a straight path or the presence of a wall ahead.
### Left ultrasonic sensor
```text
Left HC-SR04 VCC  → Breadboard 5V rail
Left HC-SR04 GND  → Breadboard GND rail
Left HC-SR04 TRIG → Arduino D10
Left HC-SR04 ECHO → Arduino D11
```
The left sensor measures the distance between the robot and the left wall and is used for centering and navigation corrections.
### Right ultrasonic sensor
```text
Right HC-SR04 VCC  → Breadboard 5V rail
Right HC-SR04 GND  → Breadboard GND rail
Right HC-SR04 TRIG → Arduino D12
Right HC-SR04 ECHO → Arduino D13
```
The right sensor measures the distance between the robot and the right wall and works together with the left sensor to keep the robot centered inside the corridor.

## Start Button and User Input
The robot includes a push button that is used to manually start the program.
### Button wiring
```text
Arduino D7 → One side of push button
Arduino GND → Other side of push button
```
The code uses INPUT_PULLUP, which means:
- the pin remains HIGH when the button is not pressed,
- the pin becomes LOW when the button is pressed and connected to ground.
This allows the robot to remain idle until the user explicitly starts the routine.

## Power Indicator LED
A red LED is connected as a power indicator to show when the 5V system is active.
### LED wiring
```text
Breadboard 5V rail → 1 kΩ resistor → LED anode (+)
LED cathode (-) → Breadboard GND rail
```
Whenever the breadboard 5V rail is powered, the LED turns on and indicates that the low-voltage electronics are energized.

## Connection Tables
### Arduino Mega 2540 Pin Map
| Arduino Pin | Connected Component | Function |
| --- | --- | --- |
| D2 | MG996R Servo Signal | Steering control |
| D3 | L298N IN2 | Rear motor direction control |
| D4 | L298N IN1 | Rear motor direction control |
| D5 | L298N ENA | Rear motor PWM speed control |
| D7 | Push Button | Manual program start |
| D8 | Front HC-SR04 TRIG | Front distance trigger |
| D9 | Front HC-SR04 ECHO | Front distance echo |
| D10 | Left HC-SR04 TRIG | Left distance trigger |
| D11 | Left HC-SR04 ECHO | Left distance echo |
| D12 | Right HC-SR04 TRIG | Right distance trigger |
| D13 | Right HC-SR04 ECHO | Right distance echo |

### L298N Motor Driver Connections
| L298N Pin | Connected To | Purpose |
| --- | --- | --- |
| ENA | Arduino D5 | Rear motor PWM speed control |
| IN1 | Arduino D4 | Rear motor direction control |
| IN2 | Arduino D3 | Rear motor direction control |
| OUT1 | Rear DC Motor Terminal 1 | Motor output |
| OUT2 | Rear DC Motor Terminal 2 | Motor output |
| +12V | Battery Pack Positive Through Switch | Main motor supply |
| GND | Battery Negative / Breadboard Ground | Common ground |
| +5V | Breadboard 5V Rail | Low-Voltage power distribution |

### Ultrasonic Sensor Conections
| Sensor | Pin | Connected to |
| --- | --- | --- |
| Front HC-SR04 | TRIG | Arduino D8 |
| Front HC-SR04 | ECHO | Arduino D9 |
| Front HC-SR04 | VCC | 5V breadboard rail |
| Front HC-SR04 | GND | GND breadboard rail |
| Left HC-SR04 | TRIG | Arduino D10 |
| Left HC-SR04 | ECHO | Arduino D11 |
| Left HC-SR04 | VCC | 5V breadboard rail |
| Left HC-SR04 | GND | GND breadboard rail |
| Right HC-SR04 | TRIG | Arduino D12 |
| Right HC-SR04 | ECHO | Arduino D13 |
| Right HC-SR04 | VCC | 5V breadboard rail |
| Right HC-SR04 | GND | GND breadboard rail |

### Additional Components
| Component | Connection |
| --- | --- |
| MG996R Servo Signal | Arduino D2 |
| MG996R Servo VCC | 5V breadboard rail |
| MG996R Servo GND | GND breadboard rail |
| Push Button | Arduino D7 and GND |
| Red Power Indicator LED | 5V rail → 1 kΩ resistor → LED → GND  |
| On/Off Switch | In series between battery positive and L298N +12V pin |

## Common Ground Architecture
A common ground is essential for correct operation.
The following grounds are electrically connected together:
- Battery negative terminal
- L298N GND
- Arduino GND
- Servo GND
- Front ultrasonic sensor GND
- Left ultrasonic sensor GND
- Right ultrasonic sensor GND
- LED GND
- Push button ground
Without a common ground reference, the control signals from the Arduino may not be interpreted correctly by the motor driver, servo, or sensors.

## Electrical Design Notes
1. Rear motor connection
The rear DC motor must be connected to the OUT1 and OUT2 terminals of the L298N.
It should not be connected directly to the Arduino or to the control pins IN1 and IN2.
2. Servo power considerations
The MG996R servo can draw a significant amount of current, especially under load.
In the current prototype, it is powered from the same 5V rail used by the Arduino and ultrasonic sensors, with that rail being supplied by the L298N regulator.

This configuration is acceptable for a prototype, but for a more robust version of the robot, a dedicated 5V regulator or separate high-current 5V supply for the servo would be recommended.
3. L298N regulator limitations
The onboard 5V regulator of the L298N is convenient for small loads, but it is not ideal for powering multiple current-demanding devices simultaneously.
Because this robot powers the Arduino, the servo, the ultrasonic sensors, and the LED from the same 5V source, the power system should be monitored under load.
4. Common symptoms of power instability
If the robot shows any of the following symptoms:
- Arduino resets,
- servo jitter,
- unstable ultrasonic readings,
- reduced motor performance,
the first subsystem that should be checked is the power distribution stage.

## Prototype Scope
This wiring description corresponds to the current prototype stage of the robot.
Additional components such as the Pixy2 camera, communication interfaces, or other sensing modules may be integrated in future development phases and documented in updated hardware and wiring sections.

## Hardware Summary
- **Main controller:** Arduino Mega 2560 R3  
- **Drive motor:** Greartisan DC 12V 300RPM motor  
- **Steering actuator:** MG996R servo  
- **Motor driver:** L298N  
- **Distance sensors:** 3 × HC-SR04 ultrasonic sensors  
- **User controls:** Push button + on/off switch  
- **Power indicator:** Red LED with 1 kΩ resistor  
- **Power source:** 4 × 18650 Li-ion cells in series

## Future Hardware Integration
- Pixy2 camera integration
- color detection subsystem
- communication protocol
- extended detection algorithm
