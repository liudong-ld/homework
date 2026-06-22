#define LED_PIN 2
unsigned long prevTime = 0;
const unsigned long shortLight = 200;
const unsigned long longLight = 600;
const unsigned long gap = 200;
const unsigned long sosPause = 2000;

// 状态机：0等待、1短闪、2长闪、3结束停顿
int state = 0;
int shortCnt = 0;
int longCnt = 0;
bool lightOn = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  if (now - prevTime < (lightOn ? (state==1?shortLight:longLight) : gap)) return;
  prevTime = now;
  lightOn = !lightOn;
  digitalWrite(LED_PIN, lightOn);

  if(!lightOn){
    if(state == 1){
      shortCnt++;
      if(shortCnt >= 3){
        state = 2; shortCnt = 0;
      }
    }else if(state == 2){
      longCnt++;
      if(longCnt >= 3){
        state = 3; longCnt = 0;
      }
    }else if(state == 3){
      state = 1;
      prevTime = millis() + sosPause;
    }
  }
}
