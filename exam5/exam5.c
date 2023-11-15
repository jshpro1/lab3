#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int executeCommand(const char *command, char *const arguments[]) {
	pid_t child_pid = fork();

	if (child_pid == -1) {
		perror("fork 실패");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0) {
		// 자식 프로세스
		if (execvp(command, arguments) == -1) {
			perror("execvp 실패");
			exit(EXIT_FAILURE);
		}
	} else {
	       // 부모 프로세스
		int status;
		waitpid(child_pid, &status, 0);

		if (WIFEXITED(status)) {
		// 자식 프로세스가 정상 종료됨
			return WEXITSTATUS(status);
		} else {
	    		perror("자식 프로세스가 비정상적으로 종료됨");
			exit(EXIT_FAILURE);
		}
	}
    return -1;  // unreachable
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "사용법: %s <command> [arguments...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// executeCommand 함수를 사용하여 외부 명령 실행
	int result = executeCommand(argv[1], &argv[1]);

    	printf("외부 명령 종료 코드: %d\n", result);
    
	return EXIT_SUCCESS;
}    
	   
