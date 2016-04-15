/* Various functions for 1138G Worlds_Main.c */


// ********************************************************************
// Looks up Power expander battery voltage and determines the best speed
// "Location" is the code number indicating where robot is shooting from
// 0 = Full court
// 1 = Bar
// 2 = Skills
// 3 = Half court
// ********************************************************************
int Lookup_Sweetspot (int Location)
{
	int tableSpeed ;

	battVoltage = (float) SensorValue(powerExpBattery) / 282.66;

	switch(Location)
	{
		case 0:	//Full court shot

			if      (battVoltage >= 8.60) {tableSpeed = 52.0;}
			else if (battVoltage >= 8.55) {tableSpeed = 52.5;}
			else if (battVoltage >= 8.50) {tableSpeed = 53.0;}
			else if (battVoltage >= 8.45) {tableSpeed = 53.5;}
			else if (battVoltage >= 8.40) {tableSpeed = 54.0;}
			else if (battVoltage >= 8.35) {tableSpeed = 55.0;}
			else if (battVoltage >= 8.30) {tableSpeed = 56.0;}
			else if (battVoltage >= 8.25) {tableSpeed = 57.0;}
			else if (battVoltage >= 8.20) {tableSpeed = 57.5;}
			else if (battVoltage >= 8.15) {tableSpeed = 58.0;}
			else if (battVoltage >= 8.05) {tableSpeed = 58.5;}
			else if (battVoltage >= 8.00) {tableSpeed = 59.0;}
			else if (battVoltage >= 7.95) {tableSpeed = 60.0;}
			else if (battVoltage >= 7.90) {tableSpeed = 60.5;}
			else if (battVoltage >= 7.80) {tableSpeed = 61.0;}
			else if (battVoltage >= 7.75) {tableSpeed = 61.5;}
			else if (battVoltage >= 7.70) {tableSpeed = 62.0;}
			else if (battVoltage >= 7.65) {tableSpeed = 62.5;}
			else if (battVoltage >= 7.60) {tableSpeed = 63.0;}
			else if (battVoltage >= 7.55) {tableSpeed = 64.0;}
			else if (battVoltage >= 7.50) {tableSpeed = 65.0;}
			else 													{tableSpeed = 66.0;}
			break ;

		case 1:	//Bar shot
			if      (battVoltage >= 8.0) {tableSpeed = 50;}
			else if (battVoltage >= 7.5) {tableSpeed = 80;}
			else if (battVoltage >= 7.0) {tableSpeed = 60;}
			else if (battVoltage >= 6.5) {tableSpeed = 65;}
			else {tableSpeed = 45.0;}
			break ;

		case 2:	//Skills shot
			if      (battVoltage >= 8.0) {tableSpeed =  95;}
			else if (battVoltage >= 7.8) {tableSpeed = 100;}
			else if (battVoltage >= 7.0) {tableSpeed = 105;}
			else if (battVoltage >= 6.5) {tableSpeed = 110;}
			break ;

		case 3:	//Half court shot
			if      (battVoltage >= 8.60) {tableSpeed = 34.5;}
			else if (battVoltage >= 8.55) {tableSpeed = 35.0;}
			else if (battVoltage >= 8.50) {tableSpeed = 35.5;}
			else if (battVoltage >= 8.45) {tableSpeed = 36.0;}
			else if (battVoltage >= 8.40) {tableSpeed = 36.5;}
			else if (battVoltage >= 8.35) {tableSpeed = 37.0;}
			else if (battVoltage >= 8.30) {tableSpeed = 37.5;}
			else if (battVoltage >= 8.25) {tableSpeed = 38.0;}
			else if (battVoltage >= 8.20) {tableSpeed = 38.5;}
			else if (battVoltage >= 8.15) {tableSpeed = 39.0;}
			else if (battVoltage >= 8.05) {tableSpeed = 39.5;}
			else if (battVoltage >= 8.00) {tableSpeed = 40.0;}
			else if (battVoltage >= 7.95) {tableSpeed = 41.0;}
			else if (battVoltage >= 7.90) {tableSpeed = 41.5;}
			else if (battVoltage >= 7.80) {tableSpeed = 42.0;}
			else if (battVoltage >= 7.75) {tableSpeed = 42.5;}
			else if (battVoltage >= 7.70) {tableSpeed = 43.0;}
			else if (battVoltage >= 7.65) {tableSpeed = 43.5;}
			else if (battVoltage >= 7.60) {tableSpeed = 44.0;}
			else if (battVoltage >= 7.55) {tableSpeed = 44.5;}
			else if (battVoltage >= 7.50) {tableSpeed = 45.0;}
			else 													{tableSpeed = 45.5;}
			break ;
	} // End of switch statement

	return tableSpeed ;
}



// ********************************************************************
// Drive base forward or backward at desired speed
// ********************************************************************
void Move_Base(int speed)
{
	motor[leftBase]  = speed ;
	motor[rightBase] = speed ;
}


// ********************************************************************
// Move conveyor and intake collector at desired speed
// ********************************************************************
void Move_Conveyors(int speed)
{
	motor[conveyors] = speed ;
	motor[intake]    = speed ;
}


// ********************************************************************
// Spin up flywheels to desired speed
// Left Outer & Right Outer Flywheels are on PID control
// and the inner motors are slaved to the outers so all are
// controlled together
// ********************************************************************
void Spin_Flywheels(int speed)
{
	motor[leftOuter]  = speed ;
	motor[leftInner]  = speed ;
	motor[rightOuter] = speed ;
	motor[rightInner] = speed ;
}


// ********************************************************************
// Stop the base wheel motors
// ********************************************************************
void Stop_Base()
{
	motor[leftBase]  = 0 ;
	motor[rightBase] = 0 ;
}


// ********************************************************************
// Stop the conveyor and intake motors
// ********************************************************************
void Stop_Conveyors()
{
	motor[conveyors] = 0 ;
	motor[intake]    = 0 ;
}


// ********************************************************************
// Stop all motors on robot
// ********************************************************************
void Stop_All_Motors()
{
	motor[leftOuter]  = 0 ; //Flywheels
	motor[rightOuter] = 0 ;

	motor[conveyors]  = 0 ; //Conveyors
	motor[intake]     = 0 ;

	motor[leftBase]   = 0 ; //Base
	motor[rightBase]  = 0 ;
}




// ********************************************************************
// Full court auton - shoots 4 balls into net
// Assumes inner flywheel motors slaved to outers
// Assumes internal PID is used
// ********************************************************************
void Full_Court_Autonomous()
{
	int iI;		//local counting variable


	battDependentFull_Court_Sweetspot = Lookup_Sweetspot (0) ;
	Spin_Flywheels(battDependentFull_Court_Sweetspot) ;
	wait1Msec(4500) ;

	//Shoot 4 balls into net
	for (iI = 1; iI <= 4; iI++)
	{
		Move_Conveyors(100) ; 		wait1Msec(750) ;			//Shoot ball 1
		Stop_Conveyors() ;				wait1Msec(2700) ;			//Wait a moment
	}

	Move_Conveyors(100) ; 	  	wait1Msec(1000) ;			//In case last ball did not shoot
	Stop_All_Motors() ;																//Stop all motors

}



// ********************************************************************
// Bar auton - drives to bar and drops 4 balls into net
// ********************************************************************
void Bar_Autonomous()
{
	int iI;		//local counting variable

	//Drive to bar
	battDependentBar_Sweetspot = Lookup_Sweetspot (1) ;
	Spin_Flywheels(battDependentBar_Sweetspot) ;

	Move_Base(100) ;
	wait1Msec(2500) ;								//Drive to bar
	Stop_Base() ;

	//Shoot 4 balls into net
	for (iI = 1; iI <= 4; iI++)
		{
		Move_Conveyors(100) ;	wait1Msec(800) ;
		Stop_Conveyors() ;		wait1Msec(1000) ;
		}

	Move_Conveyors(100) ; 	  	wait1Msec(1000) ;			//In case last ball did not shoot
	Stop_All_Motors() ;																//Stop all motors

}




// ********************************************************************
// Skills auton - shoots 32 balls into nearest (opposite color) net
// ********************************************************************
void Skills_Autonomous()
{
	int iI;		//local counting variable

	//Spin_Flywheels(SKILLS_SWEETSPOT) ;

	battDependentBar_Sweetspot = Lookup_Sweetspot (2) ;
	Spin_Flywheels(battDependentSkills_Sweetspot) ;

	wait1Msec(2500) ;

	for (iI = 1; iI <= 32; iI++)
	{
		Move_Conveyors(127) ;
		wait1Msec(WAIT_FOR_FLYWHEELS) ; //First Ball

		Stop_Conveyors() ;
		wait1Msec(WAIT_FOR_BALL_LOAD) ;
	}

	//Slow_Flywheels() ;							//Use controlled slow-down to stop flywheels
	Stop_All_Motors() ;								//Stop all motors

}


// *****************************************************************************************************************
// *****************************************************************************************************************
//             LCD ROUTINES
// *****************************************************************************************************************
// *****************************************************************************************************************


// ********************************************************************
// Wait for user to press a button on LCD screen
// ********************************************************************
void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}


// ********************************************************************
// Wait for user to release a button on LCD screen
// ********************************************************************
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}


// ********************************************************************
// Autonomous Selection Using LCD
// ********************************************************************
void Auton_Selector()
{
	//Display battery voltages
	bLCDBacklight = true;	clearLCDLine(0);	clearLCDLine(1);	//Clear the LCD
	Display_Battery_Voltages();							wait1Msec(3000);		//Display Main and Backup (9V) battery voltages
	Display_Secondary_Battery_Voltage();		wait1Msec(3000);		//Display power expander battery voltage
	bLCDBacklight = true;	clearLCDLine(0);	clearLCDLine(1);	//Clear the LCD

	iCount = 0 ;

	while(nLCDButtons != CENTER_BUTTON)
	{
		switch(iCount)
		{
		case 0: //Full Court Autonomous
			displayLCDCenteredString(0, "Full Court Auton") ;
			displayLCDCenteredString(1, "<    Enter    >") ;
			waitForPress() ;
			if     (nLCDButtons == LEFT_BUTTON)		{waitForRelease() ;		iCount = 2 ;	}
			else if(nLCDButtons == RIGHT_BUTTON)	{waitForRelease() ;		iCount++ ;		}
			break ;

		case 1: //Bar Autonomous
			displayLCDCenteredString(0, "Bar Autonomous") ;
			displayLCDCenteredString(1, "<    Enter    >") ;
			waitForPress() ;
			if     (nLCDButtons == LEFT_BUTTON)		{waitForRelease() ;		iCount-- ;		}
			else if(nLCDButtons == RIGHT_BUTTON)	{waitForRelease() ;		iCount++ ;		}
			break ;

		case 2:	//Auton Skills
			displayLCDCenteredString(0, "Auton Skills") ;
			displayLCDCenteredString(1, "<    Enter    >") ;
			waitForPress() ;
			if     (nLCDButtons == LEFT_BUTTON)		{	waitForRelease() ;		iCount-- ;	}
			else if(nLCDButtons == RIGHT_BUTTON)	{	waitForRelease() ;		iCount++ ;	}
			break;

		case 3:	//No Auton
			displayLCDCenteredString(0, "NO AUTON");
			displayLCDCenteredString(1, "<    Enter    >");
			waitForPress();
			if     (nLCDButtons == LEFT_BUTTON)		{ waitForRelease();		iCount--;	 }
			else if(nLCDButtons == RIGHT_BUTTON)	{	waitForRelease();		iCount = 0; }
			break ;


		} //End of Switch statement

	} //End of While !CENTER_BUTTON


}
