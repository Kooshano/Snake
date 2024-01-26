//define 16*16 matrix for rgb led matrix
#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN 6
#define brightness 10
int matrix[16][16];
CRGB leds[NUM_LEDS];
//0 for being off 1 for snake 2 for food
int snake_length = 3;
string direction[256] = [];
int snake_x[256] = [];
int snake_y[256] = [];
int food_x;
int food_y;
void setup() {
    Serial.begin(9600);
    // put your setup code here, to run once:
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
    FastLED.clear();
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            matrix[i][j] = 2;
        }
    }
    update_matrix();
    // for(int i = 0; i < snake_length; i++){
    //     snake_x[i] = 8;
    //     snake_y[i] = 8+i;
    //     matrix[snake_x[i]][snake_y[i]] = 1;
    //     direction[i] = "up";
    // }
    // food_x = 8;
    // food_y = 8;
    // matrix[food_x][food_y] = 2;
    // update_matrix();
}

void loop() {
  // put your main code here, to run repeatedly:

}
void update_matrix(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
        if(matrix[i][j] == 0){
            leds[i*16+j] = CRGB::Black;
        }
        else if(matrix[i][j] == 1){
            leds[i*16+j] = CRGB::Green;
        }
        else if(matrix[i][j] == 2){
            leds[i*16+j] = CRGB::Red;
        }
        }
    }
    FastLED.show();
}