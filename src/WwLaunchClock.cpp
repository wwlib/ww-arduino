

/* Includes ------------------------------------------------------------------*/
#include "WwLaunchClock.h"

WwLaunchClock::WwLaunchClock()
{
    _startTime = 10000;
    _previousSecond = -1;
    _targetTime = 0;
    _running = false;
    _mode = MODE_COUNTDOWN;
    _currentMillis = 0;
    _previousMillis = 0;
    _startMillis = 0;
}

WwLaunchClock::WwLaunchClock(long millis, long start_time, long target_time, int mode)
{
  set(millis, start_time, target_time, mode);
}

void WwLaunchClock::reset(long millis)
{
  _previousSecond = -1;
  _running = false;
  _currentMillis = millis;
  _previousMillis = millis;
  _startMillis = millis;
}

void WwLaunchClock::set(long millis, long start_time, long target_time, int mode)
{
  _startTime = start_time;
  _previousSecond = -1;
  _targetTime = target_time;
  _running = false;
  _mode = mode;
  _currentMillis = millis;
  _previousMillis = millis;
  _startMillis = millis;
}

void WwLaunchClock::start(void)
{
    _previousSecond = -1;
    _running = true;
}

void WwLaunchClock::stop(void)
{
    _running = false;
}

long WwLaunchClock::elapsed(void)
{
    return _elapsedMillis;
}

long WwLaunchClock::time(void)
{
    if (_mode == MODE_COUNTDOWN) {
      return _startTime - _elapsedMillis;
    } else {
      return _elapsedMillis + _startTime;
    }
}

long WwLaunchClock::currentSecond(void)
{
    if (reachedTargetTime()) {
      return _targetTime / 1000;
    } else {
      if (_mode == MODE_COUNTDOWN) {
        long currentSecond = time() / 1000 + 1;
        long startSecond = _startTime / 1000;
        if (currentSecond > startSecond) {
          currentSecond = startSecond;
        }
        return currentSecond;
      } else {
        return time() / 1000;
      }
    }
}

bool WwLaunchClock::isNewSecond(void)
{
    long checkCurrentSecond = currentSecond();
    if (checkCurrentSecond == _previousSecond) {
      return false;
    } else {
      _previousSecond = checkCurrentSecond;
      return true;
    }
}

bool WwLaunchClock::reachedTargetTime(void) {
  bool result = false;
  if (_mode == MODE_COUNTDOWN) {
    if (time() <= _targetTime) {
      result = true;
    }
  } else {
    if (time() >= _targetTime) {
      result = true;
    }
  }
  return result;
}

void WwLaunchClock::update(long millis)
{
      _currentMillis = millis;
      if (_running) {
        _elapsedMillis = _currentMillis - _startMillis;
      }
}
