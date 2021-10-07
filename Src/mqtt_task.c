/*
 * mqtt_task.c
 *
 *  Created on: 2020. 5. 19.
 *      Author: eziya76@gmail.com
 */

#include "main.h"
#include "mqtt_task.h"
#include "RTC.h"
#include "string.h"
#include "MPPT.h"

#define SERVER_ADDR		"a36r1007e087sh-ats.iot.eu-west-1.amazonaws.com" //replace your endpoint here
#define MQTT_PORT		"8883"

//mqtt subscribe task
void MqttClientSubTask(void const *argument)
{
	while(1)
	{
		if(!mqttClient.isconnected)
		{
			//try to connect to the broker
			MQTTDisconnect(&mqttClient);
			MqttConnectBroker();
			osDelay(1000);
		}
		else
		{
			/* !!! Need to be fixed
			 * mbedtls_ssl_conf_read_timeout has problem with accurate timeout
			 */
			MQTTYield(&mqttClient, 1000);
		}
	}
}

//mqtt publish task
void MqttClientPubTask(void const *argument)
{
	const char *str="{ \"MQTT\": \"poruka sa STM32\"}";
	//	char *str=pvPortMalloc(100*sizeof(char));
	char temperatura[10];
	MQTTMessage message;
	float temp;
	int tempint;

	while(1)
	{
		temp=getTemp();
		tempint=temp/1;
		//sprintf((char*)str,"{ \"MQTT\": \"poruka sa STM32\",\n \"Temperatura\" : \"%d\" \n}", tempint);

		if(mqttClient.isconnected)
		{
			message.payload = (void*)str;
			message.payloadlen = strlen(str);

			MQTTPublish(&mqttClient, "test", &message); //publish a message to "test" topic
		}
		osDelay(10000);
	}
}

void StartT2RTC(void const * argument)
{
  /* USER CODE BEGIN StartT2RTC */
	struct Vreme time;
  /* Infinite loop */
  for(;;)
  {
	HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
	time=getTime();
    osDelay(7500);
  }
  /* USER CODE END StartT2RTC */
}

void StartT3MPPT(void const * argument)
{
  /* USER CODE BEGIN StartT2RTC */
	struct Poruka PorMppt;
  /* Infinite loop */
  for(;;)
  {
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	PorMppt=getMppt();
	osDelay(6000);
  }
  /* USER CODE END StartT2RTC */
}

int MqttConnectBroker()
{
	int ret;
	osThreadId Task2RTCHandle;
	osThreadId Task3MPPTHandle;

	net_clear();
	ret = net_init(&net, SERVER_ADDR);
	if(ret != MQTT_SUCCESS)
	{
		printf("net_init failed.\n");
		return -1;
	}

	ret = net_connect(&net, SERVER_ADDR, MQTT_PORT);
	if(ret != MQTT_SUCCESS)
	{
		printf("net_connect failed.\n");
		return -1;
	}

	MQTTClientInit(&mqttClient, &net, 1000, sndBuffer, sizeof(sndBuffer), rcvBuffer, sizeof(rcvBuffer));

	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	data.willFlag = 0;
	data.MQTTVersion = 3;
	data.clientID.cstring = ""; //no client id required
	data.username.cstring = ""; //no user name required
	data.password.cstring = ""; //no password required
	data.keepAliveInterval = 60;
	data.cleansession = 1;

	ret = MQTTConnect(&mqttClient, &data);
	if(ret != MQTT_SUCCESS)
	{
		printf("MQTTConnect failed.\n");
		return ret;
	}

	ret = MQTTSubscribe(&mqttClient, "test", QOS0, MqttMessageArrived);
	if(ret != MQTT_SUCCESS)
	{
		printf("MQTTSubscribe failed.\n");
		return ret;
	}

	printf("MqttConnectBroker O.K.\n");
	osThreadDef(Task2RTC, StartT2RTC, osPriorityNormal, 0, 256);
	Task2RTCHandle = osThreadCreate(osThread(Task2RTC), NULL);
	osThreadDef(Task3MPPT, StartT3MPPT, osPriorityNormal, 0, 256);
	Task3MPPTHandle = osThreadCreate(osThread(Task3MPPT), NULL);
	return MQTT_SUCCESS;
}

void MqttMessageArrived(MessageData* msg)
{
	HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin); //toggle pin when new message arrived

	MQTTMessage* message = msg->message;
	memset(msgBuffer, 0, sizeof(msgBuffer));
	memcpy(msgBuffer, message->payload,message->payloadlen);

	printf("MQTT MSG[%d]:%s\n", (int)message->payloadlen, msgBuffer);
}
