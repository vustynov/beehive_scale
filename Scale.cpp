
#include "Scale.h"
#include <math.h>

Scale::Scale() 
{
}

Scale::~Scale()
{
}

void Scale::init(int dout_pin, int sck_pin, byte gain )
{
  // some magic numbers, from example here: https://github.com/hiveeyes/HX711/tree/spring-cleaning 
  const long OFFSET = 50682624;
  const long DIVIDER = 5895655;

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  SCALE.begin(dout_pin, sck_pin, gain);
/*
  SCALE.set_scale(DIVIDER);
  SCALE.set_offset(OFFSET);

  SCALE.set_scale(2280.f);
*/
//  SCALE.set_scale();
  SCALE.tare();

}


int Scale::calibrate(float etalon_weight)
{
  float units, coef;
  const float delta = 0.01;
  int i = 0;
  const int maxtrying = 100;
  float divider = etalon_weight;
  do { 
    units = SCALE.get_units(10);
    
    if (divider == 0) 
      divider = 0.01;
    coef = units / etalon_weight;
    SCALE.set_scale( coef );
    delay(5);
    i++;
    
  } while (abs(units - etalon_weight) < delta && i < maxtrying) ;

  // count of calibration times exceeded
  if (i>=maxtrying) return -1;

  // OK
  return 0;
}

void Scale::power_down()
{
  SCALE.power_down();
}

void Scale::power_up()
{
  SCALE.power_up();
}

float Scale::get_units(byte times)
{
  return SCALE.get_units(times);
}

long Scale::read()
{
  return SCALE.read();
}

long Scale::read_average(byte times )
{
  return SCALE.read_average( times );
}

double Scale::get_value(byte times)
{
  return SCALE.get_value( times );
}

void Scale::set_scale(float scale )
{
  SCALE.set_scale( scale );
}

void Scale::tare(byte times )
{
  SCALE.tare( times );
}
