/*
 * VE_MPPT.h
 *
 *  Created on: 27 sept. 2020
 *      Author: TooT
 */

#ifndef VE_MPPT_H_
#define VE_MPPT_H_

#include "Arduino.h"
#include "VEDirect.h"
#include "SPI.h"
#include "SD.h"


#define VE_VERBOSE 0

namespace VE_Manager
{
	class VE_MPPT : public VEDirect
	{
		public:
			VE_MPPT(HardwareSerial &HWSerial);

			bool isConnected();
			void update();

			void setLogStream(File* f);
			void setLogStream(HardwareSerial *s);

			bool logData(String SoL = "", String EoL = "", char Separator = ',');
			String getData(String Separator = ",");

		public:
			float MainBatteryVoltage;
			float PanelVoltage;
			float PanelPower;
			float BatteryCurrent;
			float LoadCurrent;
			bool OutputState;
			bool RelayState;
			float YieldTotal;
			float YieldToday;
			float MaxPowerToday;
			float YieldYesterday;
			float MaxPowerYesterday;
			int ErrorCode;
			int StateOfOperation;
			String Firmware;
			String ProductID;
			int DaySequence;

		private:
			bool mIsConnected;
			SDLib::File *mFile;
			HardwareSerial *mSerial;

			char mSeparator;

			enum Stream{None, SDFile, HardSerial};
			Stream mStream;
	};

}

#endif /* VE_MPPT_H_ */
