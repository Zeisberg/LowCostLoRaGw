/*
* Copyright (C) 2017 Sven Zeisberg, InnoTec21 GmbH, Germany
*
* sven.zeisberg@innotec21.de
*/

#include "FreqCntSoilMoisture.h"

FreqCntSoilMoisture::FreqCntSoilMoisture(char* nomenclature, bool is_analog, bool is_connected, bool is_low_power, uint8_t pin_read, uint8_t pin_power):Sensor(nomenclature, is_analog, is_connected, is_low_power, pin_read, pin_power){
  if (get_is_connected()){
    // start library FreqCount
    
    //dht = new DHT22(get_pin_read());
    
    pinMode(get_pin_power(),OUTPUT);
    
	if(get_is_low_power())
       digitalWrite(get_pin_power(),LOW);
    else
		digitalWrite(get_pin_power(),HIGH);
		
    set_wait_time(2000);
  }
}

void FreqCntSoilMoisture::update_data()
{
  if (get_is_connected()) {
  	
    // if we use a digital pin to power the sensor...
    if (get_is_low_power())
    	digitalWrite(get_pin_power(),HIGH);  	

    // wait
    delay(get_wait_time());

    FreqCount.begin(100); // set counter gate time
    
    delay(100); // delay by one counter gate time
  
  if (FreqCount.available()) {
    unsigned long count = FreqCount.read();
    set_data((double)count/100);
    Serial.print("\nFrequenz (capacitive soil moisture value): ");
    Serial.print(count*10);
    Serial.println(" Hz");

  }
  else {
    Serial.println("Kein Freuenzwert verfügbar");
    set_data((double)-1.0);
  }
    // recover errorCode to know if there was an error or not
   // errorCode = dht->readData();
	
	//if(errorCode == DHT_ERROR_NONE){
		// no error
		//set_data((double)dht->getHumidity());
//	}
//	else {
//		set_data((double)count*10);
//	}

    if (get_is_low_power())		
        digitalWrite(get_pin_power(),LOW);   
  }
  else {
  	// if not connected, set a random value (for testing)  	
  	if (has_fake_data()) 	{
      Serial.println("Set random data for Frequency");
      set_data((double)random(15, 90));
  	}
    	
  }
}

double FreqCntSoilMoisture::get_value()
{
  update_data();
  return get_data();
}
