
const char * hostName = "esp-async";
const char* http_username = "admin";
const char* http_password = "admin";



//fastled

uint8_t brightness = 128;
#define MILLI_AMPS         500 // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
#define DATA_PIN    0
#define CLK_PIN   5



#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_STRIPS 1
#define NUM_LEDS_PER_STRIP 12
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS
CRGB leds[NUM_LEDS];
//has to be uint8_t so it starts at 0 after it reached 256
uint8_t hue = 0;
