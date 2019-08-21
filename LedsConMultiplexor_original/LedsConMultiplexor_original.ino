/******************************************************************************
Mux_Analog_Output
SparkFun Multiplexer Output Example
Jim Lindblom @ SparkFun Electronics
August 15, 2016
https://github.com/sparkfun/74HC4051_8-Channel_Mux_Breakout

This sketch demonstrates how to use the SparkFun Multiplexer
Breakout - 8 Channel (74HC4051) to drive eight outputs using
four digital pins.

Hardware Hookup:
Mux Breakout ----------- Arduino
     S0 ------------------- 8
     S1 ------------------- 9
     S2 ------------------- 10
     S3 ------------------- 11
     Z -------------------- 3
    VCC ------------------- 5V
    GND ------------------- GND
    (VEE should be connected to GND)

Development environment specifics:
Arduino 1.6.9
SparkFun Multiplexer Breakout - 8-Channel(74HC4051) v10
(https://www.sparkfun.com/products/13906)
******************************************************************************/
/////////////////////
// Pin Definitions //
/////////////////////
const int selectPins[4] = {8, 9, 10, 11}; // S0~8, S1~9, S2~10, S2~11
const int zOutput = 3; // Connect common (Z) to 3 (PWM-capable)

const int LED_ON_TIME = 500; // Each LED is on 0.5s
const int DELAY_TIME = ((float)LED_ON_TIME/512.0)*1000;
void setup() 
{
  // Set up the select pins, as outputs
  for (int i=0; i<4; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], LOW);
  }
  pinMode(zOutput, OUTPUT); // Set up Z as an output
}

void loop() 
{
  // Cycle from pins Y0 to Y15 first
  for (int pin=0; pin<=15; pin++)
  {
    // Set the S0, S1, S2 and S3 pins to select our active
    // output (Y0-Y15):
    selectMuxPin(pin);
    // While the output is selected ramp the LED intensity up
    for (int intensity=0; intensity<=255; intensity++)
    {
      analogWrite(zOutput, intensity);
      delayMicroseconds(DELAY_TIME);
    }
    // Then bring the analog output value down:
    for (int intensity=255; intensity>=0; intensity--)
    {
      analogWrite(zOutput, intensity);
      delayMicroseconds(DELAY_TIME);
    }
  }
  // Now cycle from pins Y14 to Y1
  for (int pin=14; pin>=1; pin--)
  {
    selectMuxPin(pin); // Select the pin
    // Cycle the intensity up:
    for (int intensity=0; intensity<=255; intensity++)
    {
      analogWrite(zOutput, intensity);
      delayMicroseconds(DELAY_TIME);
    }
    // Then ramp the output down:
    for (int intensity=255; intensity>=0; intensity--)
    {
      analogWrite(zOutput, intensity);
      delayMicroseconds(DELAY_TIME);
    }
  }
}

// The selectMuxPin function sets the S0, S1, S2 and S3 pins
// accordingly, given a pin from 0-15.
void selectMuxPin(byte pin)
{
  if (pin > 15) return; // Exit if pin is out of scope
  for (int i=0; i<4; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}
