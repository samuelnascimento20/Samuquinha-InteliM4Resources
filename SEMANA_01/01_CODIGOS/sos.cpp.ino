int LED = 13;
int l_on = 0;
int l_off = 0;

void turn_On(int l_on)
{
  digitalWrite(LED, HIGH); 
  delay (l_on);
}

void turn_Off(int l_off)
{
  digitalWrite(LED, LOW); 
  delay (l_off);
}

void S()
{
turn_On (500); turn_Off (250); turn_On (500); turn_Off (250); turn_On (500); turn_Off (250);
delay (1500);
}

void O()
{
turn_On (1500); turn_Off (250); turn_On (1500); turn_Off (250); turn_On (1500); turn_Off (250);
delay (1500);
}

void setup() {
  // put your setup code here, to run once:
pinMode (LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly - display the Morse Code of SOS repeatedly
S();
O();
S();
delay (3500);
}
