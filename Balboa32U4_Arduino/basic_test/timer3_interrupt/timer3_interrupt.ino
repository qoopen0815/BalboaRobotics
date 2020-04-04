#include <TimerThree.h>
#include <Balboa32U4.h>

Balboa32U4Buzzer buzzer;

void timerFire() {
  //100ms（=100000us）毎にここが呼び出される
  // Start playing a tone with frequency 440 Hz at maximum
  // volume (15) for 200 milliseconds.
  buzzer.playFrequency(440, 200, 10);

  // Delay to give the tone time to finish.
  delay(10);
}

void setup() {
  Timer3.initialize(10000000); //マイクロ秒単位で設定
  Timer3.attachInterrupt(timerFire);
}

void loop() {

}
