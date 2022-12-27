/*
 * Modbus_Circutor_CVM_1D_Registers.h
 *
 *  Created on: 25 okt. 2022
 *      Author: bart
 */

#ifndef MODBUS_CIRCUTOR_CVM_1D_REGISTERS_H_
#define MODBUS_CIRCUTOR_CVM_1D_REGISTERS_H_

// Circutor CVM 1D Device address
static int Circutor_CVM_1D_Address = 0x01;


// Circutor CVM 1D Register addresses
static int Registers_Circutor_CVM_1D[] = {
		0x0000, 0x0032, 0x0044,
		0x0002, 0x0034, 0x0046,
		0x0004, 0x0036, 0x0048,
		0x0006, 0x0038, 0x004A,
		0x0008, 0x003A, 0x004C,
		0x000A, 0x003C, 0x004E,
		0x000C, 0x003E, 0x0050,
		0x000E, 0x0040, 0x0052,
		0x0010, 0x0042, 0x0054,
		0x0012, 0x0014, 0x0016, 0x0018, 0x001A, 0x001C, 0x001E, 0x0020,
		0x0022, 0x0024, 0x0026, 0x0028, 0x002A, 0x002C, 0x002E, 0x0030

};


// Circutor CVM 1D Register names
static char RegisterNames_Circutor_CVM_1D[][50] = {
		"ActualVoltage", "MaximumVoltage", "MinimumVoltage",
		"ActualCurrent", "MaximumCurrent", "MinimumCurrent",
		"ActualActivePower", "MaximumActivePower", "MinimumActivePower",
		"ActualReactivePower", "MaximumReactivePower", "MinimumReactivePower",
		"ActualInductiveReactivePower", "MaximumInductiveReactivePower", "MinimumInductiveReactivePower",
		"ActualCapacitiveInductivePower", "MaximumCapacitiveInductivePower", "MinimumCapacitiveInductivePower",
		"ActualApparentPower", "MaximumApparentpower", "MinimumApparentpower",
		"ActualPowerFactor", "MaximumPowerFactor", "MinimumPowerFactor",
		"ActualMaximumDemand", "MaximumMaximumDemand", "MinimumMaximumDemand",
		"ActiveEnergy", "InductiveReactiveEnergy", "CapacitiveReactiveEnergy", "ReactiveEnergy", "PartialActiveEnergy",
		"PartialInductiveReactiveEnergy", "PartialCapacitiveReactiveEnergy", "PartialReactiveEnergy", "GeneratedActiveEnergy",
		"GeneratedInductiveReactiveEnergy", "GeneratedCapacitiveReactiveEnergy", "GeneratedTotalReactiveEnergy",
		"PartialGeneratedActiveEnergy", "PartialGeneratedInductiveReactiveEnergy", "GeneratedCapacitiveReactiveEnergy",
		"PartialGeneratedTotalReactiveEnergy"
};

/* If topic sends to much unused data, maybe it is better to make a extra array  and loop over the topic until we reach a Line Feed
 * and replace them with a zero terminated string.

*/

struct mqtt
{
	unsigned char Topic[100];
	unsigned char TopicPartOne[45];
	unsigned char TopicPartTwo[50];
	float Payload;
	int SizeTopicPartOne;
    int SizeRegisterArray;
};

float ConvertToRegisterUnits(int data, int type);
void Readmodbus_CircutorData_MqttTopicPayload(int type, int fd, struct mqtt *data);

#endif /* MODBUS_CIRCUTOR_CVM_1D_REGISTERS_H_ */
