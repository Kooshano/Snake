//define 16*16 matrix for rgb led matrix
#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN 6
#define brightness 10
int matrix[16][16];
CRGB leds[NUM_LEDS];
//0 for being off 1 for snake 2 for food
int snake_length = 3;
int direction[256] = {};
int snake_x[256] = {};
int snake_y[256] = {};
int food_x;
int food_y;
bool game_over = false;
bool eat_food = false;
void spawn_food(){
    food_x = random(0, 16);
    food_y = random(0, 16);
    if(matrix[food_x][food_y] == 0){
        matrix[food_x][food_y] = 2;
    }
    else{
        spawn_food();
    }
}
bool check_game_over(){
    if(snake_x[0] < 0 || snake_x[0] > 15 || snake_y[0] < 0 || snake_y[0] > 15){
        return true;
    }
    for(int i = 1; i < snake_length; i++){
        if(snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]){
            return true;
        }
    }
    return false;
}
void setup() {
    Serial.begin(9600);
    // put your setup code here, to run once:
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
    FastLED.clear();
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            matrix[i][j] = 0;
        }
    }
    for(int i = 0; i < snake_length; i++){
        snake_x[i] = 8;
        snake_y[i] = 8+i;
        matrix[snake_x[i]][snake_y[i]] = 1;
        direction[i] = 0;
    }
    spawn_food();
    update_matrix();
}

void loop() {
    if eat_food == true{
        snake_length++;
        eat_food = false;
        spawn_food();
    }
    if check_game_over() == true{
        game_over = true;
    }
    if game_over == false{
        for(int i = snake_length-1; i > 0; i--){
            snake_x[i] = snake_x[i-1];
            snake_y[i] = snake_y[i-1];
        }
        if(direction[0] == 0){
            snake_y[0]--;
        }
        else if(direction[0] == 2){
            snake_y[0]++;
        }
        else if(direction[0] == 3){
            snake_x[0]--;
        }
        else if(direction[0] == 1){
            snake_x[0]++;
        }
        if(snake_x[0] == food_x && snake_y[0] == food_y){
            eat_food = true;
        }
        for(int i = 0; i < 16; i++){
            for(int j = 0; j < 16; j++){
                matrix[i][j] = 0;
            }
        }
        for(int i = 0; i < snake_length; i++){
            matrix[snake_x[i]][snake_y[i]] = 1;
        }
        matrix[food_x][food_y] = 2;
        update_matrix();
        delay(1000);
    }
    else{
        for(int i = 0; i < 16; i++){
            for(int j = 0; j < 16; j++){
                matrix[i][j] = 0;
            }
        }
        update_matrix();
        delay(1000);
    }

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
