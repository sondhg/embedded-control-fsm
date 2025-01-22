#include <iostream>

extern void interface();
extern void unitControl();

// Placeholder function to initialize hardware
extern void initializeHardware();

// Placeholder function to check if the system should continue running
extern bool systemShouldRun();

int main()
{
    // Initialize hardware
    initializeHardware();

    while (systemShouldRun())
    {
        interface();
        unitControl();
    }

    return 0;
}