/*
  mlab_thermistor.cpp - Simple NTC Thermistor interface by M Lab.
 Created by H. Dhamdhawach, January 10, 2012.
*/

#include "Arduino.h"
#include "Mlab_thermistor.h"
Mlab_thermistor::Mlab_thermistor(unsigned char thermistor_pin,char configuration,float pair_resistance,float thermistor_r25,float thermistor_beta){
	_thermistor_pin = thermistor_pin;
	_configuration = configuration;//PULL_UP or PULL_DOWN
	_pair_resistance = pair_resistance;
	_thermistor_r25 = thermistor_r25;//thermistor resistance at 25 degree celsius
	_thermistor_beta = thermistor_beta;
}
float  Mlab_thermistor::getResistance(float raw_sensor_val){
  float voltage = raw_sensor_val * 5.0 / 1024.0;//for arduino adc resolution
  float current;
  if (_configuration == PULL_UP)current = (5.0 - voltage) / _pair_resistance;
  else if (_configuration == PULL_DOWN)current = (voltage) / _pair_resistance;
  else return -1;// _configuration incorrect
  
  return voltage / current;
}

float  Mlab_thermistor::readCelsius(void){
	return readKelvin() - ZERO_CELSIUS_KELVIN;
}

float  Mlab_thermistor::readFahrenheit (void){
	return (readKelvin() - ZERO_CELSIUS_KELVIN)*1.8 + 32.0;
}
float  Mlab_thermistor::readKelvin (void){
	current_reading =  analogRead(_thermistor_pin);
	float temp = 1.0 / (1.0 / (ZERO_CELSIUS_KELVIN+25) + (1.0 / _thermistor_beta) * log(getResistance(current_reading) / _thermistor_r25)); // calculate temp in kelvin
	return temp;
}
float  Mlab_thermistor::adc2kelvin (float adc_val){

	float temp = 1.0 / (1.0 / (ZERO_CELSIUS_KELVIN+25) + (1.0 / _thermistor_beta) * log(getResistance(adc_val) / _thermistor_r25)); // calculate temp in kelvin
	return temp;
}
float  Mlab_thermistor::getAccuracy(void){
    float upper_temp = adc2kelvin(float(current_reading) + 0.5);
    float lower_temp = adc2kelvin(float(current_reading) - 0.5);
	float current_temp = adc2kelvin(float(current_reading));
    float accuracy = max(abs(upper_temp - current_temp), abs(lower_temp - current_temp));
	return accuracy;
}
