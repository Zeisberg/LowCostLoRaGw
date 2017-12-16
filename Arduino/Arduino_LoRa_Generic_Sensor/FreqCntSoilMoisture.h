/*
* Copyright (C) 2017 Sven Zeisberg, InnoTec21 GmbH, Germany
*
* sven.zeisberg@innotec21.de
*/

#ifndef FreqCntSoilMoisture_H
#define FreqCntSoilMoisture_H

#include "Sensor.h"
#include "FreqCount.h"

class FreqCntSoilMoisture : public Sensor {
  public:    
    FreqCntSoilMoisture(char* nomenclature, bool is_analog, bool is_connected, bool is_low_power, uint8_t pin_read, uint8_t pin_power);
    double get_value();
    void update_data(); 
};

#endif
