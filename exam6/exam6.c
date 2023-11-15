#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Ctrl+C 시그널 핸들러 등록
void handleCtrlC(int signum) {
	printf("Ctrl+C를 누르셨습니다. 프로그램을 종료합니다.\n");
	exit(EXIT_SUCCESS);
}

int main() {
	 // Ctrl+C 시그널 핸들러 등록
	if (signal(SIGINT, handleCtrlC) == SIG_ERR) {
		perror("시그널 핸들러 등록 실패");	
		exit(EXIT_FAILURE);
	}

	printf("Ctrl+C를 눌러보세요. 프로그램은 계속 실행됩니다.\n");

	// 프로그램이 종료되지 않도록 대기
	while (1) {
		sleep(1);
	}

	return EXIT_SUCCESS;
}

