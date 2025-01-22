#include <iostream>

// Enumeration for different states of the interface
enum State
{
    Run = 0,
    Parameter = 1,
    Setting = 2,
    Change = 3
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

// Function representing the interface for the embedded system
void interface()
{
    State state = Run;          // Initialize state to Run
    State parentState = Run;    // Variable to store the parent state before entering Change state
    int buttonPress = 0;        // Variable to store button press actions
    int levelPressDuration = 0; // Variable to store the duration of LEVEL button press

    while (true) // Infinite loop to keep the interface running
    {
        switch (state)
        {
        case Run:
            displaySV(); // Display set value
            displayPV(); // Display process value

            // Simulate button press actions
            buttonPress = getButtonPress();                     // Function to get button press (LEVEL, MODE, UP, DOWN)
            levelPressDuration = getLevelButtonPressDuration(); // Get the duration of LEVEL button press

            if (buttonPress == LEVEL && levelPressDuration >= 3) // LEVEL button pressed for >= 3s
            {
                state = Parameter;
            }
            else if (buttonPress == LEVEL && levelPressDuration < 3) // LEVEL button pressed for < 3s
            {
                state = Setting;
            }
            break;

        case Parameter:
            displayParameter(); // Display parameter values

            // Simulate button press actions
            buttonPress = getButtonPress(); // Function to get button press (LEVEL, MODE, UP, DOWN)

            if (buttonPress == UP || buttonPress == DOWN) // UP/DOWN button pressed
            {
                parentState = Parameter;
                state = Change;
            }
            else if (buttonPress == LEVEL) // LEVEL button pressed
            {
                state = Run;
            }
            break;

        case Setting:
            displaySetting(); // Display setting values

            // Simulate button press actions
            buttonPress = getButtonPress(); // Function to get button press (LEVEL, MODE, UP, DOWN)

            if (buttonPress == UP || buttonPress == DOWN) // UP/DOWN button pressed
            {
                parentState = Setting;
                state = Change;
            }
            else if (buttonPress == LEVEL) // LEVEL button pressed
            {
                state = Run;
            }
            break;

        case Change:
            // Simulate button press actions
            buttonPress = getButtonPress(); // Function to get button press (LEVEL, MODE, UP, DOWN)

            if (buttonPress == MODE) // MODE button pressed
            {
                state = Run;
            }
            else if (buttonPress == LEVEL) // LEVEL button pressed
            {
                if (parentState == Parameter)
                {
                    state = Parameter;
                }
                else if (parentState == Setting)
                {
                    state = Setting;
                }
            }
            break;

        default:
            state = Run; // Default state
            break;
        }
    }
}