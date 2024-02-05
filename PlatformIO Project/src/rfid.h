#ifndef RFID_H
#define RFID_H

#include <stdint.h>
#include <Arduino.h>
#include <MFRC522.h>

#ifdef __cplusplus
extern "C" {
#endif

#define rfid_sck_pin 12
#define rfid_mosi_pin 17
#define rfid_miso_pin 0
#define rfid_ss_pin 21
#define rfid_reset_pin 13
#define rfid_irq_pin 33

void read_rfid();
void init_rfid();

#ifdef __cplusplus
}
#endif

#endif // RFID_H
