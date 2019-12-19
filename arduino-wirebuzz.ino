// CONSTANTS
// The "start zone" which players must touch to start the game each time
const byte startPin = 8;
// Touching any part of the wire itself causes a failure
const byte failPin = 9;
// The "win zone" at the end of the wire
const byte endPin = 10;
// A piezo buzzer chirps to signify success/failure
const byte buzzerPin = 6;

// GLOBALS
// Keep track of the current states of the game
enum GameState {FAILED, IN_PROGRESS, SUCCESS};
GameState gameState = GameState::FAILED;

void setup() {
  // Set the pins to the correct mode
  pinMode(startPin, INPUT_PULLUP);
  pinMode(failPin, INPUT_PULLUP);
  pinMode(endPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  // Begin a serial connection for debugging
  Serial.begin(9600);
}

void loop() {
  switch(gameState) {
   
    case GameState::IN_PROGRESS:
      if(!digitalRead(endPin)) {
        gameState = GameState::SUCCESS;
        Serial.println("Congratulations!");
        tone(buzzerPin, 440, 50);
        delay(60);
        tone(buzzerPin, 587, 250);
      }
      else if(!digitalRead(failPin)) {
        gameState = GameState::FAILED;
        Serial.println("FAILED");
        tone(buzzerPin, 440, 200);
        delay(200);
        tone(buzzerPin, 415, 200);
        delay(200);
        tone(buzzerPin, 392, 200);
        delay(200);
        tone(buzzerPin, 370, 400);
      }
      break;

    case GameState::FAILED:
    case GameState::SUCCESS:
      if(!digitalRead(startPin)) {
        gameState = GameState::IN_PROGRESS;
        Serial.println("New Game Started");
        tone(buzzerPin, 440, 100);
        delay(120);
        tone(buzzerPin, 554, 100);
        delay(120);
        tone(buzzerPin, 659, 200);
      }
      break;    
  }
}
