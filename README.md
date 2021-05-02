# VEDirectMPPTArduino
Small library to fetch and easily log data from Victron Energy MPPT.

ℹ️ You'll need to install first **[VictronVEDirectArduino](https://github.com/T88T/VictronVEDirectArduino)** library in order to communicate with the MPPT

# Available data

For further details check informations on [Victron Energy website](https://www.victronenergy.fr/download-document/4459/bluesolar-hex-protocol-mppt.pdf).

| Attibute | Description | Unit |
|--|--|--|
| MainBatteryVoltage | Current battery voltage | V |
| PanelVoltage | Current panel voltage | V |
| PanelPower | Current panel power | mA |
| BatteryCurrent | Current battery charge current | mA |
| LoadCurrent | Current load output current | mA |
| OutputState | Output state | Boolean |
| RelayState | Relay state | Boolean |
| YieldTotal | Power yield from MPPT last factory reset | kWh |
| YieldToday | Power yield today | kWh |
| MaxPowerToday | Maximum power reached today | W |
| YieldYesterday | Maximum power yield yesterday | kWh |
| MaxPowerYesterday | Maximum power reached yesterday | W |
| ErrorCode | Error code | Integer |
| StateOfOperation | Charging mode | Boolean |
| Firmware | Firmware version | String |
| ProductID | ProductID | String |
| DaySequence | Day since last reset | Day/365 |


# Usage
```C
#include <VE_MPPT.h>

VE_MPPT myMPPT(Serial1);

void setup()
{
    Serial.begin(9600);
    myMPPT.setLogStream(&Serial);
}

void loop()
{
    myMPPT.update();
    myMPPT.logData();
    delay(10000);
}
```

