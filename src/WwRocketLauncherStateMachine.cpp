#include "WwRocketLauncherStateMachine.h"

WwRocketLauncherStateMachine::WwRocketLauncherStateMachine(void)
{
  _currentState = STATE_UNARMED;
}

void WwRocketLauncherStateMachine::reset(void)
{

}

int WwRocketLauncherStateMachine::state(void)
{
  return _currentState;
}

bool WwRocketLauncherStateMachine::update(bool continuity, bool rocket_on_pad, bool armed, bool launch)
{
  int startState = _currentState;

  switch(_currentState) {
    case STATE_UNARMED:
      if (continuity && rocket_on_pad && armed) {
        _currentState = STATE_ARMED;
      }
      break;
    case STATE_ARMED:
      if (continuity && rocket_on_pad && armed && launch) {
        _currentState = STATE_COUNTDOWN;
      } else if (!armed) {
        _currentState = STATE_UNARMED;
      } else if (launch) {
        _currentState = STATE_FAULT;
      }
      break;
    case STATE_COUNTDOWN:
      if (!armed) {
        _currentState = STATE_UNARMED;
      }
      break;
    case STATE_LAUNCH:
      if (!armed) {
        _currentState = STATE_UNARMED;
      }
      break;
    case STATE_POSTLAUNCH:
      if (!armed) {
        _currentState = STATE_UNARMED;
      }
      break;
    case STATE_FAULT:
      if (!armed) {
        _currentState = STATE_UNARMED;
      }
      break;
    default:
      break;
  }

  if (startState != _currentState) {
    return true;
  } else {
    return false;
  }
}
