const char *settings="/settings.json";
const char *wifinets="/wifinets.json";

struct Settings{
  char hostname[10] = "esp-async";
  char ap_dns_name[10] = "test";
  //
  char http_user[10] = "admin";
  char http_pass[10] = "admin";
  
  char sta_ssid[20] = "Sensor";
  char sta_pass[20] = "sensorgarten";
  
  char ap_ssid[20] = "testerwlan";
  char ap_pass[20] = "Sanifar123=";
  // Editor Access
  char edit_user[10] = "admin";
  char edit_pass[10] = "admin";
};

Settings conf;

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

#define WIFI_CONNECT_TIMEOUT 10
