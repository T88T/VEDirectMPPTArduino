/*
 * VE_MPPT.cpp
 *
 *  Created on: 27 sept. 2020
 *      Author: TooT
 */

#include "VE_MPPT.h"


namespace VE_Manager
{

VE_MPPT::VE_MPPT(HardwareSerial &HWSerial) : VEDirect(HWSerial)
{

	mIsConnected = begin();

#if VE_VERBOSE
	Serial.print("\tMPPT base code init... ");
	if(mIsConnected)
		Serial.println("OK");
	else
		Serial.println("Failed");
#endif

	MainBatteryVoltage = 0;
	PanelVoltage = 0;
	PanelPower = 0;
	BatteryCurrent = 0;
	LoadCurrent = 0;
	OutputState = false;
	RelayState = false;
	YieldTotal = 0;
	YieldToday = 0;
	MaxPowerToday = 0;
	YieldYesterday = 0;
	MaxPowerYesterday = 0;
	ErrorCode = 0;
	StateOfOperation = 0;
	Firmware = String("");
	ProductID = String("");
	DaySequence = 0;

	mFile = nullptr;
	mSerial = nullptr;

	mStream = Stream::None;
	mSeparator = ',';

}

bool VE_MPPT::isConnected()
{
	return mIsConnected;
}

void VE_MPPT::update()
{
	if(!mIsConnected)
		return;

	VEDirect::update();

	if(available())
	{
		MainBatteryVoltage = VEDirect::read(VE_VOLTAGE)*0.001;
		PanelVoltage = VEDirect::read(VE_PANEL_VOLTAGE)*0.001;
		PanelPower = VEDirect::read(VE_PANEL_POWER);
		BatteryCurrent = VEDirect::read(VE_CURRENT)*0.001-0.1;
		LoadCurrent = VEDirect::read(VE_BATTERY_LOAD_CURRENT)*0.001;
		OutputState = VEDirect::read(VE_LOAD_STATE);
		RelayState = VEDirect::read(VE_RELAY_STATE);
		YieldTotal = VEDirect::read(VE_YIELD_TOTAL)*0.01;
		YieldToday = VEDirect::read(VE_YIELD_TODAY)*0.01;
		MaxPowerToday = VEDirect::read(VE_MAX_DAILY_POWER);
		YieldYesterday = VEDirect::read(VE_YIELD_YESTERDAY)*0.01;
		MaxPowerYesterday = VEDirect::read(VE_MAX_YESTERDAY_POWER);
		ErrorCode = VEDirect::read(VE_ERROR_CODE);
		StateOfOperation = VEDirect::read(VE_STATE_OF_OPERATION);
		Firmware = String(VEDirect::read(VE_FW));
		ProductID = String(VEDirect::read(VE_PID), HEX);
		DaySequence = VEDirect::read(VE_DAY_SEQUENCE_NUMBER);
	}
}

void VE_MPPT::setLogStream(File* f)
{
	if(f != nullptr)
		mFile = f;

	mStream = Stream::SDFile;
}

void VE_MPPT::setLogStream(HardwareSerial *s)
{
	if(s != nullptr)
		mSerial = s;

	mStream = Stream::SDFile;
}

bool VE_MPPT::logData(String SoL, String EoL, char Separator)
{

	if(!mIsConnected)
			return false;

	String data = SoL;

	mSeparator = Separator;

	data += String(MainBatteryVoltage, 2); data += mSeparator;
	data += String(PanelVoltage, 2); data += mSeparator;
	data += String(PanelPower, 2); data += mSeparator;
	data += String(BatteryCurrent, 2); data += mSeparator;
	data += String(LoadCurrent, 2); data += mSeparator;
	data += String(OutputState); data += mSeparator;
	data += String(RelayState); data += mSeparator;
	data += String(YieldTotal, 2); data += mSeparator;
	data += String(YieldToday, 2); data += mSeparator;
	data += String(MaxPowerToday); data += mSeparator;
	data += String(YieldYesterday, 2); data += mSeparator;
	data += String(MaxPowerYesterday); data += mSeparator;
	data += String(ErrorCode); data += mSeparator;
	data += String(StateOfOperation); data += mSeparator;
	data += String(Firmware); data += mSeparator;
	data += String(ProductID); data += mSeparator;
	data += String(DaySequence);
	data += EoL;
	data += "\n\r";

	if(mStream == Stream::SDFile && mFile != nullptr)
	{
		if(mFile->availableForWrite())
		{
			mFile->print(data);
			mFile->close();
			return true;
		}

		else
		{
#if VE_VERBOSE
			Serial.println("# Event : Error -> SD unavailable for log");
#endif
			mFile->close();
			return false;
		}
	}

	if(mStream == Stream::HardSerial && mSerial != nullptr)
	{
		if(mSerial->availableForWrite())
		{
			mSerial->print(data);
			return true;
		}

		else
		{
#if VE_VERBOSE
			Serial.println("# Event : Error -> Serial unavailable for log");
#endif
			return false;
		}
	}

	return false;

}


String VE_MPPT::getData(String Separator)
{
	String data("");

	data += String(MainBatteryVoltage, 2); data += mSeparator;
	data += String(PanelVoltage, 2); data += mSeparator;
	data += String(PanelPower, 2); data += mSeparator;
	data += String(BatteryCurrent, 2); data += mSeparator;
	data += String(LoadCurrent, 2); data += mSeparator;
	data += String(OutputState); data += mSeparator;
	data += String(RelayState); data += mSeparator;
	data += String(YieldTotal, 2); data += mSeparator;
	data += String(YieldToday, 2); data += mSeparator;
	data += String(MaxPowerToday); data += mSeparator;
	data += String(YieldYesterday, 2); data += mSeparator;
	data += String(MaxPowerYesterday); data += mSeparator;
	data += String(ErrorCode); data += mSeparator;
	data += String(StateOfOperation); data += mSeparator;
	data += String(Firmware); data += mSeparator;
	data += String(ProductID); data += mSeparator;
	data += String(DaySequence);

	return data;
}

} /* namespace VE_Manager */
