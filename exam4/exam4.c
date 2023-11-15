#include <stdio.h>
#include <unistd.h>

int main() {
	// 현재 프로세스의 ID 출력
	printf("현재 프로세스의 ID: %d\n", getpid());

	// 부모 프로세스의 ID 출력
	printf("부모 프로세스의 ID: %d\n", getppid());
	
	return 0;
}

