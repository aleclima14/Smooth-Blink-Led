#define SMOOTH_LED 11

#define TIMER_DELAY 10
long timer = 0;
int pwmValue = 0;
bool ledStatus = false;

void setup() 
{
  pinMode(SMOOTH_LED, OUTPUT);
}

void loop() 
{
  if (((millis() - timer) > TIMER_DELAY) && ledStatus == false)
  { 
    timer = millis();

    analogWrite(SMOOTH_LED, pwmValue);
    pwmValue++;

    pwmValue == 255 ? ledStatus = true: ledStatus = false;
  }
  if (((millis() - timer) > TIMER_DELAY) && ledStatus == true)
  { 
    timer = millis();

    analogWrite(SMOOTH_LED, pwmValue);
    pwmValue--;

    pwmValue == 0 ? ledStatus = false: ledStatus = true;
  }
}
