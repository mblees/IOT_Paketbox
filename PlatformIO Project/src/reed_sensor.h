#ifndef REED_SENSOR_H
#define REED_SENSOR_H

#include <stdint.h>
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

#define reed_data_pin 36

uint8_t read_reed();
void init_reed();

#ifdef __cplusplus
}
#endif

#endif // REED_SENSOR_H