#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *get_sum(void *p)
{
	int i;
	int n = *(int*)p;
	int sum = 0;
	int *ret;
	int timeout = 10;

	for(i = 0;i < n;i++) {
		sum += i;
	}

	ret = (int*)malloc(sizeof(int));
	*ret = sum;

	while(timeout > 0) {
		printf("[%s:%d] wainting for timeout(%d)\n", __FILE__, __LINE__, timeout);
		timeout--;
		sleep(1);
	}

	return (void*)ret;
}

int main(void)
{
	pthread_t t1;
	int n = 10;
	int *ret;
	int timeout = 3;

	pthread_create(&t1, NULL, get_sum, &n);
	pthread_detach(t1);
	while(timeout > 0) {
		printf("[%s:%d] wainting for timeout(%d)\n", __FILE__, __LINE__, timeout);
		timeout--;
		sleep(1);
	}
	pthread_join(t1, (void**)&ret);

	printf("[%s:%d] ret = %d\n", __FILE__, __LINE__, *ret);

	return 0;
}
