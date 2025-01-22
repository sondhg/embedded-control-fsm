#include <iostream>

enum State
{
    Run = 0,
    Parameter = 1,
    Setting = 2,
    Change = 3
};

enum SubState
{
    SV = 0,
    AV = 1,
    KP = 2,
    KI = 3,
    KD = 4,
    hysteresis = 5,
    INPUT = 6,
    OUTPUT = 7,
    CONTROL = 8
};

enum Button
{
    LEVEL = 1,
    MODE = 2,
    UP = 3,
    DOWN = 4
};

extern int getButtonPress();

State handleButtonPress(State currentState, State parentState, SubState &subState)
{
    int buttonPress = getButtonPress();

    switch (currentState)
    {
    case Run:
        if (buttonPress == LEVEL)
        {
            subState = SV; // Reset substate to SV when entering Parameter state
            return Parameter;
        }
        break;

    case Parameter:
        if (buttonPress == UP || buttonPress == DOWN)
        {
            return Change;
        }
        else if (buttonPress == LEVEL)
        {
            subState = INPUT; // Reset substate to INPUT when entering Setting state
            return Setting;
        }
        else if (buttonPress == MODE)
        {
            subState = static_cast<SubState>((subState + 1) % 6);
        }
        break;

    case Setting:
        if (buttonPress == UP || buttonPress == DOWN)
        {
            return Change;
        }
        else if (buttonPress == LEVEL)
        {
            return Run;
        }
        else if (buttonPress == MODE)
        {
            subState = static_cast<SubState>((subState + 1) % 3 + 6);
        }
        break;

    case Change:

        if (buttonPress == MODE)
        {
            return parentState;
        }
        break;

    default:
        return Run;
    }

    return currentState;
}

void interface()
{
    State state = Run;
    State parentState = Run;
    SubState subState = SV;

    while (true)
    {
        State newState = handleButtonPress(state, parentState, subState);

        if (newState == Change)
        {
            parentState = state;
        }

        state = newState;
    }
}