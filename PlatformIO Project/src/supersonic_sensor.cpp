#include "supersonic_sensor.h"

void init_us()
{
    pinMode(us_trig_pin, OUTPUT);
    pinMode(us_echo_pin, INPUT);
}

float read_us()
{
    float duration = 0;
    float distance = 0;

    digitalWrite(us_trig_pin, LOW);
    delayMicroseconds(2);

    digitalWrite(us_trig_pin, HIGH);
    delayMicroseconds(12);

    digitalWrite(us_trig_pin, LOW);

    duration = pulseIn(us_echo_pin, HIGH);
    distance = (duration * 0.0343) / 2;

    if (distance > MAX_DISTANCE || distance <= 0)
    {
        return -1;
    }
    else
    {
        return distance;
    }
}

float read_us_average(){
    float distance = 0;
    float additive = 0;
    uint8_t confirmation_counter = 0;

    for(int i = 0; i <= 10; i++){
        additive = read_us();
        if(additive == -1){
            i--;
            confirmation_counter++;
        }
        else{
            distance += additive;
        }
        if(confirmation_counter == 10){
            return -1;
        }
    }
    return distance / 10;
}