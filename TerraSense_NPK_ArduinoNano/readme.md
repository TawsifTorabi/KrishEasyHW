# Arduino RS485 NPK Sensor Serial Interface

## Overview

This Arduino sketch allows communication with an RS485-based 5-in-1 NPK sensor. It reads data for:

*   Temperature
*   Soil pH
*   Nitrogen (N)
*   Phosphorus (P)
*   Potassium (K)

Data is requested **on demand** via Serial. When the command `sendData` is sent over Serial, the Arduino reads the sensor values and responds with a comma-separated string.

## Hardware Setup

*   **Microcontroller:** Arduino Nano / Uno
*   **RS485 Transceiver:** MAX485 or similar
*   **Sensor Connection:** 5-in-1 NPK sensor (Modbus RTU)

### Pin Configuration

*   `D2` - RX (to RO of MAX485)
*   `D3` - TX (to DI of MAX485)
*   `D7` - DE (Driver Enable)
*   `D8` - RE (Receiver Enable)

## How It Works

1.  The Arduino listens on Serial (9600 baud) for a string input.
2.  If the input equals `sendData`, the Arduino:
    *   Performs a Modbus RTU read for each sensor value.
    *   Waits briefly between requests for reliability.
    *   Outputs a formatted string with all sensor readings.

### Example Output Format

tem-23,ph-6.8,n-120,p-50,k-80

## Serial Command

Send the following command via the Arduino Serial Monitor or any serial tool:

sendData

### Serial Monitor Settings

*   **Baud Rate:** 9600
*   **Line Ending:** `Newline` or `Both NL & CR`

## Modbus RTU Details

Each sensor parameter is accessed via its own Modbus request (Function 0x03 - Read Holding Registers):

*   **Temperature:** Register 0x0001
*   **pH:** Register 0x0003
*   **Nitrogen:** Register 0x0004
*   **Phosphorus:** Register 0x0005
*   **Potassium:** Register 0x0006

Each request is 8 bytes and the response is parsed from bytes \[3\] and \[4\].

## Code Snippet

The logic for sending the data on demand is based on buffered serial input:

```
if (serialInput == "sendData") {
  // Read sensors and print output
  Serial.print("tem-"); Serial.print(tempVal);
  ...
}
```

## Limitations

*   Sensor reads take ~1 second due to Modbus delays.
*   No CRC validation in response parsing (basic 7-byte buffer only).
*   No retry mechanism for failed sensor reads.
*   Response values are assumed to be 16-bit integers.

## Author

Developed by Gazi Tawsif Turabi  
_Center for Artificial Intelligence & Robotics, UIU_