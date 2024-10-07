/* this code is an edited version of this code: 
https://github.com/G6EJD/ESP32-8266-Audio-Spectrum-Display/blob/master/ESP32_Spectrum_Display_02.ino

you need to have/download 3 libraries: arduinoFFT, Adafruit_GFX, Adafruid_SSD1306.
*/


#include <Wire.h>
#include "arduinoFFT.h" // Standard Arduino FFT library
#include "SSD1306.h" 

SSD1306 display(0x3c, 8, 9); // (address, SDA, SCL)

/////////////////////////////////////////////////////////////////////////
#define SAMPLES 256              // Must be a power of 2
#define SAMPLING_FREQUENCY 40000 // Hz, must be 40000 or less due to ADC conversion time. Fmax=sampleF/2.
#define amplitude 200            // Depending on your audio source level, you may need to increase this value


double vReal[SAMPLES];
double vImag[SAMPLES];
int pixelWidth = 128; // Width of OLED display
int pixelHeight = 64; // Height of OLED display

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

/////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9); // SDA, SCL
  display.init();
  display.setFont(ArialMT_Plain_10);
}

void loop() {
  display.clear(); // Clear the display
  for (int i = 0; i < SAMPLES; i++) {

    vReal[i] = analogRead(A0); // Read input from analog pin
    vImag[i] = 0;
    //while (micros() < (newTime + sampling_period_us)) { /* Do nothing to wait */ }
  }

  FFT.windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.complexToMagnitude(vReal, vImag, SAMPLES);

  // Call new function to display frequencies on the OLED
  displayFrequency(vReal, SAMPLES / 2);

  display.display(); // Update the display with drawn content
}

// New function to display frequencies using all 128 pixels
void displayFrequency(double *vReal, int numBins) {
  double binWidth = numBins / (double)pixelWidth; // Number of FFT bins per pixel column
  int columnValue;

  // Loop through each column of the OLED display
  for (int x = 5; x < pixelWidth; x++) {
    columnValue = 0;
    int startBin = round(x * binWidth);
    int endBin = round((x + 1) * binWidth);

    // Calculate the average amplitude for the bins corresponding to this pixel
    for (int i = startBin; i < endBin && i < numBins; i++) {
      columnValue += vReal[i];
    }
    columnValue = columnValue / (endBin - startBin); // Average amplitude

    // Apply noise floor threshold
    // if (columnValue < 150) {
    //   columnValue = 0; // Ignore if below noise floor
    // }

    // Scale amplitude to fit the display height
    int height = map(columnValue, 0, 4000, 0, pixelHeight); // Adjust 2000 as needed for scaling
    height = constrain(height, 0, pixelHeight); // Limit to the display height

    // Draw vertical line at the current pixel position (x)
    display.drawLine(x, pixelHeight, x, pixelHeight - height);
  }
}
