#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h>
#include <Arduino.h>
#include <MFRC522.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <AccelStepper.h>
#include <Arduino.h>

const byte Fullstep = 4;
const byte Halfstep = 8;
const short fullRevolution = 2038;
const float SteppDegree = 5.66;

void init_stepper();
void open_door();
void close_door();

#ifdef __cplusplus
}
#endif

#endif // STEPPER_H
