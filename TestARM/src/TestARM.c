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
#define CLIENTID    "Circutor"
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
#define ACTIVEENERGIE		27






int main (int argc, char *argv[])
{
	// Used with Serial and modbus.

	struct mqtt mqttdata;
	strcpy(mqttdata.TopicPartOne, "ProjectenVoorHetWerkveld/CircutorEnergyMeter/");
    int fd;
    char serialdev[] = "/dev/ttyUSB0";


    // Used with paho mqtt client.

    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;


    // Creating the mqtt client and connect to the broker

    if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
         printf("Failed to create client, return code %d\n", rc);
         exit(EXIT_FAILURE);
    }

    else
    {
    	printf("MQTT Client created.\n\n");
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
    	printf("MQTT Client connected to the Mosquitto broker.\n\n");
    }


    while(1)
    {
        // Open the serial port, read the modbus data and close the serial port.

        fd = openserial(serialdev);

        if (!fd)
        {
            fprintf(stderr, "Error while initializing %s.\n", serialdev);
            //return 1;
        }


        Readmodbus_CircutorData_MqttTopicPayload(VOLTAGE, fd, &mqttdata);
        closeserial(fd);

        // Publish message

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
        printf("Message with delivery token %d delivered.\n\n", token);

        sleep(2);

        // Open the serial port, read the modbus data and close the serial port.

        fd = openserial(serialdev);

        if (!fd)
        {
            fprintf(stderr, "Error while initializing %s.\n", serialdev);
            //return 1;
        }


        Readmodbus_CircutorData_MqttTopicPayload(CURRENT, fd, &mqttdata);
        closeserial(fd);

        // Publish message

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
        printf("Message with delivery token %d delivered.\n\n", token);

        sleep(2);

        // Open the serial port, read the modbus data and close the serial port.

        fd = openserial(serialdev);

        if (!fd)
        {
            fprintf(stderr, "Error while initializing %s.\n", serialdev);
            //return 1;
        }


        Readmodbus_CircutorData_MqttTopicPayload(ACTIVEPOWER, fd, &mqttdata);
        closeserial(fd);

        // Publish message

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
        printf("Message with delivery token %d delivered.\n\n", token);

        sleep(2);


        // Open the serial port, read the modbus data and close the serial port.

                fd = openserial(serialdev);

                if (!fd)
                {
                    fprintf(stderr, "Error while initializing %s.\n", serialdev);
                    //return 1;
                }


                Readmodbus_CircutorData_MqttTopicPayload(ACTIVEENERGIE, fd, &mqttdata);
                closeserial(fd);

                // Publish message

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
                printf("Message with delivery token %d delivered.\n\n", token);

                sleep(2);
    }




    // Disconnect the client from the broker.

    if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
        printf("Failed to disconnect, return code %d\n", rc);
    MQTTClient_destroy(&client);
    return rc;


}



