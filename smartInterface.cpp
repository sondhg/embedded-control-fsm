#include <iostream>

// Enumeration for different states of the interface
enum State
{
    Run = 0,
    Parameter = 1,
    Setting = 2,
    Change = 3
};

// Enumeration for sub-states within Parameter and Setting
enum SubState
{
    SV = 0,
    AV = 1,
    KP = 2,
    KI = 3,
    KD = 4,
    INPUT = 5,
    OUTPUT = 6,
    CONTROL = 7
};

// Enumeration for button presses
enum Button
{
    LEVEL = 1,
    MODE = 2,
    UP = 3,
    DOWN = 4
};

// Function prototypes for hardware-related functions
extern void displayPV();        // Display process value on 1st row
extern void displaySV();        // Display set value on 2nd row
extern void displayParameter(); // Display parameter name on 1st row and its value on 2nd row
extern void displaySetting();   // Display setting name on 1st row and its value on 2nd row

// Function to get button press (LEVEL, MODE, UP, DOWN)
extern int getButtonPress();

// Function to get the duration of the LEVEL button press
extern int getLevelButtonPressDuration();

// Function to handle state transitions based on button press
State handleButtonPress(State currentState, State parentState, SubState &subState)
{
    int buttonPress = getButtonPress();
    int levelPressDuration = getLevelButtonPressDuration();

    switch (currentState)
    {
    case Run:
        if (buttonPress == LEVEL)
        {
            return (levelPressDuration >= 3) ? Parameter : Setting;
        }
        break;

    case Parameter:
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
            subState = static_cast<SubState>((subState + 1) % 5); // Cycle through SV, AV, KP, KI, KD
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
            subState = static_cast<SubState>((subState + 1) % 3 + 5); // Cycle through INPUT, OUTPUT, CONTROL
        }
        break;

    case Change:
        if (buttonPress == MODE)
        {
            return Run;
        }
        else if (buttonPress == LEVEL)
        {
            return parentState;
        }
        break;

    default:
        return Run;
    }

    return currentState;
}

// Function to display the appropriate information based on the current state and sub-state
void displayState(State state, SubState subState)
{
    switch (state)
    {
    case Run:
        displaySV();
        displayPV();
        break;
    case Parameter:
        switch (subState)
        {
        case SV:
            // Display SV
            break;
        case AV:
            // Display AV
            break;
        case KP:
            // Display KP
            break;
        case KI:
            // Display KI
            break;
        case KD:
            // Display KD
            break;
        default:
            break;
        }
        displayParameter();
        break;
    case Setting:
        switch (subState)
        {
        case INPUT:
            // Display INPUT
            break;
        case OUTPUT:
            // Display OUTPUT
            break;
        case CONTROL:
            // Display CONTROL
            break;
        default:
            break;
        }
        displaySetting();
        break;
    default:
        break;
    }
}

// Function representing the interface for the embedded system
void interface()
{
    State state = Run;       // Initialize state to Run
    State parentState = Run; // Variable to store the parent state before entering Change state
    SubState subState = SV;  // Initialize sub-state to SV

    while (true) // Infinite loop to keep the interface running
    {
        displayState(state, subState);                                    // Display the appropriate information based on the current state and sub-state
        State newState = handleButtonPress(state, parentState, subState); // Handle state transitions based on button press

        if (newState == Change)
        {
            parentState = state; // Update parent state before entering Change state
        }

        state = newState; // Update the current state
    }
}