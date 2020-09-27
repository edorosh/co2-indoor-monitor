/**
 * CO2 Indoor Monitor (MH-Z19B)
 * 
 * Monitors CO2 level in a room. It first warns and then alarms in case of CO2 level reaches a nonacceptable 
 * level. It has 4 Digit 7-Segment Display Module, a LED illumination along with a Buzzer. 
 * Currently the device is powered by a USB source only.
 * 
 * Author: Evgeny Doros
 * Email: eugene.dorosh@gmail.com
 * Github: https://github.com/edorosh
 * License: MIT 
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <SoftwareSerial.h>                                // Remove if using HardwareSerial or Arduino package without SoftwareSerial support
#include <MHZ19.h>
#include <TM1637Display.h>
#include <GyverTimer.h>
#include <GyverButton.h>
#include <rtttl.h>

#define RX_PIN 7                                          // Rx pin which the MHZ19 Tx pin is attached to
#define TX_PIN 8                                          // Tx pin which the MHZ19 Rx pin is attached to
#define BAUDRATE 9600                                     // Device to MH-Z19 Serial baudrate (should not be changed)

// Module connection pins (Digital Pins)
#define DISPLAY_CLK_PIN 10
#define DISPLAY_DIO_PIN 9

#define LED_RED_PIN 6
#define LED_GREEN_PIN 5
#define LED_BLUE_PIN 11
#define LED_BRIGHTNESS 60

#define BUZZER_PIN 2
#define BTN_MUTE_PIN 3
#define MELODY_REPEAT_INTERVAL_MS 5e3

#define CO2_READ_INTERVAL_MS 2e3                              // MH-Z19 read timeout

// Aha - Take on me
const char song_P[] PROGMEM = "TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5";

MHZ19 myMHZ19;                                             // Constructor for library
SoftwareSerial mySerial(RX_PIN, TX_PIN);                   // (Uno example) create device to MH-Z19 serial
TM1637Display display(DISPLAY_CLK_PIN, DISPLAY_DIO_PIN);
GTimer_ms melodyRepeatTimeout;
ProgmemPlayer player(BUZZER_PIN);

GButton muteButton(BTN_MUTE_PIN, HIGH_PULL);

unsigned long getDataTimer = 0;
int CO2 = 0;
boolean muteMode = false;
boolean requestPlayMelody = false;
boolean requestResetMelody = false;
boolean melodyCompleted = false;
uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };

enum LED_COLOR {LED_OFF, LED_RED, LED_GREEN, LED_BLUE, LED_YELLOW};

void setup() {
    Serial.begin(9600);                                     // Device to serial monitor feedback

    mySerial.begin(BAUDRATE);                               // (Uno example) device to MH-Z19 serial start   
    myMHZ19.begin(mySerial);                                // *Serial(Stream) refence must be passed to library begin(). 

    myMHZ19.autoCalibration(false);                              // Turn auto calibration ON (OFF autoCalibration(false))

    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_BLUE_PIN, OUTPUT);
    setLED(LED_OFF);

    //display.setBrightness(0x0f);
    display.setBrightness(5);

    player.setSong(song_P);
    //attachInterrupt(digitalPinToInterrupt(BTN_MUTE_PIN), isrMute, CHANGE);
}

//void isrMute() {
//  muteButton.tick();
//}

void loop() {
  muteButton.tick();
  //melodyTick();

  if (muteButton.isHold()) {
    if (!player.isSilent()) {
      requestResetMelody = true;
    }
    
    muteMode = true;
  } else {
    muteMode = false;
  }

  if (requestResetMelody) {
    player.initSong();
    requestResetMelody = false;
    Serial.println("Melody has been reset");
  }

  if (requestPlayMelody && !muteMode && !melodyCompleted) {
    melodyCompleted = !player.pollSong();

    if (melodyCompleted) {
      // skip next start in MS
    }
  } else if (requestPlayMelody && muteMode && !player.isSilent()) {
    player.silence();
  }

  if (millis() - getDataTimer >= CO2_READ_INTERVAL_MS)
  {
    CO2 = myMHZ19.getCO2(); // Request CO2 (as ppm)
    
    Serial.print("CO2 (ppm): ");                      
    Serial.println(CO2);
    
    handleLedIndicator();
    handleMusic();
  
    display.showNumberDec(CO2, false);
    
    getDataTimer = millis();
  }
}
