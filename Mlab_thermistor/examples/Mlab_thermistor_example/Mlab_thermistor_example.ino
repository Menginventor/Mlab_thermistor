#include <Mlab_thermistor.h>
#define INTERVAL_MS 100 //Interval of display
#define PAIR_RESISTANCE 20000.0
#define THERMISTER_R25 100000.0 //thermistor resistance at 25 degree celsius
#define THERMISTER_BETA 4400.0  //beta value of thermistor (usually 4000)
#define THERMISTOR_PIN A0
#define THERMISTOR_CONFIGURATION PULL_UP // Using Pukk-up resistor or you can use PULL_DOWN

//mlab_thermistor(unsigned char thermistor_pin,char configuration,float pair_resistance,float thermistor_r25,float thermistor_beta)
Mlab_thermistor thermistor(THERMISTOR_PIN,PULL_UP,PAIR_RESISTANCE,THERMISTER_R25,THERMISTER_BETA);
void setup() {
  Serial.begin(115200);
}
void loop() {
  static unsigned long timer = millis();
  if (millis() - timer >= INTERVAL_MS) {
    timer += INTERVAL_MS;
    Serial.print(thermistor.readCelsius());
    //You can use readFahrenheit() or  readKelvin() if you want.
    Serial.print("\t");
    Serial.println(thermistor.getAccuracy());// accuracy in +-kelvin or celsius (same scale) based on adc resolution.
  }
}
