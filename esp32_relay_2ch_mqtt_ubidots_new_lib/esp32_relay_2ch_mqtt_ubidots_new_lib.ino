#include "UbidotsEsp32Mqtt.h"

#define WIFISSID "SSID" // Put your WifiSSID here
#define PASSWORD "SSIDPASSWORD" // Put your wifi password here
#define TOKEN "XXXX-xxxxxxxxxxxxxxxxxxxxxxxx"

#define RELAY1_VARIABLE_LABEL "relay1"    // Assing the variable label to subscribe
#define RELAY2_VARIABLE_LABEL "relay2"   // Assing the variable label to subscribe

#define DEVICE_LABEL "esp32-device" // Assig the device label to subscribe

#define RELAY1 23
#define RELAY2 22

const uint8_t NUMBER_OF_VARIABLES = 2;                                                                                                            // Number of variable to subscribe to
char *variable_labels[NUMBER_OF_VARIABLES] = {RELAY1_VARIABLE_LABEL, RELAY2_VARIABLE_LABEL}; // labels of the variable to subscribe to

float CONTROL1;  // Name of the variable to be used within the code.
float CONTROL2;  // Name of the variable to be used within the code.

float value;      // To store incoming value.
uint8_t variable; // To keep track of the state machine and be able to use the switch case.

const int ERROR_VALUE = 65535; // Set here an error value

Ubidots ubidots(TOKEN);

void callback(char *topic, byte *payload, unsigned int length)
{
    char *variable_label = (char *)malloc(sizeof(char) * 30);
    get_variable_label_topic(topic, variable_label);
    Serial.println(variable_label);
    value = btof(payload, length);
    set_state(variable_label);
    execute_cases();
    free(variable_label);
}

// Parse topic to extract the variable label which changed value
void get_variable_label_topic(char *topic, char *variable_label)
{
    Serial.print("topic:");
    Serial.println(topic);
    sprintf(variable_label, "");
    for (int i = 0; i < NUMBER_OF_VARIABLES; i++)
    {
        char *result_lv = strstr(topic, variable_labels[i]);
        if (result_lv != NULL)
        {
            uint8_t len = strlen(result_lv);
            char result[100];
            uint8_t i = 0;
            for (i = 0; i < len - 3; i++)
            {
                result[i] = result_lv[i];
            }
            result[i] = '\0';
            Serial.print("Label is: ");
            Serial.println(result);
            sprintf(variable_label, "%s", result);
            break;
        }
    }
}

// cast from an array of chars to float value.
float btof(byte *payload, unsigned int length)
{
    char *demo_ = (char *)malloc(sizeof(char) * 10);
    for (int i = 0; i < length; i++)
    {
        demo_[i] = payload[i];
    }
    return atof(demo_);
}

// State machine to use switch case
void set_state(char *variable_label)
{
    variable = 0;
    for (uint8_t i = 0; i < NUMBER_OF_VARIABLES; i++)
    {
        if (strcmp(variable_label, variable_labels[i]) == 0)
        {
            break;
        }
        variable++;
    }
    if (variable >= NUMBER_OF_VARIABLES)
        variable = ERROR_VALUE; // Not valid
}

// Function with switch case to determine which variable changed and assigned the value accordingly to the code variable
void execute_cases()
{
    switch (variable)
    {
    case 0:
        CONTROL1 = value;
         digitalWrite(RELAY1, !value);
        Serial.print("CONTROL1: ");
        Serial.println(CONTROL1);
        Serial.println();
        break;
    case 1:
        CONTROL2 = value;
         digitalWrite(RELAY2, !value);
        Serial.print("CONTROL2: ");
        Serial.println(CONTROL2);
        Serial.println();
        break;
    case ERROR_VALUE:
        Serial.println("error");
        Serial.println();
        break;
    default:
        Serial.println("default");
        Serial.println();
    }
}

/****************************************
Main Functions
****************************************/

void setup()
{
    Serial.begin(115200);
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    digitalWrite(RELAY1, HIGH);
    digitalWrite(RELAY2, HIGH);

    // ubidots.setDebug(true);  // uncomment this to make debug messages available
    ubidots.connectToWifi(WIFISSID, PASSWORD);
    ubidots.setCallback(callback);
    ubidots.setup();
    ubidots.reconnect();
    for (uint8_t i = 0; i < NUMBER_OF_VARIABLES; i++)
    {
        ubidots.subscribeLastValue(DEVICE_LABEL, variable_labels[i]); // Insert the device and Variable's Labels
        delay(100);
    }
}

void loop()
{
    if (!ubidots.connected())
    {
        ubidots.reconnect();
        for (uint8_t i = 0; i < NUMBER_OF_VARIABLES; i++)
        {
            ubidots.subscribeLastValue(DEVICE_LABEL, variable_labels[i]); // Insert the device and Variable's Labels
            delay(100);
        }
    }

    ubidots.loop();
}
