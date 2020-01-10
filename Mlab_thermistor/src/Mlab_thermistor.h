/*
  mlab_thermistor.h - Simple NTC Thermistor interface by M Lab.
 Created by H. Dhamdhawach, January 10, 2012.
*/

// ensure this library description is only included once
#ifndef Mlab_thermistor_h
#define Mlab_thermistor_h

// include types & constants of Wiring core API
#include "Arduino.h"

// library interface description
#define PULL_UP 1
#define PULL_DOWN 2
#define ZERO_CELSIUS_KELVIN 273.15

class Mlab_thermistor{

private:
	unsigned char _thermistor_pin;
	char _configuration = 0;//PULL_UP or PULL_DOWN
	float _pair_resistance;
	float _thermistor_r25;//thermistor resistance at 25 degree celsius
	float _thermistor_beta;
	float  current_reading;
	float  adc2kelvin (float adc_val);
public:
	Mlab_thermistor(unsigned char thermistor_pin,char configuration,float pair_resistance,float thermistor_r25,float thermistor_beta);
    float  getResistance(float raw_sensor_val);
	float  readCelsius(void);
	float  readFahrenheit (void);
	float  readKelvin (void);
	float  getAccuracy(void);
	


};

#endif