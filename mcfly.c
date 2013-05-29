#include <time.h>
#include <stdio.h>
#include <errno.h>

int main()
{
	time_t now, last;
	struct tm *nowtm, *lasttm;
	struct tm tmp1, tmp2;
	char timestamp[21];
	
	now = time(NULL);
	nowtm = gmtime_r(&now, &tmp1);
	if (!strftime(timestamp, 21, "%Y-%m-%dT%XZ", nowtm))
		return -EFAULT;
	printf("Started at %s\n", timestamp);

	while (1) {
		last = now;
		now = time(NULL);
		if ((now - last) > 1) {
			/* We time jumped! */
			printf("**** Time jump detected! ****\n");
			nowtm = gmtime_r(&now, &tmp1);
			lasttm = gmtime_r(&last, &tmp2);
			if (!strftime(timestamp, 21, "%Y-%m-%dT%XZ", lasttm))
				return -EFAULT;
			printf("Last was %s\n", timestamp);
			if (!strftime(timestamp, 21, "%Y-%m-%dT%XZ", nowtm))
				return -EFAULT;
			printf("Now is %s\n", timestamp);
			return -EINVAL;
		}
	}

	return 0;
}
