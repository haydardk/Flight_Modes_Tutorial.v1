/*
 * FlightModes_Tutorial.c
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

// STARTING
extern uint32_t ESC_RunValue, servo1value, servo2value, servo3value, servo4value;

extern uint32_t ThrustRaw,Thrustvalue,RudderRaw,Ruddervalue,ElevatorRaw,Elevatorvalue,R_AileronRaw,R_Aileronvalue,L_AileronRaw,L_Aileronvalue;

const float Constant_Altitude ;

extern Flight_Mode_e S_FLY_MODE ;

int Flight_Mode_Choose_And_Altered(void){
	// SBUS DATA PROCESS
	Flight_Mode_e oncekimod , suankimod ;
	oncekimod = S_FLY_MODE ;

	if (CH[5]==306){     //  DÜZENLENECEK !!!!!!!
		S_FLY_MODE = FLY_BY_WIRE;
	}else if(CH[5]==1694) {
		S_FLY_MODE = ALTITUDE_F;
	}else if (CH[6]==306){
		S_FLY_MODE = STABILIZE;
	}else if (CH[6]==1694){
		S_FLY_MODE = MANUAL;
	}
	suankimod = S_FLY_MODE;
	if (oncekimod==suankimod){
		return 1;
	}else{
		return 0;
	}
}
    // This two funciton has to be used in order
void Flight_Mode_Choose_And_Initiate(void){
	if (S_FLY_MODE == FLY_BY_WIRE){
		Flight_Mode_FBW();
	}else if (S_FLY_MODE == ALTITUDE_F){
		Flight_Mode_Altitude();
	}else if (S_FLY_MODE == STABILIZE){
		Flight_Mode_Stabilize();
	}else if (S_FLY_MODE == MANUAL){
		Flight_Mode_Manual();
	}
}

	/* RudderRaw = (uint32_t)CH[3]; // REFERENCE POINT
	Ruddervalue = ((( (uint32_t)RudderRaw - 314 ) / 1007 ) * 1000) + 1000;
	ElevatorRaw = (uint32_t)CH[3]; // ?
	Elevatorvalue = ((( (uint32_t)ElevatorRaw - 314 ) / 1007 ) * 1000) + 1000;
	R_AileronRaw = (uint32_t)CH[3]; // ?
	R_Aileronvalue = ((( (uint32_t)R_AileronRaw - 314 ) / 1007 ) * 1000) + 1000;
	L_AileronRaw = (uint32_t)CH[3]; // ?
	L_Aileronvalue = ((( (uint32_t)L_AileronRaw - 314 ) / 1007 ) * 1000) + 1000; */


void Flight_Mode_FBW(void){
		if(Ruddervalue > MAX_SERVO_VALUE){
			Ruddervalue=MAX_SERVO_VALUE;
		}
		if(Ruddervalue < MIN_SERVO_VALUE){
			Ruddervalue=MIN_SERVO_VALUE;
		}
		if(Elevatorvalue > MAX_SERVO_VALUE){
			Elevatorvalue=MAX_SERVO_VALUE;
		}
		if(Elevatorvalue < MIN_SERVO_VALUE){
			Elevatorvalue=MIN_SERVO_VALUE;
		}
		if(L_Aileronvalue > MAX_SERVO_VALUE){
			L_Aileronvalue=MAX_SERVO_VALUE;
		}
		if(L_Aileronvalue < MIN_SERVO_VALUE){
			L_Aileronvalue=MIN_SERVO_VALUE;
		}
		if(R_Aileronvalue > MAX_SERVO_VALUE){
			R_Aileronvalue=MAX_SERVO_VALUE;
		}
		if(R_Aileronvalue < MIN_SERVO_VALUE){
			R_Aileronvalue=MIN_SERVO_VALUE;
		}
		ThrustRaw = (uint32_t)CH[4];
		Thrustvalue = (ThrustRaw-306)/(1694)*1000 + 1600;

		ESC_RunValue = Thrustvalue;
		servo1value=Ruddervalue;
		servo2value=Elevatorvalue;
		servo3value=R_Aileronvalue;
		servo4value=L_Aileronvalue;
}
