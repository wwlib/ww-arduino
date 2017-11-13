#include <WwLaunchClock.h>
#include <WwRocketLauncherStateMachine.h>
#include <MeOrion.h>

WwLaunchClock clock;
WwRocketLauncherStateMachine rlsm;
Me7SegmentDisplay disp(PORT_3);
MeJoystick joystick(PORT_6);

int16_t x = 0;    /* a variable for the Joystick's x value */
int16_t y = 0;    /* a variable for the Joystick's y value */

bool btnLaunch = false;
bool btnArmed = false;
bool continuity = true;
bool rocketOnPad = true;

void setup() {
  Serial.begin(9600);
  Serial.println("RocketLauncher Setup.");

  clock.set(millis(), 10000, 0, clock.MODE_COUNTDOWN);
  clock.start();
  disp.display(clock.time() / 1000);

  Serial.print("Setup time: ");
  Serial.println(clock.elapsed());
  Serial.println(clock.time());
}

void loop() {
  x = joystick.readX();
  y = joystick.readY();
  btnLaunch = false;

  // simulates arm switch
  if (y > 400){
    btnArmed = true;
  } else if (y < -400) {
    btnArmed = false;
  } else if (x > 400) { // simulates momentary launch button
    btnLaunch = true;
  }

  //bool continuity, bool rocket_on_pad, bool armed, bool launch
  bool stateChanged = rlsm.update(continuity, rocketOnPad, btnArmed, btnLaunch);
  if (stateChanged) {
    int state = rlsm.state();
    Serial.print("State changed: ");
    Serial.println(state);
    Serial.println(continuity);
    Serial.println(rocketOnPad);
    Serial.println(btnArmed);
    Serial.println(btnLaunch);
    switch (state) {
      case rlsm.STATE_COUNTDOWN:
        clock.reset(millis());
        clock.start();
        break;
    }
  }
  clock.update(millis());

  switch (rlsm.state()) {

    case rlsm.STATE_COUNTDOWN:
      if (clock.isNewSecond()) {
      Serial.print("Clock elapsed: ");
      Serial.println(clock.elapsed());
      Serial.print("Clock currentSecond: ");
      Serial.println(clock.currentSecond());
      disp.display(clock.currentSecond());
      if (clock.reachedTargetTime()) {
        clock.stop();
      }
      break;
    }
  }
}
