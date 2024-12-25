# Finite state machine of interface of temperature controller

## Finite State Machine

### Notation explanation

- Display\_{something}\_Text_1stRow: Display the text {something} on the 1st row of the display screen to indicate what parameter is being adjusted
- Display\_{something}\_Value_2ndRow: Display the numeric value associated to the parameter {something} on the 2nd row of the display screen

### Overall FSM

```mermaid
stateDiagram-v2
    direction TB

    OperationLevel --> OperationLevel: 1s <= timerPressLEVELButton < 3s
    OperationLevel --> InitialSettingLevel: timerPressLEVELButton >= 3s
    OperationLevel --> AdjustmentLevel: timerPressLEVELButton < 1s

    InitialSettingLevel --> OperationLevel: pressLEVELbutton
    InitialSettingLevel --> InitialSettingLevel: !pressLEVELbutton

    AdjustmentLevel --> OperationLevel: pressLEVELbutton
    AdjustmentLevel --> AdjustmentLevel: !pressLEVELbutton
```

### Operation Level

```mermaid
stateDiagram-v2
    direction TB

    state OperationLevel {
            [*] --> Operation_Display
            Operation_Display --> Choose_Desired_SP: pressMODEbutton
            Choose_Desired_SP --> Choose_Alarm_SP: pressMODEbutton
            Choose_Alarm_SP --> Operation_Display: pressMODEbutton

            state Operation_Display {
                [*] --> Display_PV_Value_1stRow
                Display_PV_Value_1stRow --> Display_SP_Value_2ndRow
            }

            state Choose_Desired_SP {
                    [*] --> Display_SP_Text_1stRow
                    Display_SP_Text_1stRow --> Display_DesiredSP_Value_2ndRow
                    Display_DesiredSP_Value_2ndRow --> Increase_DesiredSP_Value: pressUPbutton
                    Increase_DesiredSP_Value --> Display_DesiredSP_Value_2ndRow
                    Display_DesiredSP_Value_2ndRow --> Decrease_DesiredSP_Value: pressDOWNbutton
                    Decrease_DesiredSP_Value --> Display_DesiredSP_Value_2ndRow
                    }

            state Choose_Alarm_SP {
                [*] --> Display_AL_Text_1stRow
                Display_AL_Text_1stRow --> Display_Alarm_Value_2ndRow
                Display_Alarm_Value_2ndRow --> Increase_Alarm_Value: pressUPbutton
                Increase_Alarm_Value --> Display_Alarm_Value_2ndRow
                Display_Alarm_Value_2ndRow --> Decrease_Alarm_Value: pressDOWNbutton
                Decrease_Alarm_Value --> Display_Alarm_Value_2ndRow
                }



        }
```

### Initial Setting Level

```mermaid
stateDiagram-v2
    direction TB

    state InitialSettingLevel {
            [*] --> Choose_Sensor_Type
            Choose_Sensor_Type --> Choose_Control_Type: pressMODEbutton
            Choose_Control_Type --> Choose_Sensor_Type: pressMODEbutton
        }

```

#### Choose Sensor Type

```mermaid
stateDiagram-v2
    direction TB
    state Choose_Sensor_Type {
                [*] --> Display_INT_Text_1stRow
                Display_INT_Text_1stRow --> Display_SensorType_Value_2ndRow
                Display_SensorType_Value_2ndRow --> Increase_SensorType_Value: pressUPbutton
                Increase_SensorType_Value --> Display_SensorType_Value_2ndRow
                Display_SensorType_Value_2ndRow --> Decrease_SensorType_Value: pressDOWNbutton
                Decrease_SensorType_Value --> Display_SensorType_Value_2ndRow
                }
```

#### Choose Control Type

```mermaid
stateDiagram-v2
    direction TB
     state Choose_Control_Type {
            [*] --> Display_CNTL_Text_1stRow
            Display_CNTL_Text_1stRow --> Display_ControlType_Value_2ndRow
            Display_ControlType_Value_2ndRow --> Choose_ControlType_PID: pressUPbutton
            Choose_ControlType_PID --> Display_ControlType_Value_2ndRow
            Display_ControlType_Value_2ndRow --> Choose_ControlType_ONOFF: pressDOWNbutton
            Choose_ControlType_ONOFF --> Display_ControlType_Value_2ndRow
            }
```

### Adjustment Level

```mermaid
stateDiagram-v2
    direction TB

    state AdjustmentLevel {
        [*] --> Display_ADJ_Text_1stRow
        Display_ADJ_Text_1stRow --> Choose_PID_Parameters

        state Choose_PID_Parameters {
            [*] --> Choose_P
            Choose_P --> Choose_I: pressMODEbutton
            Choose_P --> Choose_P: !pressMODEbutton

            Choose_I --> Choose_D: pressMODEbutton
            Choose_I --> Choose_I: !pressMODEbutton

            Choose_D --> Choose_P: pressMODEbutton
            Choose_D --> Choose_D: !pressMODEbutton
        }
    }
```

#### Choose P

```mermaid
stateDiagram-v2
    direction TB
    state Choose_P {
        [*] --> Display_P_Text_1stRow
        Display_P_Text_1stRow --> Display_P_Value_2ndRow
        Display_P_Value_2ndRow --> Increase_P_Value: pressUPbutton
        Increase_P_Value --> Display_P_Value_2ndRow
        Display_P_Value_2ndRow --> Decrease_P_Value: pressDOWNbutton
        Decrease_P_Value --> Display_P_Value_2ndRow
        }
```

#### Choose I

```mermaid
stateDiagram-v2
    direction TB
    state Choose_I {
        [*] --> Display_I_Text_1stRow
        Display_I_Text_1stRow --> Display_I_Value_2ndRow
        Display_I_Value_2ndRow --> Increase_I_Value: pressUPbutton
        Increase_I_Value --> Display_I_Value_2ndRow
        Display_I_Value_2ndRow --> Decrease_I_Value: pressDOWNbutton
        Decrease_I_Value --> Display_I_Value_2ndRow
        }
```

#### Choose D

```mermaid
stateDiagram-v2
    direction TB
    state Choose_D {
        [*] --> Display_D_Text_1stRow
        Display_D_Text_1stRow --> Display_D_Value_2ndRow
        Display_D_Value_2ndRow --> Increase_D_Value: pressUPbutton
        Increase_D_Value --> Display_D_Value_2ndRow
        Display_D_Value_2ndRow --> Decrease_D_Value: pressDOWNbutton
        Decrease_D_Value --> Display_D_Value_2ndRow


        }
```

## Explanation

- The interface has 4 buttons named: LEVEL, MODE, UP, DOWN.
  - LEVEL button: Change between Level settings
  - MODE button: Change between Parameter settings in a Level
  - UP/DOWN button: Increase/Decrease the value of the selected parameter
- There are 8 digits of 7-segment LED being used for display screen. These 8 digits are separated into 2 rows, each row has 4 digits.

### Setting the sensor type

To set the sensor type, you need to change the parameter INT (input type). Do this as follows:

1. Press LEVEL button for at least 3 seconds until "INT" is displayed on 1st row.
2. The value on 2nd row defaults to 5.
3. If you are using a different sensor type, please enter the number corresponding to the sensor type used. Use the reference table below.
4. You can change the value with the UP / DOWN button.

### Selecting PID or ON/OFF control

#### Setting up as PID controller

The control type is defaulted to ON/OFF. If you like to use ON/OFF, you can skip this step.

To set the control type as PID (you have to set P, I, D parameters manually later on), adjust the CNTL (control) parameter.

1. Press LEVEL button for at least 3 seconds until "INT" is displayed on the 1st row of the display screen.
2. Then press MODE button until "CNTL" is displayed on 1st row.
3. As you can see on 2nd row, the value for CNTL parameter is "ONOF" (ON-OFF). With the UP button change this to "PID".
4. When finished, press LEVEL button again to return to the operation display.

#### Setting the PID parameters manually

Set the P, I, D parameters manually in the Adjustment Level. Their default values are:

- Proportional band in °C: P = 8
- Integral time in seconds: I = 233
- Derivative time in seconds: D = 40

1. Press LEVEL button for less than 1 2nd. "ADJ" will be displayed on 1st row to show that the Adjustment Level has been entered.
2. Press MODE button to display P parameter on 1st row. You can change the value (shown on 2nd row) of this parameter with UP/DOWN buttons.
3. Similarly, you can change the values of I and D parameters by pressing MODE button to scroll through the parameters.

### Selecting the Alarm value

1. Press LEVEL button for 3 seconds until "INT" is displayed on 1st row.
2. Press MODE button several times until you see "AL" (Alarm) displayed on the 1st row of the screen
3. You can change the alarm value on the 2nd row with the UP and DOWN button.

### Finish

At any stage above, if you wanna go back to the operation display to see the current temperature SV and PV, press the LEVEL button for at least 3 seconds.
