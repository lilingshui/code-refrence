#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<fcntl.h>

int main(int argc, char * argv[])
{
	printf("===== enter main function =====\n");
	int fd = open("/dev/globalmem", O_RDWR);
	if (fd < 0) {
		printf("===== open error =====\n");
		return -1;
	}

	printf("===== open success =====\n");
	char buffer[64] = {0};
	int size = read(fd, buffer, sizeof(buffer));
	write(fd, buffer, sizeof(buffer));

	while(1) {
		sleep(1);
		printf("===== sleep =====\n");
	}

	close(fd);
	return 0;
}



