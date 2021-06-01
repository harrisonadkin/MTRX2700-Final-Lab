
# MTRX2700-Final-Lab
Code for MTRX2700 Final Demonstration

### Group Members
> Alessandro Savian, Zach Ball, Harrison Adkin

### Roles and Responsibilities
> - Alessandro Savian: Servo initialization, movement calculations and logic, interfacing with drivers.
> - Zach Ball: Servo logic, offsets, presentation, .
> - Harrison Adkin: Calibration, module integration.

### Project Overview
This code uses the gyroscope (L3G4200D) and accelerometer (ADXL345) mounted to the PTU to achieve stabilization in one axis (pitch). This function aims to address various muscle degenerative diseases which have the symptom of trembling. Through countering this we aim to provide such people with a means to complete everyday tasks and thus maintain a normal life.

The system block diagram comes in three major modules as below: 
**<img width="908" alt="Modular Diagram " src="https://user-images.githubusercontent.com/79881907/120250371-36df1b80-c2c1-11eb-936e-9fc3d0f1986e.png">

### Module 1 – Interfacing
This initial module aimed to provide seamless connection to everyday users, by providing them with a connection both in software and hardware to the device. Moreover, the use of the buzzer to provide auditory prompts allowed users to best interact with the machine, particularly with no prior understanding of the practise of Mechatronics.
The interaction through software utilised a two way serial communication, which would print information or read from a terminal program PuTTY. This was done through a serial module that operated with an input, a function and a baud rate. Note that in hardware, any calling of serial port 0 must be removed (commented) as it creates interference errors with the interrupts. Also note that varying baud rate must be considered to facilitate correct information parsing. 

*Serial block diagram*
<img width="616" alt="Screen Shot 2021-06-01 at 10 22 52 am" src="https://user-images.githubusercontent.com/79881907/120251010-7575d580-c2c3-11eb-8d8e-7aeaef8c6da3.png">

---

The second interfacing interaction was in hardware, through the utilisation of the liquid crystal display unit. This was particularly useful to update real time instructions when using the board to drive the circuit (i.e: when the buttons were used in calibration). This was chosen to allow a connection in hardware that would communication throughout operation, if say, the code were used to drive a real-world device that needed to communicate with user. The system was chosen to operate without a cursor or blinking, to prevent the false interpretation of active communication. 

*LCD block diagram*
<img width="550" alt="Screen Shot 2021-06-01 at 10 22 55 am" src="https://user-images.githubusercontent.com/79881907/120251019-7e66a700-c2c3-11eb-9e51-c45d5c6f728e.png">

---

Finally, the use of the buzzer through an implemented "music module" allowed both a boot and error noise signal to provide the user with an auditory que on correct use. In particular the boot noise was to signal not to use the hardware until boot had completed (with a complementary boot LCD instruction) and the error noise was leveraged to prevent misuse of the board (i.e physically disrupting the servos to incorrect & harmful positions). This was done through an output compare that triggered the buzzer to operate at different PWM frequencies based on the respective note, and hold for a certain duration. Varying scores for any buzzer sound can be implemented within the module.  

*Music Module block diagram*
<img width="359" alt="Screen Shot 2021-06-01 at 10 23 07 am" src="https://user-images.githubusercontent.com/79881907/120251064-ab1abe80-c2c3-11eb-9c7f-1aadcea7a774.png">

---

Ultimately, these three modules were triggered through a boot/help function that initialised on running the script. Despite this providing no additional features to the system, it housed this module and compartmentalised how the three interfacing systems were used. 

*Help Module block diagram*
<img width="469" alt="Screen Shot 2021-06-01 at 10 22 59 am" src="https://user-images.githubusercontent.com/79881907/120251070-afdf7280-c2c3-11eb-90b5-b9930a0da4ee.png">

#### Best Use
The Serial operates with the following inputs:
Where the BaudRate was set to 156 for our operation, the interface was 1 for hardware and the function was determined based on read/write.
```
SerialInitialise(BaudRate, Interface, Function, String_Pointer)
```

The musicmodule operates with no input with the following command:
```
bootjingle()
```

The LCD module operates with the following inputs:
Where CMD / DATA indicated wether the input was a command function to perform a task (i.e: move to next line) or data to write.
```
writeLCD(String_Pointer, CMD/DATA)
```


### Module 2 - Calibration
This module aims to address the issue of drifting which is inherent in sensors. This module calculates the error offsets for later data cleaning as well as general testing of the hardware. This module includes the calibration procedure prompts given to the user through the liquid crystal display, as well as the calibration calculations itself. 

 4 seperate strings are used to demonstrate each of the tasks.
#### Interfacing

\\HOW TO

```
LDX #String_1
JSR allUppercase
```

To run task 2, uncomment

```
LDX #String_2
JSR allLowercase
```
To run task 3, uncomment
```
LDX #String_3
JSR everyWordStartUpper
```
To run task 4, uncomment
```
LDX #String_4
JSR everySentenceStartUpper
```

Check the string using `SPC String_Number` in CodeWarrior.

### Valid input

Any combination of letters, whitespaces and fullstops are considered to be valid.

### Module 2 - Logic


#### Interfacing

This module consists of five functions which take the following structs, `GyroRaw`, `AccelRaw`, `AccelScaled`, `rotation` and `duty` which take the following forms,

```
rotation {
  float pitch;
  float previous_pitch;
}

duty {
  int current;
  float min;
  float max;
  float factor;
}

raw/scaled {
  float z;
  float y;
  float x;
}
```
These structs undergo certain conversions to bring about the intended function of the system through the following functions,

`convertUnits`
Takes the raw acceleration values then transforms them into ones which are a function of gravity. Done by using the constants define in the ADXL345 datasheet, which depend on control register settings.

`GyroRotation`
Intakes the raw gyroscope values, converts them to degrees/second and then performs real-world mathematical displacement equations on them and returns how far the PTU has been displaced as a product of these measurements.

`AccelRotation`
Intakes the current acceleration values in the x, y and z directions then uses trigonometry to return new orientation of the PTU.

`DistCalcs`
Requires the structs which hold information on changes in orientation. Uses these in conjunction and weights them according to inputted variables to calculate the angles which the servos must go to in order to oppose relative motion. Then returns these angles in a `rotation` struct.

`changePitch`
Converts the angles in the `rotation` struct to be in terms of duty cycle which can be assigned to the corresponding PWMDTYXX registers to achieve the module intended function.

### Testing
1. 



