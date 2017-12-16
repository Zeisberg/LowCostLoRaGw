/*
* Copyright (C) 2017 Sven Zeisberg, InnoTec21 GmbH, Germany
*
* sven.zeisberg@innotec21.de
*/

#include "SHT1X_Humidity.h"

SHT1X_Humidity::SHT1X_Humidity(char* nomenclature, bool is_analog, bool is_connected, bool is_low_power, uint8_t pin_read, uint8_t pin_power):Sensor(nomenclature, is_analog, is_connected, is_low_power, pin_read, pin_power){
  if (get_is_connected()){
    // start library FreqCount
    
    //dht = new DHT22(get_pin_read()); -- was an example
	
	//Create an instance of the SHT1X sensor
	sht = new SHT1x( get_pin_read(), 9);// Data, SCK 
	// Data = yellow = Pin D8
	// Clk = blue = Pin D9
    pinMode(6,OUTPUT); // provide permanent ground on PIN 6 (due to less ground pins)
	digitalWrite(6,LOW);
	
    pinMode(get_pin_power(),OUTPUT);
    
	if(get_is_low_power())
       digitalWrite(get_pin_power(),LOW);
    else
		digitalWrite(get_pin_power(),HIGH);
		
    set_wait_time(2000);
  }
}

void SHT1X_Humidity::update_data()
{
  if (get_is_connected()) {
  	
    // if we use a digital pin to power the sensor...
    if (get_is_low_power())
    	digitalWrite(get_pin_power(),HIGH);  	

    // wait
    delay(get_wait_time());

	// Read value from the sensor
    float humidity = sht->readHumidity();
	set_data((double)humidity);
	
 
    Serial.print("SHT10 Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

  
    if (get_is_low_power())		
        digitalWrite(get_pin_power(),LOW);   
  }
  else {
  	// if not connected, set a random value (for testing)  	
  	if (has_fake_data()) 	{
      Serial.println("Set random data for SHT10 Humidity");
      set_data((double)random(15, 90));
  	}
    	
  }
}

double SHT1X_Humidity::get_value()
{
  update_data();
  return get_data();
}
