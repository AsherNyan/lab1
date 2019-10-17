#include "pitches.h"
#include "button.h"
#include "buzzer.h"

#define BUZZER_PIN_P1 9 //Player 1 buzzer pin
#define BUZZER_PIN_P2 7 //Player 2 buzzer pin

#define BUTTON_PIN_P1 10 //Player 1 button pin
#define BUTTON_PIN_P2 8 //Player 2 button pin

#define RED_LIGHT_PIN 6
#define GREEN_LIGHT_PIN 5
#define BLUE_LIGHT_PIN 4

enum GameState{
 gameStarted,
 gameVictory,
 gameReset
};

GameState gameState = gameReset;
Buzzer buzzerWinner(BUZZER_PIN_P1);
Button buttonP1(BUTTON_PIN_P1);
Button buttonP2(BUTTON_PIN_P2);
uint64_t melodyStarted = 0;

int notes[] = {NOTE_G3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE, NOTE_DS3, NOTE_SILENCE};
double durations[] = {8, 8, 1, 8, 1, 8, 1, 24};
int melodyLength = 8;
int melodyDurationInMillis = 5900;

void setup() {
    buzzerWinner.setMelody(notes, durations, melodyLength);
    pinMode(RED_LIGHT_PIN, OUTPUT);
    pinMode(GREEN_LIGHT_PIN, OUTPUT);
    pinMode(BLUE_LIGHT_PIN, OUTPUT);
    
}

void loop(){
  
  switch(gameState)
  {
    case gameStarted:
      if(buttonP1.wasPressed()){
        buzzerWinner.setBuzzerPin(BUZZER_PIN_P1);
        gameState = gameVictory;
        set_rgb(0, 0, 0);
        buzzerWinner.turnSoundOn();
        melodyStarted = millis();
      }
      if(buttonP2.wasPressed()){
        buzzerWinner.setBuzzerPin(BUZZER_PIN_P2);
        gameState = gameVictory;
        set_rgb(0, 0, 0);
        buzzerWinner.turnSoundOn();
        melodyStarted = millis();
      }
      break;
      
    case gameVictory:
      buzzerWinner.playSound();
      if (millis() - melodyStarted < melodyDurationInMillis)
        buzzerWinner.playSound();
      else
        gameState = gameReset;
      break;
      
    case gameReset:
      endGame();
      startGame();
      break;
  }
}

void startGame(){
  set_rgb(0, 255, 0);
  delay(1000);
  set_rgb(0, 0, 0);
  delay(random(20, 50) * 100);
  set_rgb(255, 0, 0);
  gameState = gameStarted;  
}

void endGame() {
  buzzerWinner.turnSoundOff();  
}

void set_rgb(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(RED_LIGHT_PIN, 255 - red_light_value);
  analogWrite(GREEN_LIGHT_PIN, 255 - green_light_value);
  analogWrite(BLUE_LIGHT_PIN, 255 - blue_light_value);
}
