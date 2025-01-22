#include <iostream>

enum State
{
    Running,
    Alarm
};

enum Method
{
    OnOff,
    PID
};

enum Output
{
    Sink,
    Relay
};

extern float getProcessValue();
extern float getAlarmValue();
extern float getSetValue();
extern Method getControlMethod();

extern float getHysteresis();
extern float getKp();
extern float getKi();
extern float getKd();

extern void pidControl(float PV, float SV, float Kp, float Ki, float Kd);
extern void onOffControl(float PV, float SV, float H);

extern void turnAlarmOn();
extern void turnAlarmOff();
extern void stop();

State handleState(State currentState)
{
    float PV = getProcessValue();
    float alarmValue = getAlarmValue();

    switch (currentState)
    {
    case Running:
        if (PV >= alarmValue)
        {
            return Alarm;
        }
        break;

    case Alarm:
        if (PV < alarmValue)
        {
            return Running;
        }
        break;

    default:
        return Running;
    }

    return currentState;
}

void unitControl()
{
    State state = Running;
    Method currentMethod = getControlMethod();

    while (true)
    {
        state = handleState(state);

        switch (state)
        {
        case Running:
            if (currentMethod != getControlMethod())
            {
                currentMethod = getControlMethod();
            }

            if (currentMethod == OnOff)
            {
                float PV = getProcessValue();
                float SV = getSetValue();
                float H = getHysteresis();
                onOffControl(PV, SV, H);
            }
            else if (currentMethod == PID)
            {
                float PV = getProcessValue();
                float SV = getSetValue();

                float Kp = getKp();
                float Ki = getKi();
                float Kd = getKd();
                pidControl(PV, SV, Kp, Ki, Kd);
            }
            break;
        case Alarm:
            stop();
            turnAlarmOn();
            break;

        default:
            break;
        }
    }
}