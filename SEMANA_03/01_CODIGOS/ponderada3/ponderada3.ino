/**
Jogo Simon para Arduino
*/

// Pinos dos LEDs e dos botões
const byte ledPins[] = {9, 10, 12, 13};
const byte buttonPins[] = {2, 3, 5, 6};
#define SPEAKER_PIN 8

// Constantes de jogo
#define MAX_GAME_LENGTH 100
const int gameTones[] = { NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G5};

// Variáveis de controle do jogo
byte gameSequence[MAX_GAME_LENGTH] = {0};
byte gameIndex = 0;

// Configuração inicial
void setup() {
Serial.begin(9600);
for (byte i = 0; i < 4; i++) {
pinMode(ledPins[i], OUTPUT);
pinMode(buttonPins[i], INPUT_PULLUP);
}
pinMode(SPEAKER_PIN, OUTPUT);

randomSeed(analogRead(A0));
}

// Acende o LED e toca um tom
void lightLedAndPlayTone(byte ledIndex) {
digitalWrite(ledPins[ledIndex], HIGH);
tone(SPEAKER_PIN, gameTones[ledIndex]);
delay(300);
digitalWrite(ledPins[ledIndex], LOW);
noTone(SPEAKER_PIN);
}

// Toca a sequência de jogo
void playSequence() {
for (int i = 0; i < gameIndex; i++) {
byte currentLed = gameSequence[i];
lightLedAndPlayTone(currentLed);
delay(50);
}
}

// Lê os botões pressionados pelo jogador
byte readButtons() {
while (true) {
for (byte i = 0; i < 4; i++) {
byte buttonPin = buttonPins[i];
if (digitalRead(buttonPin) == LOW) {
return i;
}
}
delay(1);
}
}

// Ação quando o jogo acaba
void gameOver() {
Serial.print("Fim de jogo! Sua pontuação: ");
Serial.println(gameIndex - 1);
gameIndex = 0;
delay(200);

// Toca um som indicando o fim do jogo
tone(SPEAKER_PIN, NOTE_DS5);
delay(300);
tone(SPEAKER_PIN, NOTE_D5);
delay(300);
tone(SPEAKER_PIN, NOTE_CS5);
delay(300);
for (byte i = 0; i < 10; i++) {
for (int pitch = -10; pitch <= 10; pitch++) {
tone(SPEAKER_PIN, NOTE_C5 + pitch);
delay(5);
}
}
noTone(SPEAKER_PIN);
delay(500);
}

// Verifica se a sequência do jogador está correta
bool checkUserSequence() {
for (int i = 0; i < gameIndex; i++) {
byte expectedButton = gameSequence[i];
byte actualButton = readButtons();
lightLedAndPlayTone(actualButton);
if (expectedButton != actualButton) {
return false;
}
}
return true;
}

// Toca um som de sucesso quando o jogador passa de nível
void playLevelUpSound() {
tone(SPEAKER_PIN, NOTE_E4);
delay(150);
tone(SPEAKER_PIN, NOTE_G4);
delay(150);
tone(SPEAKER_PIN, NOTE_E5);
delay(150);
tone(SPEAKER_PIN, NOTE_C5);
delay(150);
tone(SPEAKER_PIN, NOTE_D5);
delay(150);
tone(SPEAKER_PIN, NOTE_G5);
delay(150);
noTone(SPEAKER_PIN);
}

// O loop principal do jogo
void loop() {
// Adiciona uma cor aleatória no final da sequência
gameSequence[gameIndex] = random(0, 4);
gameIndex++;
if (gameIndex >= MAX_GAME_LENGTH) {
gameIndex = MAX_GAME_LENGTH - 1;
}

playSequence();
if (!checkUserSequence()) {
gameOver();
}

delay(300);

if (gameIndex > 0) {
playLevelUpSound();
delay(300);
}
}
