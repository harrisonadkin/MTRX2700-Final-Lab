# MTRX2700-Final-Lab
Code for MTRX2700 Final Demonstration

### Group Members
> Alessandro Savian, Zach Ball, Harrison Adkin

### Roles and Responsibilities
> - Alessandro Savian: Servo initialization, movement calculations and logic, interfacing with drivers.
> - Zach Ball: Presentation, offsets.
> - Harrison Adkin: Calibration, module integration.

### Project Overview
This code uses the gyroscope (L3G4200D) and accelerometer (ADXL345) mounted to the PTU to achieve stabilization in one axis (pitch). This function aims to address various diseases which have the symptom of trembling.

### Module 1 - Calibration
This module aims to address the issue of drifting which is inherent in sensors...

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




## Integration

### Summary

### Testing
