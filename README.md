# TTN Boat Sensor

Project forked from https://github.com/kizniche/ttgo-tbeam-ttn-tracker.

This project intends to create a boat LoRa sensor station to get several metrics and send them via TTN. In this release the sensor station gathers and sends the following variables:

* Boat's battery level
* Whether the battery of the boat is turned on
* Humidity and temperature
* GPS position
* Status of a float switch. A floating switch is placed at the bottom of the bilge.

Then the program sends all these variables via TTN.


To save power we're doing some logic. Apart from tuning the deep sleep time it will only get and send GPS data if we're connected to the main power. We're doing this to prevent GPS to drain the battery too quickly, as waiting for the GPS to be ready consumes a lot of time.

This sensor station will be placed inside a boat, so its enclosure must be water and corrosion resistant. It must be also well fixed to the boat so it does not move or fall when sailing, as it could cause several damage to other components of the boat. Space in boats is limited, so it must be easy to unmount (we don't want to remove meters of cable inside the bilge if we have to remove it temporally). In addition, two antennas will be placed on top of the mast, because GPS and LoRa signals may be blocked or attenuated by the deck.

The main electrical components will be detached from the main battery of the boat because it must be working all the time and we don't want it to eventually drain the battery of the boat. For this reason electronics will use a different power source, so we have also to be sure that electronics use as little power as possible. Anyway, when the battery of the boat is connected, it will charge the batteries of the electronics.


## Hardware

Check list:

- LoRa Board [TTGO Lora T-BEAM V1.1](https://www.aliexpress.com/item/32875743018.html)
- Float switch [like this one](https://www.aliexpress.com/item/33004754249.html)
- DHT-22 humidity and temperature sensor
- Arduino [voltage sensor](https://www.aliexpress.com/item/1005002235375607.html)
- 12V-24V to USB converter.
- Plastic or fiber case of at least 28x35cm
- Din rail
- Li-ION Rechargeable batteries (one at least)
- SMA Male to Female Pigtals.
- Wiring cable, connectors, zip ties...
- Powerbank or battery shield (optional, only intended for more battery life) 
- GPS Antenna (optional)
- USB cables

## Software dependencies

Install Arduino IDE and libraries listed in https://github.com/kizniche/ttgo-tbeam-ttn-tracker:

- Espressif/arduino-esp32 board for Arduino IDE as specified in https://github.com/espressif/arduino-esp32.
- mcci-catena/arduino-lmic (for Rev0 and Rev1)
- mikalhart/TinyGPSPlus (for Rev0 and Rev1)
- lewisxhe/AXP202X_Library (for Rev1 only)
- Only if you want to add the OLED SSD screen: ThingPulse/esp8266-oled-ssd1306 (for Rev0 and Rev1)

## Design

### Program flow
The program simply loops and takes a deep sleep and wakes up as specified in the SEND_INTERVAL. When waking up the program initializes all peripherals and checks if it's connected to the main power. The program checks if we are connected to the main power and if so waits for the GPS for GPS_WAIT_FOR_LOCK seconds. If it is not connected to the main power it won't wait for the GPS and simply will send the LoRa packet instantly.

To calculate the deep sleep time substracts the GPS_WAIT_FOR_LOCK value to SEND_INTERVAL.

### LoRa Packet structure

LoRa Packet structure takes only 9 bytes (1 unused) and is as follows:

```
 0                   1                   2                   3  
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                Encoded Latitude               |               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|       Encoded Longitude       |G|   Humidity  |    Temp   |B|S|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  Btt voltage  |     Unused    |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

(ASCII created thanks to https://github.com/luismartingarcia/protocol.git)

Where: 
- G is whether GPS is valid
- B is whether battery is on
- S is whether the bilge switch is on.
- Btt voltage is the voltage of the boat battery

### Pinout

# Board mount


# Electrical diagram

![block](img/block_diagram.jpg)

