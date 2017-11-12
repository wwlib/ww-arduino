
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>

class WwLaunchClock
{
public:
  static const int MODE_COUNTDOWN = 0;
  static const int MODE_COUNTUP = 1;

  WwLaunchClock(void);

  WwLaunchClock(long millis, long start_time, long target_time, int mode);

  void reset(long millis);

  void set(long millis, long start_time, long target_time, int mode);

  void start(void);

  void stop(void);

  long elapsed(void);

  long time(void);

  long WwLaunchClock::currentSecond(void);

  bool WwLaunchClock::isNewSecond(void);

  bool WwLaunchClock::reachedTargetTime(void);

  void update(long millis);

private:
  bool _running;
  long _startMillis;
  long _previousMillis;
  long _currentMillis;
  long _elapsedMillis;
  long _startTime;
  long _targetTime;
  long _previousSecond;

  int _mode;
};
