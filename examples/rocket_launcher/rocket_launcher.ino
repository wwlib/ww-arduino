#include <WwLaunchClock.h>
#include <MeOrion.h>

WwLaunchClock clock;
Me7SegmentDisplay disp(PORT_3);

void setup() {
  Serial.begin(9600);
  Serial.println("RocketLauncher Setup.");

  clock.set(millis(), 30000, 9000, clock.MODE_COUNTDOWN);
  clock.start();
  disp.display(clock.time() / 1000);

  Serial.print("Setup time: ");
  Serial.println(clock.elapsed());
  Serial.println(clock.time());
}

void loop() {
  clock.update(millis());
  if (clock.reachedTargetTime()) {
    clock.stop();
  }
  if (clock.isNewSecond()) {
    Serial.print("Clock elapsed: ");
    Serial.println(clock.elapsed());
    Serial.print("Clock currentSecond: ");
    Serial.println(clock.currentSecond());
    disp.display(clock.currentSecond());
  }
}
