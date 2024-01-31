#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "xtimer.h"
#include "net/emcute.h"
#include "net/ipv6/addr.h"
#include "msg.h"
#include "thread.h"
#include "shell.h"
#include "mutex.h"
#include "lpsxxx.h"
#include "lpsxxx_params.h"

static lpsxxx_t lpsxxx;

#define DELAY (55000LU * US_PER_MS)

int16_t temp = 0;
uint16_t pres = 0;

#ifndef EMCUTE_ID
#define EMCUTE_ID ("station1")
#endif

#ifndef EMCUTE_DEFAULT_PORT
#define EMCUTE_DEFAULT_PORT (1885)
#endif

#define EMCUTE_PRIO (THREAD_PRIORITY_MAIN - 1)
#define NUMOFSUBS (1U)
#define TOPIC_MAXLEN (128U)
#define STATUS_LEN 5
#define MAIN_QUEUE_SIZE (8)

static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];
static char status_MQTT[STATUS_LEN] = "";

typedef struct sensors{
    int temp;
    int press;
} t_sensors;

static char stack[THREAD_STACKSIZE_DEFAULT];
char stack_loop[THREAD_STACKSIZE_MAIN];
char stack_measure[THREAD_STACKSIZE_MAIN];

kernel_pid_t tmain, tmes;

static emcute_sub_t subscriptions[NUMOFSUBS];
static char topics[NUMOFSUBS][TOPIC_MAXLEN];
static void *emcute_thread(void *arg)
{
    (void)arg;
    emcute_run(EMCUTE_DEFAULT_PORT, EMCUTE_ID);
    return NULL;
}

static void on_pub(const emcute_topic_t *topic, void *data, size_t len){
    char *in = (char *)data;

    char comm[len+1];

    printf("### got publication for topic '%s' [%i] ###\n",
           topic->name, (int)topic->id);
    for (size_t i = 0; i < len; i++) {
        comm[i] = in[i];
    }
    comm[len] = '\0';
    printf("%s", comm);

    for(size_t i = 0; i < STATUS_LEN; i++){
        if(i < len){
            status_MQTT[i] = in[i];
        } else {
            status_MQTT[i] = 0;
        }
    }

    puts("\n");
}

static int pub(char* topic, const char* data, int qos){
    emcute_topic_t t;
    unsigned flags = EMCUTE_QOS_0;

    switch(qos){
        case 1:
            flags |= EMCUTE_QOS_1;
            break;
        case 2:
            flags |= EMCUTE_QOS_2;
            break;
        default:
            flags |= EMCUTE_QOS_0;
            break;
    }

    t.name = MQTT_TOPIC_OUT;
    if(emcute_reg(&t) != EMCUTE_OK){
        puts("Unable to obtain the topic ID");
        return 1;
    }
    if(emcute_pub(&t, data, strlen(data), flags) != EMCUTE_OK){
        printf("Unable to publish data to the topic '%s [%i]'\n", t.name, (int)t.id);
        return 1;
    }

    printf("Publication is done: Published %s on topic %s\n", data, topic);
    return 0;
}

const char* data_parse(t_sensors* sensors){
    static char json[128];

    sprintf(json, "{\"Temp\": \"%i.%u\", \"press\": \"%d\"}",
                  ((sensors->temp)/100), ((sensors->temp)%100), sensors->press);
    
    return json;
}

int setup_mqtt(void)
{
    memset(subscriptions, 0, (NUMOFSUBS * sizeof(emcute_sub_t)));
    xtimer_sleep(10);
    printf("Dev_id: %s\n",EMCUTE_ID);
    thread_create(stack, sizeof(stack), EMCUTE_PRIO, 0, emcute_thread, NULL, "emcute");
    printf("Connecting to MQTT-SN broker %s port %d.\n", SERVER_ADDR, SERVER_PORT);

    sock_udp_ep_t gw = {
        .family = AF_INET6,
        .port = SERVER_PORT
    };

    char *message = "connected";
    size_t len = strlen(message);

    if (ipv6_addr_from_str((ipv6_addr_t *)&gw.addr.ipv6, SERVER_ADDR) == NULL) {
        printf("error parsing IPv6 address\n");
        return 1;
    }

    if (emcute_con(&gw, true, MQTT_TOPIC_OUT, message, len, 0) != EMCUTE_OK) {
        printf("unable to connect to [%s]:%i\n", SERVER_ADDR, (int)gw.port);
        return 1;
    }

    printf("connected to gateway at [%s]:%i\n", SERVER_ADDR, (int)gw.port);
    
    unsigned flags = EMCUTE_QOS_0;
    subscriptions[0].cb = on_pub;
    strcpy(topics[0], MQTT_TOPIC_IN);
    subscriptions[0].topic.name = MQTT_TOPIC_IN;

    if (emcute_sub(&subscriptions[0], flags) != EMCUTE_OK) {
        printf("unable to subscribe to %s\n", MQTT_TOPIC_IN);
        return 1;
    }

    printf("finally subscribed to %s\n", MQTT_TOPIC_IN);
    return 1;
}

int started = -1;
void *main_loop(void *arg){
    (void)arg;
    tmain = thread_getpid();
    t_sensors sensors;

    xtimer_ticks32_t last= xtimer_now();
    while(1) {
        srand(time(NULL));
        lpsxxx_read_temp(&lpsxxx, &temp);
        lpsxxx_read_pres(&lpsxxx, &pres);
        sensors.temp = temp;
        sensors.press = pres;
        printf("Pressure value from sensors: %uhPa\n", pres);
        printf("Temperature value from sensors: %i.%u°C\n", (temp / 100), (temp % 100));
        printf("[MQTT] sending data to Broker\n");
        pub(MQTT_TOPIC_OUT, data_parse(&sensors), 0);
        xtimer_sleep(2);
        printf("\n");
        xtimer_periodic_wakeup(&last, DELAY);
    }
}

static int cmd_status(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    printf("hello!!!\n");
    return 0;
}

static int cmd_mqtt_status(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    printf("mqtt broker: %s \nPORT: %d \nTOPIC_IN: %s/%s TOPIC_OUT: %s\n", SERVER_ADDR, SERVER_PORT,MQTT_TOPIC_IN,EMCUTE_ID,MQTT_TOPIC_OUT);
    return 0;
}

static const shell_command_t shell_commands[] = {
    { "status", "get a status report", cmd_status },
    { "mqtt_status", "mqtt status report", cmd_mqtt_status},
    { NULL, NULL, NULL }
};

int main(void){
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    lpsxxx_init(&lpsxxx, &lpsxxx_params[0]);
    puts("trying to setup mqtt.\n");
    setup_mqtt();
    xtimer_sleep(3);
    thread_create(stack_loop, sizeof(stack_loop), EMCUTE_PRIO, 0, main_loop, NULL, "main_loop");
    puts("Thread began");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}
