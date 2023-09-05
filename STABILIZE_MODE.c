/*
 * STABILIZE_MODE.c
 *
 *  Created on: Sep 4, 2023
 *      Author: CASPER
 */
#include "stdint.h"
#include "Flight_Modes_Tut.h"

extern float Temperature_BMP, Pressure_BMP , Humidity_BMP,Altitude_BMP; //BMP or BME

extern char GGA[100]; //GPS
extern char RMC[100];
//GPSSTRUCT gpsData;

extern uint32_t raw_Volt; //Pitot
extern float  air_speed, voltage ;
extern float kpascal_pitot ;
extern float pitot_velocity ;

extern uint8_t buf[25]; // SBUS
extern uint16_t CH[18];

extern uint32_t ESC_RunValue ;

// STARTING
extern uint32_t ESC_RunValue, servo1value, servo2value, servo3value, servo4value;

extern uint32_t ThrustRaw,Thrustvalue,RudderRaw,Ruddervalue,ElevatorRaw,Elevatorvalue,R_AileronRaw,R_Aileronvalue,L_AileronRaw,L_Aileronvalue;

const float Constant_Altitude ;

extern Flight_Mode_e S_FLY_MODE ;

void Flight_Mode_Stabilize(void){
	if (ESC_RunValue < MIN_THROTTLE_VALUE){
		ESC_RunValue = MIN_THROTTLE_VALUE;
	}else if(ESC_RunValue > MAX_THROTTLE_VALUE){
		ESC_RunValue = MAX_THROTTLE_VALUE;
	}

	// IMU VERİLERİ İLE UÇAK STABİLİZASYONU SAĞLANACAK

	RudderRaw = (uint32_t)CH[3]; // REFERENCE POINT
	Ruddervalue = ((( (uint32_t)RudderRaw - 314 ) / 1007 ) * 1000) + 1000;
	ElevatorRaw = (uint32_t)CH[3]; // ?
	Elevatorvalue = ((( (uint32_t)ElevatorRaw - 314 ) / 1007 ) * 1000) + 1000;
	R_AileronRaw = (uint32_t)CH[3]; // ?
	R_Aileronvalue = ((( (uint32_t)R_AileronRaw - 314 ) / 1007 ) * 1000) + 1000;
	L_AileronRaw = (uint32_t)CH[3]; // ?
	L_Aileronvalue = ((( (uint32_t)L_AileronRaw - 314 ) / 1007 ) * 1000) + 1000;

	ESC_RunValue = Thrustvalue;
	servo1value=Ruddervalue;
	servo2value=Elevatorvalue;
	servo3value=R_Aileronvalue;
	servo4value=L_Aileronvalue;
}

