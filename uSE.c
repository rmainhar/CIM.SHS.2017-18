#pragma config(Sensor, in2,    lineFollowerRIGHT, sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerCENTER, sensorLineFollower)
#pragma config(Sensor, in4,    lineFollowerLEFT, sensorLineFollower)
#pragma config(Sensor, dgtl1,  bump,           sensorTouch)
#pragma config(Sensor, dgtl2,  touch,          sensorTouch)
#pragma config(Sensor, dgtl12, e_stopBTN,      sensorTouch)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                             	    - Triple Sensor Line Tracking -                                   *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program uses 3 VEX Line Follower Sensors to track a black line on a light(er) surface.       *|
|*  There is a two second pause at the beginning of the program.                                      *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*    2)  Lighting conditions, line darkness, and surface lightness change from place to place,       *|
|*        so the value of 'threshold' may need to be changed to better suit your environment.         *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor  - Port 2     rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor  - Port 3     leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Analog - Port 1     lineFollowerRIGHT   VEX Light Sensor      Front-right, facing down          *|
|*    Analog - Port 2     lineFollowerCENTER  VEX Light Sensor      Front-center, facing down         *|
|*    Analog - Port 3     lineFollowerLEFT    VEX Light Sensor      Front-left, facing down           *|
\*-----------------------------------------------------------------------------------------------4246-*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
int swag;
int threshold;

task main()
{
	swag = 0;
	untilBump(touch, 500);
	threshold = ((((SensorValue(lineFollowerRIGHT))+ (SensorValue(lineFollowerCENTER)))  /2));/* found by taking a reading on both DARK and LIGHT    */
	/* surfaces, adding them together, then dividing by 2. */
	untilBump(bump, 500);
	swag = 1;
	while(1==1)
	{
		if(swag==2)
		{
			stopMotor(leftMotor);
			stopMotor(rightMotor);
			untilBump(bump, 500);
			swag = 1;
		}
		if(swag==1)
		{
			// RIGHT sensor sees dark:
			if(SensorValue(e_stopBTN) == 1)
			{
				swag = 2;
			}
			if(SensorValue(lineFollowerLEFT) > threshold)
			{
				// counter-steer right:
				motor[leftMotor]  = 60;
				motor[rightMotor] = -40;
			}
			// CENTER sensor sees dark:
			if(SensorValue(lineFollowerCENTER) > threshold)
			{
				// go straight
				motor[leftMotor]  = 70;
				motor[rightMotor] = 70;
			}
			// LEFT sensor sees dark:
			if(SensorValue(lineFollowerRIGHT) > threshold)
			{
				// counter-steer left:
				motor[leftMotor]  = -40;
				motor[rightMotor] = 60;
			}
			if((SensorValue(lineFollowerLEFT) > threshold) && (SensorValue(lineFollowerCENTER) > threshold) && (SensorValue(lineFollowerRIGHT) > threshold))
			{
				backward(30);
				wait(0.1);                                                     					// Waits 0.1 seconds
				stopMotor(leftMotor);                                                  // Right motor stops
				stopMotor(rightMotor);                                                  // Left motor stops                                                      // Waits 6 seconds
				untilBump(bump, 1);
				forward(60);
				wait(0.5);// waits 0.25 seconds

			}
		}
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
