/*
* Copyright (C) 2017 Sven Zeisberg, InnoTec21 GmbH, Germany
*
* sven.zeisberg@innotec21.de
*/

#ifndef SHT1X_Temperature_H
#define SHT1X_Temperature_H

#include "Sensor.h"
#include "SHT1X.h"

class SHT1X_Temperature : public Sensor {
  public:    
    SHT1X_Temperature(char* nomenclature, bool is_analog, bool is_connected, bool is_low_power, uint8_t pin_read, uint8_t pin_power);
    double get_value();
    void update_data(); 

 private:
    SHT1x* sht = NULL;
    // SHT1X_ERROR_t errorCode;
    uint8_t _sht_type;
    
};

#endif
