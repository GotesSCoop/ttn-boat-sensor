/*

TTGO T-BEAM Tracker for The Things Network

Copyright (C) 2018 by Xose Pérez <xose dot perez at gmail dot com>

This code requires LMIC library by Matthijs Kooijman
https://github.com/matthijskooijman/arduino-lmic

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include <Arduino.h>

float isBattConnected(float vIN) {
  //If vIN is below threshold we consider battery is OFF.
  return (vIN > BATT_OFF_THRESHOLD) ;  
}

float getBoatBatt(int pin) {
    uint16_t vsens = 0;
    float vOUT;
    float vIN;
    // BATTERY VOLTAGE SENSORS

    // First calculate received voltages for both sensors
    // Formula should be: (vsens1 * 3.3) / (4095 * 3)
    // vsens1 should be divided by 3 to get average value
    vsens = analogRead(pin);
    vOUT = (vsens * 3.3) / 4095; 
    
    // Calculate real voltages
    vIN = vOUT / (VSENS_R2/(VSENS_R1+VSENS_R2));

    return vIN;    
}
