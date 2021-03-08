#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
	int pdes_1[2];
	int pdes_2[2];
	pipe(pdes_1);
	pipe(pdes_2);

	int rc = fork();

	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(7, &set);

	struct timeval time_before, time_after;
	gettimeofday(&time_before, NULL);

	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		sched_setaffinity(getpid(), sizeof(cpu_set_t), &set);
		for (int i = 0; i < 100; i++) {
			read(pdes_1[0], NULL, 0);
			write(pdes_2[1], NULL, 0);
		}
	} else {
		for (int i = 0; i < 100; i++) {
			write(pdes_1[1], NULL, 0);
			read(pdes_2[0], NULL, 0);
		}
		gettimeofday(&time_after, NULL);
		printf("Time for context switch: %ld microseconds",
		       ((time_after.tv_sec -
			 time_before.tv_sec) * 100000L +
			(time_after.tv_usec - time_before.tv_usec) / 200));
	}
	return 0;
}
