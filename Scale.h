
/**
 * Beehive scales project
 * 
 * Scale class is used as wrapper to HX711 library. 
 * 
 * Dependencies:
 * Scale use the HX711 library:
 * https://github.com/hiveeyes/HX711/tree/spring-cleaning
 *
 * MIT License
 * (c) 2020 victor.ustynov@gmail.com
 *
 **/

#ifndef SCALE_h
#define SCALE_h

#include "HX711.h"

class Scale
{
    public:
      Scale();
      ~Scale();

      void init( int DOUT_PIN, int SCK_PIN, byte gain = 128 );

      int calibrate(float etalon_weight);

      void power_down();

      void power_up();

      float get_units(byte times = 1);

      long read();

      long read_average(byte times = 10);

      double get_value(byte times = 1);

      void set_scale(float scale = 1.f);

      void tare(byte times = 10);

    private:
      HX711  SCALE;
  
};

#endif
