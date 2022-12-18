/*
 * Modbus_Circutor_CVM_1D_Registers.c
 *
 *  Created on: 25 okt. 2022
 *      Author: bart
 */

#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include "Serial.h"
#include "Modbus.h"

#define	VOLTAGE 		0
#define CURRENT			3
#define ACTIVEPOWER		6



float ConvertToRegisterUnits(int data, int type)
{
	float ConvertedData;
	if (type == VOLTAGE)
	{
		ConvertedData = (float) data;
		ConvertedData = (ConvertedData/10);
	}

	if (type == CURRENT || type == ACTIVEPOWER)
	{
		ConvertedData = (float) data;
		ConvertedData = (ConvertedData/100);
	}

	return ConvertedData;
}

