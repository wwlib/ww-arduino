class WwRocketLauncherStateMachine
{
public:
  static const int STATE_UNARMED = 0;
  static const int STATE_ARMED = 1;
  static const int STATE_COUNTDOWN = 2;
  static const int STATE_LAUNCH = 3;
  static const int STATE_POSTLAUNCH = 4;
  static const int STATE_FAULT = 5;

  WwRocketLauncherStateMachine(void);

  void WwRocketLauncherStateMachine::reset(void);

  int WwRocketLauncherStateMachine::state(void);

  bool WwRocketLauncherStateMachine::update(bool continuity, bool rocket_on_pad, bool armed, bool launch);

private:
  int _currentState;
};
