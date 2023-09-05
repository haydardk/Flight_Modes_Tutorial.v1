/*
 * Flight_Modes_Tut.h
 *
 *  Created on: Sep 4, 2023
 *      Author: CASPER
 */

#ifndef INC_FLIGHT_MODES_TUT_H_
#define INC_FLIGHT_MODES_TUT_H_

#define MAX_SERVO_VALUE 1750
#define MIN_SERVO_VALUE 1250

#define MAX_THROTTLE_VALUE 2000//2128 - 1600     DÜZENLENECEK
#define MIN_THROTTLE_VALUE 1600

#define TAKEOFF_MAX_THROTTLE 2000
#define TAKEOFF_MIN_THROTTLE 1700
#define TAKEOFF_PITCH 20
#define TAKEOFF_ALTITUDE 3

typedef enum {
	 FLY_BY_WIRE = 1 ,
	 ALTITUDE_F = 2 ,
	 STABILIZE = 3,
	 MANUAL = 4,
}Flight_Mode_e;

Flight_Mode_e S_FLY_MODE ;

int Flight_Mode_Choose_And_Altered(void);
void Flight_Mode_FBW(void);
void Flight_Mode_Altitude(void);
void Flight_Mode_Stabilize(void);
void Flight_Mode_Manual(void);



#endif /* INC_FLIGHT_MODES_TUT_H_ */
