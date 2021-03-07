#include <stdio.h>
#include <mosquitto.h>
#include <stdio.h>
#include <mosquitto.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
	int rc,r;
	char v[5];
	
	
	struct mosquitto * mosq;

	mosquitto_lib_init();

	mosq = mosquitto_new("publisher-test", true, NULL);
	while(1){
	sleep(1);
	rc = mosquitto_connect(mosq, "localhost", 1883, 60);
	r = (rand() % (100 - 0));
	printf(" v is %d\n",r);
	if(rc != 0){
		printf("Client could not connect to broker! Error Code: %d\n", rc);
		mosquitto_destroy(mosq);
		return -1;
	}
	//printf("We are now connected to the broker!\n");
	snprintf(v, 10, "%d", r);
	mosquitto_publish(mosq, NULL, "test/t1", 6, v, 0, false);}

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);

	mosquitto_lib_cleanup();
	return 0;
}
