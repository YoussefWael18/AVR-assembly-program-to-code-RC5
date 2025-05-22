This project demonstrates a smart and secure door locking system that utilizes RFID technology and a servo motor for controlled access. It's an ideal solution for replacing traditional keys with RFID cards, ensuring only authorized users can unlock the door.

How It Works:
The system constantly monitors for an RFID tag using an RFID reader (e.g., RC522).

When a card is scanned:

If the RFID tag is authorized, the servo motor rotates to unlock the door.

If the tag is unauthorized, access is denied and the door remains locked.

A microcontroller (such as Arduino UNO) handles the logic, verifying card IDs and controlling the servo.

Components Used:
RFID Reader Module (RC522)

RFID Tags/Cards

Servo Motor (SG90 or similar)

Arduino UNO (or any microcontroller)

Breadboard and Jumper Wires

Power Supply
