#include <stdio.h>
#include <unistd.h>

int main() {
	unsigned char tape[30000] = {0};
	unsigned char *memory = tape;

	*memory+=72;
	sleep(0);
	putchar(*memory);
	memory+=1;
	*memory+=101;
	sleep(0);
	putchar(*memory);
	memory+=1;
	*memory+=108;
	sleep(0);
	putchar(*memory);
	memory+=1;
	*memory+=108;
	sleep(0);
	putchar(*memory);
	memory+=1;
	*memory+=111;
	sleep(0);
	putchar(*memory);
	memory+=1;
	*memory+=32;
	sleep(0);
	putchar(*memory);
	memory+=1;
	*memory+=87;
	sleep(0);
	putchar(*memory);
	memory+=1;
	*memory+=111;
	sleep(0);
	putchar(*memory);
	memory+=1;
	*memory+=114;
	sleep(0);
	putchar(*memory);
	memory+=1;
	*memory+=108;
	sleep(0);
	putchar(*memory);
	memory+=1;
	*memory+=100;
	sleep(0);
	putchar(*memory);
	memory+=1;
	*memory+=33;
	sleep(0);

	return 0;
}