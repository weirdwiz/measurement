#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
	struct timeval time_before, time_after;
	gettimeofday(&time_before, NULL);
	for (int i = 0; i < 10; i++) {
		read(STDIN_FILENO, NULL, 0);
	}
	gettimeofday(&time_after, NULL);

	printf("Time for one zero byte read: %ld microseconds",
	       ((time_after.tv_sec - time_before.tv_sec) * 1000000L +
		(time_after.tv_usec - time_before.tv_usec)) / 10);
	return 0;
}
