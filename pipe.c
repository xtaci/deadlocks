#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	int ch1[2];
	int ch2[2];

	char buf1[100];
	char buf2[100];

	// create ch1 
	if (pipe(ch1) == -1) {
		perror("ch1");
		exit(-1);
	}

	// create ch2
	if (pipe(ch2) == -1) {
		perror("ch2");
		exit(-1);
	}

	// commit this line to create deadlock
	write(ch2[1], buf1, 100);

	ssize_t n;
	pid_t pid = fork();

	for (;;) {
		switch (pid) {
			case 0: // child
				n = read(ch1[0], buf1,100);
				printf("child read %d\n",n);
				n = write(ch2[1], buf1, 100);
				printf("child write %d\n",n);
				break;
			default:
				n = read(ch2[0], buf2,100);
				printf("parent read %d\n",n);
				n = write(ch1[1], buf2, 100);
				printf("parent write %d\n",n);
		}
	}
}
