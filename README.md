# IoT-Projekt – Paketbox Dokumentation

## Übersicht:

### 1. Hardware
   #### 1.1 Box
   Das Gerüst der Paketbox besteht aus MiniTec-Aluprofilen, die zum Halten von 4 mm dicken Spanholzplatten genutzt werden. Der Deckel wird durch 2 Scharniere mit dem Körper der Box verbunden.

   #### 1.2 Sensoren/andere Hardware
   - Ultraschallsensor: HC-SR04
       - Da der Sensor auf 5V läuft und die GPIO-Pins des ESP32 nur 3,3V vertragen, muss ein Spannungsteiler bestehend aus 2 10k Ohm Widerständen verwendet werden. Das senkt die Spannung allerdings nicht genau auf 3,3V, deshalb muss in der Software damit gerechnet werden.
   - Reed-Modul: KY-021
       - Wird mit 3,3V versorgt, daher muss hier nichts Besonderes beachtet werden.
   - Schrittmotor: 28BYJ-48
       - Wird mit 5V über den dazugehörigen Motortreiber versorgt.
   - Matrixtastatur: [Link zur Tastatur](https://www.az-delivery.de/products/4x4-matrix-keypad)
       - Aufgrund mangelnder Pins verwende ich die 4x4 Matrix nur als 2x2 Matrix mit den Tasten 1, 2, 4, 5.
   - Stromversorgung durch eine Powerbank mit 5V Ausgang.

   #### 1.3 Mikroprozessor
   Beim Mikroprozessor handelt es sich um den WiFi-LoRa-32-V2 der Firma Heltec Automation mit eingebautem LoRa-Modul, Display und integrierter LED. Um Energie zu sparen, werden sowohl das Display als auch die integrierte LED nicht verwendet.

   #### 1.4 Verschlussmechanismus
   Der Verschlussmechanismus besteht aus einem Stepper Motor mit einem Zahnrad, welches einen Kolben durch 2 Ösen schiebt. Die Ösen sind jeweils am Deckel oder am Körper der Box befestigt und verhindern, wenn der Kolben ausgefahren ist, dass sich der Deckel öffnen lässt.
   ![WhatsApp Bild 2024-02-06 um 20 21 44_378a7dea](https://github.com/mblees/IOT_Paketbox/assets/104490472/fe967090-578b-4d9d-857b-74d28b1b5561)

   Anmerkung: Hier handelt es sich Budgetverschuldet um 3D-gedruckte Teile welche in eienr realen Anwendung nicht sicher genug wären um ein Paket mit Wert zu sichern.

### 2. Software
   #### 2.1 C++-Part / Mikroprozessorprogrammierung
   Die Programmierung des Controllers beruht auf dem Framework/Example LMIC-node von lnlp ([GitHub-Link](https://github.com/lnlp/LMIC-node)). Ich habe eine logische Steuerung in der `main()`-Funktion hinzugefügt sowie Bibliotheken für alle Peripheriekomponenten:
   - `Matrix.h`/`Matrix.cpp`: Beinhaltet das Auslesen der Matrix-Tastatur unter Verwendung der Bibliothek: `chris--a/Keypad@^3.1.1`.
   - `Reed_sensor.h`/`Reed_sensor.cpp`: Beinhaltet das Auslesen des Reed-Sensors, das über ein DigitalReed geschieht.
   - `Rfid.h`/`Rfid.cpp`: Beinhaltet Funktionen, um einen RFID-Sensor zu verwenden. Diese Funktion wurde letztendlich nicht genutzt, da der Mikrocontroller nicht genug Pins übrig hat.
   - `Stepper.h`/`Stepper.cpp`: Beinhaltet die Ansteuerung des Schrittmotor-Treibers unter Verwendung der Bibliothek: `waspinator/AccelStepper@^1.64`.
   - `Supersonic_sensor.h`/`Supersonic_sensor.cpp`: Beinhaltet das Auswerten des Ultraschallsensors und eine Funktion, die einen Mittelwert bildet, da der Sensor ab und zu falsche Werte liefern kann.

   #### 2.2 Python Service
   Der Service nutzt die HomeAssistantAPI, um Push-Benachrichtigungen an Handys zu schicken und die `paho-mqtt`-Bibliothek, um die von TTN empfangenen LoRa-Daten auszuwerten und daraufhin einen `notify`-Service in HomeAssistant auszulösen.

### 3. Datenübertragung
   Die Daten, die mit den Sensoren erfasst werden, werden beim Öffnen und Schließen der Box vom Mikrocontroller über LoRa und The Things Network (TTN) gesendet. TTN stellt die Daten über einen MQTT-Server zur Verfügung, welche wir mithilfe eines Python-Services abfangen und daraufhin einen Service in HomeAssistant auslösen. Der Service in HomeAssistant führt dann wiederum dazu, dass eine Push-Benachrichtigung auf dem Handy des Besitzers der Box erscheint.

   Sensoren -> ESP32 -> LoRa -> TTN -> MQTT -> Python Service -> HomeAssistant -> Mobiltelefon

### 4. Pinbelegung

![Screenshot 2024-02-06 195223](https://github.com/mblees/IOT_Paketbox/assets/104490472/6597162c-f7ba-4976-bddb-5b58aae3a955)

| Gerät                | Pins                    |
|----------------------|-------------------------|
| Matrixtastatur       | 0, 2, 23, 25            |
| Steppermotor         | 12, 13, 17, 21          |
| Reed Sensor          | 36                      |
| Ultraschallsensor    | 22, 37                  |
| LoRa Modul (Werk)    | 19, 18, 5, 15, 4, 16, 26, 27, 14 |

### 5. Anmerkungen
Um weitere Features wie einen RFID-Sensor hinzuzufügen, fehlen dem verwendeten ESP32 weitere Pins. Eine mögliche Alternative war in diesem Fall der STM-WL55JC mit LoRa-Antenne. Allerdings gibt es für diesen Mikrocontroller keine öffentlichen LoRa-Bibliotheken, die für dieses Projekt in Frage gekommen wären. Ich habe versucht, eine Bibliothek für diesen Controller selbst zu schreiben, habe aber nach einigen Stunden Arbeit keine Ergebnisse erzielen können.
