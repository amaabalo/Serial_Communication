int state[6]; // keep track of which leds are on and which are off
byte x[1];
int target;
int MAX;    // maximum number of LEDs on at any point in time
int count;  // number of LEDs that have been turned on
int timeOn;
int current;
int prev = -1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MAX = 1;
  count = 0;
  for(int i = 2; i<=7; i++)
  {
    pinMode(i, OUTPUT);
    state[i-2] = 0;
  }
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (count < MAX)
  {
    do
    {
      target = random(6);
    }
    while (state[target] || target==prev);
    digitalWrite((target + 2), HIGH);
    state[target] = 1;
    count ++;
    timeOn = millis();
  }
  else
  {
    current = millis();
    if (current >= (timeOn + 1500) && state[target])
    {
      digitalWrite((target + 2), LOW);
      state[target] = 0;
      count --;
      prev = target;
    }
    else
    {
      while(Serial.available())
      {
        if(Serial.readBytes(x,1))
        {  
          if (state[x[0]])
          {
            tone(9,1500,100);
            digitalWrite((x[0] + 2),LOW);
            state[x[0]] = 0;
            count --;
            prev = x[0];
          }
          else
          {
            tone(9,31,300);
          }
        }
      }
    }
  }
}
