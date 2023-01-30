#define SMOOTH_LED 11

#define TIMER_DELAY 5

long timer = 0;
int pwmValue = 0;

int brightnessDirection = 1;

void setup() 
{
  pinMode(SMOOTH_LED, OUTPUT);
}

void loop() 
{
  if ((millis() - timer) > TIMER_DELAY)
  { 
    timer = millis();

    pwmValue = pwmValue + brightnessDirection;

    if (pwmValue == 0 || pwmValue == 255) 
    {
      brightnessDirection = -brightnessDirection;
    }
    analogWrite(SMOOTH_LED, pwmValue);
  }
}
