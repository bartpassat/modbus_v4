//============================================================================
// Name        : TestARM.c
// Author      : Bart
// Version     :
// Copyright   : Your copyright notice
// Description : Energiemeter to cloud
//============================================================================




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
#include "Serial.h"
#include "Modbus.h"
#include "Modbus_Circutor_CVM_1D_Registers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"

#define ADDRESS     "tcp://test.mosquitto.org:1883"
#define CLIENTID    "ExampleClientPub2"
#define TOPIC       "ProjectenVoorHetWerkveld/Beaglebone/test"
#define PAYLOAD     "Beaglebone say Hello!"
#define QOS         1
#define TIMEOUT     10000L

//defines for reading the energy meter
#define VOLTAGE				0
#define	VOLTAGEMAX			1
#define VOLTAGEMIN			2
#define CURRENT				3
#define CURRENTMAX			4
#define CURRENTMIN			5
#define ACTIVEPOWER			6
#define ACTIVEPOWERMAX		7
#define ACTIVEPOWERMIN		8

#define ENABLEMODBUS
#define ENABLEMQTT





int main (int argc, char *argv[])
{

#ifdef ENABLEMODBUS

	struct mqtt mqttdata;
	strcpy(mqttdata.TopicPartOne, "ProjectenVoorHetWerkveld/CircutorEnergyMeter/");
    int fd;
    int error = 0;
    char serialdev[] = "/dev/ttyUSB0";



    puts(serialdev);
    puts ("Open port");

    fd = openserial(serialdev);

    if (!fd)
    {
        fprintf(stderr, "Error while initializing %s.\n", serialdev);
        //return 1;
    }

    Readmodbus_CircutorData_MqttTopicPayload(ACTIVEPOWER, fd, &mqttdata);
    closeserial(fd);

#endif

#ifdef ENABLEMQTT

    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
         printf("Failed to create client, return code %d\n", rc);
         exit(EXIT_FAILURE);
    }

    else
    {
    	printf("Client creation ok.\n");
    }

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;


    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    else
    {
    	printf("Client connect ok.\n");
    }


    pubmsg.payload = (char *) malloc(20);
    sprintf(pubmsg.payload, "%f", mqttdata.Payload);
    pubmsg.payloadlen = (int)strlen(pubmsg.payload);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    if ((rc = MQTTClient_publishMessage(client, mqttdata.Topic, &pubmsg, &token)) != MQTTCLIENT_SUCCESS)
    {
         printf("Failed to publish message, return code %d\n", rc);
         exit(EXIT_FAILURE);
    }
    else
    {
    	printf("Message published.\n");
    }

    printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), pubmsg.payload, mqttdata.Topic, CLIENTID);

    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);

    if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
        printf("Failed to disconnect, return code %d\n", rc);
    MQTTClient_destroy(&client);
    return rc;

#endif
}



