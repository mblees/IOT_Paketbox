#include "rfid.h"
MFRC522 mfrc522(rfid_ss_pin, rfid_reset_pin);

void init_rfid()
{
    mfrc522.PCD_Init();
}

void read_rfid()
{
    // Print UID
    Serial.print("Card UID: ");
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Read data from the card
    byte buffer[18];
    byte bufferSize = sizeof(buffer);

    if (mfrc522.MIFARE_Read(1, buffer, &bufferSize) == MFRC522::STATUS_OK)
    {
        Serial.println("Read data: ");
        for (byte i = 0; i < 16; i++)
        {
            Serial.print(buffer[i] < 0x10 ? " 0" : " ");
            Serial.print(buffer[i], HEX);
        }
        Serial.println();
    }
}