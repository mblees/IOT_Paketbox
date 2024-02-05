#include "reed_sensor.h"

void init_reed()
{
    pinMode(reed_data_pin, INPUT);
}

uint8_t read_reed()
{
    return digitalRead(reed_data_pin);
}