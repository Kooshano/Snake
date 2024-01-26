//define 16*16 matrix for rgb led matrix
#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN 6
#define brightness 10
int matrix[16][16];
//0 for being off 1 for snake 2 for food
int snake[256];
int snake_length = 1;
void setup() {
  // put your setup code here, to run once:

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