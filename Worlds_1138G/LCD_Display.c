/*    LCD Display Functions     */


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Display Primary and backup battery voltages
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Display_Battery_Voltages()
{
	string mainS, backupS;													//Holds formatted battery voltage
	clearLCDLine(0); clearLCDLine(1); bLCDBacklight = true;					//Clear LCD lines and turn on backlight
	stringFormat(mainS,   "%1.2f", nImmediateBatteryLevel / 1000.0) ;
	stringFormat(backupS, "%1.2f", BackupBatteryLevel     / 1000.0) ;
	displayLCDString(0, 0, "Primary:  "); displayLCDString(0,11,mainS) ;		//Display the Primary battery voltage on LCD line 1
	displayLCDString(1, 0, "9VBackup: "); displayLCDString(1,11,backupS) ;	//Display the Backup battery voltage on LCD line 2
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Display Primary and Secondary battery voltages
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Display_Secondary_Battery_Voltage()
{
	string secondaryS;																							//Holds formatted battery voltages
	clearLCDLine(0); clearLCDLine(1); bLCDBacklight = true;					//Clear LCD lines and turn on backlight
	battVoltage = SensorValue(powerExpBattery) / 282.66 ;
	stringFormat(secondaryS, "%1.2f", battVoltage);
	displayLCDString(0, 1, "Power Expander");
	displayLCDString(1, 1, "VDC: ");
	displayLCDString(1, 6,secondaryS);
}

void Display_Message(string Msg1, float Num1)
	{
	clearLCDLine(0); clearLCDLine(1); bLCDBacklight = true;
	displayLCDString(0, 0, Msg1);
	displayLCDNumber(1, 0, Num1);
	}
