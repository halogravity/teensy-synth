#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Bounce button0 = Bounce(0, 15);
Bounce button1 = Bounce(1, 15);
Bounce button2 = Bounce(2, 15);
Bounce button3 = Bounce(3, 15);
Bounce button4 = Bounce(4, 15);
Bounce button5 = Bounce(5, 15);
Bounce button14 = Bounce(14, 15);
Bounce button16 = Bounce(16, 15);

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     noise1;         //xy=210,232
AudioSynthNoiseWhite     noise3;         //xy=210,622
AudioSynthNoiseWhite     noise2;         //xy=211,422
AudioSynthWaveform       waveform3;      //xy=217,187
AudioSynthWaveform       waveform9;      //xy=217,577
AudioSynthWaveform       waveform6;      //xy=218,377
AudioSynthWaveform       waveform2;      //xy=219,146
AudioSynthWaveform       waveform8;      //xy=219,536
AudioSynthWaveform       waveform5;      //xy=220,336
AudioSynthWaveform       waveform1;      //xy=221,102
AudioSynthWaveform       waveform7;      //xy=221,492
AudioSynthWaveform       waveform4;      //xy=222,292
AudioMixer4              mixer1;         //xy=409,160
AudioMixer4              mixer3;         //xy=425,554
AudioMixer4              mixer2;         //xy=426,354
AudioEffectEnvelope      envelope1;      //xy=584,160
AudioEffectEnvelope      envelope3;      //xy=584,551
AudioEffectEnvelope      envelope2;      //xy=585,351
AudioMixer4              finalMixer;     //xy=818,376
AudioOutputI2S           i2s1;           //xy=1152,378
AudioConnection          patchCord1(noise1, 0, mixer1, 3);
AudioConnection          patchCord2(noise3, 0, mixer3, 3);
AudioConnection          patchCord3(noise2, 0, mixer2, 3);
AudioConnection          patchCord4(waveform3, 0, mixer1, 2);
AudioConnection          patchCord5(waveform9, 0, mixer3, 2);
AudioConnection          patchCord6(waveform6, 0, mixer2, 2);
AudioConnection          patchCord7(waveform2, 0, mixer1, 1);
AudioConnection          patchCord8(waveform8, 0, mixer3, 1);
AudioConnection          patchCord9(waveform5, 0, mixer2, 1);
AudioConnection          patchCord10(waveform1, 0, mixer1, 0);
AudioConnection          patchCord11(waveform7, 0, mixer3, 0);
AudioConnection          patchCord12(waveform4, 0, mixer2, 0);
AudioConnection          patchCord13(mixer1, envelope1);
AudioConnection          patchCord14(mixer3, envelope3);
AudioConnection          patchCord15(mixer2, envelope2);
AudioConnection          patchCord16(envelope1, 0, finalMixer, 0);
AudioConnection          patchCord17(envelope3, 0, finalMixer, 2);
AudioConnection          patchCord18(envelope2, 0, finalMixer, 1);
AudioConnection          patchCord19(finalMixer, 0, i2s1, 0);
AudioConnection          patchCord20(finalMixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1108,550
// GUItool: end automatically generated code


void setup() {
Serial.begin(9600);

// by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("PANDA SYNTH");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println("V.0.0.1 BETA");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("PANDA LABS");
  display.display();
  delay(2000);
  display.clearDisplay();

//Full Synth requires some serious memory
  AudioMemory(64);
  sgtl5000_1.enable();

  // Full volume is 1.0 which will damage speakers or ears in most cases
  sgtl5000_1.volume(0.4); 

  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);

  mixer1.gain(0, 0.8);
  mixer1.gain(1, 0.8);
  mixer1.gain(2, 0.8);

  mixer2.gain(0, 0.8);
  mixer2.gain(1, 0.8);
  mixer2.gain(2, 0.8);

  mixer3.gain(0, 0.8);
  mixer3.gain(1, 0.8);
  mixer3.gain(2, 0.8);

  finalMixer.gain(0, 0.8);
  finalMixer.gain(0, 0.8);
  finalMixer.gain(0, 0.8);

  envelope1.attack(250);
  envelope1.decay(350);
  envelope1.sustain(0.6);
  envelope1.release(350);

  envelope2.attack(250);
  envelope2.decay(350);
  envelope2.sustain(0.6);
  envelope2.release(350);

  envelope3.attack(250);
  envelope3.decay(350);
  envelope3.sustain(0.6);
  envelope3.release(350);

  waveform1.begin(0.6, 440, WAVEFORM_TRIANGLE);
  waveform2.begin(0.6, 523.25, WAVEFORM_TRIANGLE);
  waveform3.begin(0.6, 659.26, WAVEFORM_TRIANGLE);

  waveform4.begin(0.6, 261.63, WAVEFORM_SQUARE);
  waveform5.begin(0.6, 329.63, WAVEFORM_SQUARE);
  waveform6.begin(0.6, 392, WAVEFORM_SQUARE);

  waveform7.begin(0.6, 329.63, WAVEFORM_SAWTOOTH);
  waveform8.begin(0.6, 196, WAVEFORM_SAWTOOTH);
  waveform9.begin(0.6, 247, WAVEFORM_SAWTOOTH);
  
}
void loop() {
  button0.update();
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  button5.update();
  button14.update();
  button16.update();

 // float knob1 = (float)analogRead(A9) / 1023.0;
 // float knob2 = (float)analogRead(A8) / 1023.0;
 // float knob3 = (float)analogRead(A7) / 1023.0;

  if (button0.fallingEdge()) {
    envelope1.noteOn();
  }
  if (button0.risingEdge()) {
    envelope1.noteOff();
  }
  if (button1.fallingEdge()) {
    envelope2.noteOn();
  }
  if (button1.risingEdge()) {
    envelope2.noteOff();
  }
    if (button2.fallingEdge()) {
    envelope3.noteOn();
  }
  if (button2.risingEdge()) {
    envelope3.noteOff();
  }
      if (button3.fallingEdge()) {
    envelope3.noteOn();
  }
  if (button3.risingEdge()) {
    envelope3.noteOff();
  }
  if (button4.fallingEdge()) {
    envelope2.noteOn();
  }
  if (button4.risingEdge()) {
    envelope2.noteOff();
  }
if (button5.fallingEdge()) {
    envelope3.noteOn();
  }
  if (button5.risingEdge()) {
    envelope3.noteOff();
  }
      if (button14.fallingEdge()) {
    envelope3.noteOn();
  }
  if (button14.risingEdge()) {
    envelope3.noteOff();
  }
  if (button16.fallingEdge()) {
    envelope1.noteOn();
  }
  if (button16.risingEdge()) {
    envelope1.noteOff();
  }
}