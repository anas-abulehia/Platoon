// compile 
//gcc mqtt_subs_1.c -o sub_1 -lmosquitto -lpthread
// excute 
// ./sub_1
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mosquitto.h>

void on_connect(struct mosquitto *mosq, void *obj, int rc) {
	printf("ID: %d\n", * (int *) obj);
	if(rc) {
		printf("Error with result code: %d\n", rc);
		exit(-1);
	}
	mosquitto_subscribe(mosq, NULL, "test/t1", 0);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
	printf("New velocity with topic %s: %s\n", msg->topic, (char *) msg->payload);
}
void* subscribe(void * arg)
{
	int rc, id=12;

	mosquitto_lib_init();

	struct mosquitto *mosq;

	mosq = mosquitto_new("subscribe-test", true, &id);
	mosquitto_connect_callback_set(mosq, on_connect);
	mosquitto_message_callback_set(mosq, on_message);
	
	rc = mosquitto_connect(mosq, "localhost", 1883, 10);

	mosquitto_loop_start(mosq);
	printf("Press Enter to quit...\n");
	getchar();
	mosquitto_loop_stop(mosq, true);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();

}

void* lateral(void * arg){
	srand(time(NULL));
	float lat_angle;
	while(1){
		lat_angle = -1+2*((float)rand())/RAND_MAX;
		printf("the lateral angle is %f\n",lat_angle);
		sleep(3);
	}
}

void* longitudinal(void * arg){
	srand(time(NULL));
	float throttle;
	float brake;
	while(1){
		throttle = 0+1*((float)rand())/RAND_MAX;
		brake = 0+1*((float)rand())/RAND_MAX;
		printf("the throttle angle is %f\n",throttle);
		printf("the brake angle is %f\n",brake);
		sleep(2);
	}
}

int main() {

	pthread_t thread_subs;
	pthread_t thread_lateral;
	pthread_t thread_longitudinal;
	pthread_create(&thread_lateral,NULL,lateral,NULL);
	pthread_create(&thread_subs,NULL,subscribe,NULL);
	pthread_create(&thread_longitudinal,NULL,longitudinal,NULL);

	pthread_join(thread_lateral, NULL);
	pthread_join(thread_subs, NULL);
	pthread_join(thread_longitudinal, NULL);
	
	return 0;
	
}
