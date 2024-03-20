#include <stdio.h>

int main() {
unsigned char tape[30000] = {0};
unsigned char *memory = tape;
int loop0 = 0;
while (*memory) {
memory += 1;(*memory) += 1;int loop1 = 0;
while (*memory) {
memory += 1;(*memory) += 1;int loop2 = 0;
while (*memory) {
memory += 1;(*memory) -= 1;(*memory) += 1;int loop3 = 0;
while (*memory) {
memory += 1;(*memory) -= 1;(*memory) += 1;putchar(*memory);memory += 1;memory -= 1;putchar(*memory);}
memory += 1;putchar(*memory);}
}
}

return 0;
}